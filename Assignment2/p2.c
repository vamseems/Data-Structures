#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
	char c;
	struct node *prev;
} node;

void push(char c, node **h)
{
	node *tmp;
	tmp = (node *)malloc(sizeof(node));
	tmp->prev = (*h);
	tmp->c = c;
	(*h) = tmp;
	return;
}

char pop(node **h)
{
	char c;
	c = (*h)->c;
	(*h) = (*h)->prev;
	return c;
}

int isEmpty(node *h)
{
	if (h->prev == NULL && h->c == '\0')
		return 1;
	else
		return 0;
}

int main()
{
	int t, i, j, len,op_count, flag = 0, count;
	scanf("%d", &t);
	char s[1000];
	while (t > 0)
	{
		getchar();
		op_count = 0;
		flag = 0;
		count = 0;
		node *head;
		char *out;
		head = (node *)malloc(sizeof(node));
		head->prev = NULL;
		head->c ='\0';
		scanf("%s", s);
		len = strlen(s);
		out = (char *)malloc(sizeof(char)*len);
		for ( i = 0 ; i < len ; i++ )
		{
			if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
				op_count--;
			else if (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^' && s[i] != '(' && s[i] != ')')
				op_count++;
			if (s[i] == ')')
				count++;
			else if (s[i] == '(')
				count--;
			if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
			{
				if (i < len - 1)
				{
					if (s[i+1] == '+' || s[i+1] == '-' || s[i+1] == '/' || s[i+1] == '*' || s[i+1] == '^')
					{
						flag = 1;
						break;
					}
				}
			}
			if (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^' && s[i] != '(' && s[i] != ')')
			{
				if (i<len-1)
				{
					if (s[i+1] != '+' && s[i+1] != '-' && s[i+1] != '*' && s[i+1] != '/' && s[i+1] != '^' && s[i+1] != '(' && s[i+1] != ')')
					{
						flag =1;
						break;
					}
			    }
			}
		}
		if (s[0]==')' || s[len-1]=='(')
			flag = 1;
		if (op_count <= 0)
			flag = 1;
		if (count != 0)
			flag = 1;
		if (flag == 0)
		{
			j = len -1;
			for (i = len-1 ; i >= 0 ; i--)
			{
				if (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^' && s[i] != '(' && s[i] != ')')
				{
					out[j] = s[i];
					j--;
				}	
				else if (s[i] == '+')
				{
					while (head->c != '+' && head->c != '-' && head->c != ')' && !isEmpty(head))
					{
						out[j] = pop(&head);
						j--;
					}
					push(s[i], &head);
				}
				else if (s[i] == '-')
				{
					while (head->c != '+' && head->c != '-' && head->c != ')' && !isEmpty(head))
					{
						out[j] = pop(&head);
						j--;
					}
					push(s[i], &head);
				}
				else if (s[i] == '*')
				{
					while (head->c == '^' && !isEmpty(head))
					{
						out[j] = pop(&head);
						j--;
					}
					push(s[i], &head);
				}
				else if (s[i] == '/')
				{
					while (head->c == '^' && !isEmpty(head))
					{
						out[j] = pop(&head);
						j--;
					}
					push(s[i], &head);
				}
				else if (s[i] == '^')
				{
					while (head->c == '^' && !isEmpty(head))
					{
						out[j] = pop(&head);
						j--;
					}
					push(s[i], &head);
				}
				else if (s[i] == ')')
				{
					push(s[i], &head);
				}
				else if (s[i] == '(')
				{
					while (head->c != ')' && !isEmpty(head))
					{
						out[j] = pop(&head);
						j--;	
					}
					pop(&head);
				}
			}
		}
		while (flag == 0 && !isEmpty(head))
		{
			out[j] = pop(&head);
			j--;
		}
		if (flag == 1)
			printf("invalid");
		else
		{
			for (i = j+1 ; i < len ; i++)
			{
				printf("%c", out[i]);
			}
		}
		printf("\n");
		free(out);
		free(head);
		t--;
	}
	return 0;
}