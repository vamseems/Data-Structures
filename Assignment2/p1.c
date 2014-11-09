#include <stdio.h>
#include <stdlib.h>

int n;

typedef struct node
{
	char c;
	struct node *next;
	struct node *prev;
}node;

void print( node **order)
{
	int i,j,flag=0;
	node *t;
	for (i=0;i<n;i++)
	{
		flag=0;
		t=order[i];
		while(t->next!=NULL)
		{
			t=t->next;
		}
		while (t!=NULL)
		{
			if(t->c == '0' && flag == 0 && t->prev!=NULL)
			{}
			else
			{
				flag=1;
				printf("%c", t->c);
			}
			t=t->prev;
		}
		if(i!=n-1)
		printf(" ");
	}
	printf("\n");
}

node* insert(char c, node *h)
{
	node *t;
	t = (node *)malloc(sizeof(node));
	t->next = NULL;
	t->prev = NULL;
	t->c = c;
	if (h == NULL)
	{
		h = t;
	}
	else
	{
		t->next = h;
		h->prev = t;
		h = t;
	}
	return h;
}

node* insert1(char c, node *h)
{
	node *t;
	t = (node *)malloc(sizeof(node));
	t->next = NULL;
	t->prev = NULL;
	t->c = c;
	while(h->next!=NULL)
	{
		h = h->next;
	}
	h->next	= t;
	t->prev = h;
	return h;
}

node ** next (node **order)
{
	int i, flag= 0;
	for (i=0;i<n;i++)
	{
		flag = 0;
		if (order[i]->next == NULL)
		{
			if (order[i]->c == '0')
				flag = 1;
			else
				order[i]=insert1('0',order[i]);
		}
		if (flag == 0)
		order[i] = order[i]->next;
	}
	return order;
}

node ** counting_sort(node **order)
{
	int *arr;
	node **result;
	arr = (int *)calloc(10,sizeof(int));
	result = (node **)malloc(sizeof(node *)*n);
	int i;
	for (i=0;i<n;i++)
	{
		arr[((order[i])->c)-'0']++;
	}
	for (i=1;i<10;i++)
	{
		arr[i]=arr[i]+arr[i-1];
	}
	for (i=n-1;i>=0;i--)
	{
	//	printf("\t%d\t%c\n",arr[order[i]->c-'0']-1,order[i]->c);
		result[arr[order[i]->c-'0']-1] = order[i];
		arr[order[i]->c-'0']--;
	}
	//printf("-------------------------\n");
	return result;
}

int main()
{
	int tc, i,digits,max,k;
	char c;
	scanf("%d", &tc);
	while (tc>0)
	{
		max=0;
		node **order;
		scanf("%d", &n);
		getchar();
		order = (node **)malloc(sizeof(node *)*n);
		for (i = 0; i < n; i++)
		{
			digits=0;
			order[i]=NULL;
			while (c=getchar())
			{
				if (c != '\n' && c!=' ')
				{
					order[i]=insert(c, order[i]);
					digits++;
				}
				else
					break;
			}
			if (digits > max)
				max = digits;
		}
		scanf("%d", &k);
		for (i=0;i<k;i++)
		{
			order = counting_sort(order);
			order = next(order);
		}
		print(order);
		tc--;
		free(order);
	}
	return 0;
}