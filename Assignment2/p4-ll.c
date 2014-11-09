#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int power;
	int coeff;
	struct node *next;
}node;

node * insert(node * start,int e,int c)
{
	int state = 0;
	node * temp = start;
	if(start==NULL)
	{
		temp=(node *)malloc(sizeof(node));
		temp -> power = e;
		temp -> coeff = c;
		temp -> next = NULL;
		start = temp;
		return start;
	}
	else
	{
		state = 0;
		node * prev = start;
		node * new = (node *)malloc(sizeof(node));
		new -> power = e;
		new -> coeff = c;
		new -> next = NULL;
		while(start!=NULL)
		{
			if(e > start->power)
			{
				state = 1;
				if(start==prev)
				{
					new->next = start;
					temp = new;
					break;
				}
				else
				{
					new->next=start;
					prev->next = new;
					break;
				}
			}
			else if(e == start->power)
			{
				start->coeff = start->coeff + c;
				break;
			}
			prev = start;
			start=start->next;
		}
		if(state==0 && start==NULL)
		{
			prev->next=new; 
		}
		return temp;
	}
}
void print(node * hell)
{
	node *t;
	t = hell;
	int count=0;
	while (t != NULL)
	{
		if (t->coeff != 0 )
			count++;
		t=t->next;
	}
	printf("%d\n", count);
	while(hell!=NULL)
	{
		if (hell->coeff != 0 )
			printf("%d %d\n",hell->power,hell->coeff);
		hell = hell -> next;
	}
}
int main()
{
	int tc,m,n,i, flag=0,p,c;
	scanf("%d" ,&tc);
	while (tc>0)
	{
		node * head = NULL;
		node * start = NULL;
		node * add = NULL;
		node * sub = NULL;
		node * mult = NULL;
		node * tmp;
		scanf("%d%d", &m, &n);
		
		for (i = 0; i < m; ++i)
		{
			scanf("%d %d",&p,&c);
			head=insert(head,p,c);
		}
		for (i = 0; i < n; ++i)
		{
			scanf("%d %d",&p,&c);
			start=insert(start,p,c);
		}
		tmp = head;
		for ( i = 0 ; i < m ; i++)
		{
			add=insert(add,tmp->power,tmp->coeff);
			tmp = tmp->next;
		}
		tmp = start;
		for (i = 0; i < n; ++i)
		{
			add=insert(add,tmp->power,tmp->coeff);
			tmp = tmp->next;
		}
		print(add);
		tmp = head;
		for ( i = 0 ; i < m ; i++)
		{
			sub=insert(sub,tmp->power,tmp->coeff);
			tmp = tmp->next;
		}
		tmp = start;
		for (i = 0; i < n; ++i)
		{
			sub=insert(sub,tmp->power,-1*tmp->coeff);
			tmp = tmp->next;
		}
		print(sub);
		tmp = start;
		node *t;
		for (i = 0; i < n; ++i)
		{
			t = head;
			while(t!=NULL)
			{
				mult=insert(mult,t->power+tmp->power,t->coeff*tmp->coeff);
				t = t->next;
			}
			tmp = tmp->next;
		}
		print(mult);
		tc--;
	}
	return 0;
}