#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node
{
	int c;
	struct node *prev;
}node;

void push(int c, node **h)
{
	node *tmp;
	tmp = (node *)malloc(sizeof(tmp));
	tmp->c = c;
	tmp->prev = *h;
	*h = tmp;
}

int pop (node **h)
{
	int n;
	node *t;
	n = (*h)->c;
	t = (*h);
	(*h) = (*h)->prev;
	t->prev = NULL;
	return n;

}

int isEmpty( node *h )
{
	if ( h->prev == NULL)
		return 1;
	else 
		return 0;
}

int main()
{
	int t, i,n1,n2,flag, ans, par_ans, len;
	char s[101];
	scanf("%d", &t);
	node *head;
	head = (node *)malloc(sizeof(node));
	head->prev = NULL;
	while ( t > 0 )
	{
		getchar();
		scanf("%[^\n]", s);
		len = strlen(s);
		for ( i = len - 1 ; i >= 0 ; i-- )
		{
			if (s[i]-'0' <= 9 && s[i]-'0' >= 0)
			{
				push(s[i]-'0', &head);
			}
			else
			{
				flag = 0;
				if (!isEmpty(head))
					n2 = pop(&head);
				if (!isEmpty(head))
				{
					n1 = pop(&head);
					flag = 1;
				}
				if ( flag == 1 )
				{
					switch (s[i])
					{
						case '/':
							par_ans = n2/n1;
							push(par_ans, &head);
							break;
						case '*':
							par_ans = n1 * n2;
							push(par_ans, &head);
							break;
						case '-':
							par_ans = n2 - n1;
							push(par_ans, &head);
							break;
						case '+':
							par_ans = n1 + n2;
							push(par_ans, &head);
							break;
						case '^':
							par_ans = pow(n2,n1);
							push(par_ans, &head);
							break;			
					}
				}
				else
					break;
			}
		}
		if(!isEmpty(head))
			ans = pop(&head);
		if (isEmpty(head) && flag == 1)
			printf("%d\n", ans );
		else
			printf("invalid\n");
		t--;
	}
	return 0;
}
