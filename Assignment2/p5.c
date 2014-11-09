#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int h;
	struct node *next;
	struct node *prev;
}node;

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main()
{
	int n, i, k, k_tmp;
	node *head,*tail, *t;
	head = (node *)malloc(sizeof(node));
	head->next = NULL;
	head->prev = NULL;
	int te;
	scanf("%d", &te);
	while (te>0)
	{
	scanf("%d", &n);
	tail = head;
	int *tmp;
	tmp = (int *)malloc(sizeof(int)*n);
	for ( i=0 ; i<n ; i++ )
		scanf("%d", &tmp[i]);
	qsort(tmp, n, sizeof(int), compare);
	head->h = tmp[0];
	//printf("%d ", tmp[0]);
	for ( i = 1; i < n; i++)
	{
		tail->next = (node *)malloc(sizeof(node));
		t = tail;
		tail = tail->next;
		tail->h = tmp[i];
		//printf("%d ", tmp[i]);
		tail->next = NULL;
		tail->prev = t;
	}
	//printf("\n");
	tail->next = head;
	head->prev = tail;
	free(tmp);
	scanf("%d", &k);
	k_tmp = k;
	tail = head;
	while ( n!=1 )
	{
		k = k_tmp;
		if ( k > n)
		{
			k = k % n;
		}
		if (k == 0)
		{
			tail = tail->prev;
		}
		for ( i = 1 ; i < k ; i++ )
		{
			tail = tail->next;
		}
		tail->prev->next = tail->next;
		tail->next->prev = tail->prev;
		t = tail;
		//printf("\t%d\n", tail->h);
		tail = tail->next;
		t->next=NULL;
		t->prev=NULL;
		n--;
	}
	printf("%d\n", tail->h);
	te--;
	}
	return 0;
}