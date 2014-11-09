#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int d;
	struct node *repr;
	struct node *next;
	int len;

} node;

typedef struct edge
{
	int wt;
	int v1;
	int v2;
	int flag;
} edge;

node **arr;
edge *edg;

int cmp (const void *a, const void *b)
{
	return ((edge *)a)->wt - ((edge *)b)->wt;
}

void union_set (int v1, int v2)
{
	node *t;
	if (arr[v1]->len >= arr[v2]->len)
	{
		t = arr[v2];
		while(t != NULL)
		{
			t->repr = arr[v1];
			t = t->next;
		}
		t = arr[v1];
		while(t->next != NULL)
			t = t->next;
		t->next = arr[v2];
		arr[v1]->len += arr[v2]->len;
	}
	else
	{
		t = arr[v1];
		while(t != NULL)
		{
			t->repr = arr[v2];
			t = t->next;
		}
		t = arr[v2];
		while(t->next != NULL)
			t = t->next;
		t->next = arr[v1];
		arr[v2]->len += arr[v1]->len;
	}
}

int find (int a)
{
	return arr[a]->repr->d;
}

int main()
{
	int t, v, e, i, rep1, rep2;
	scanf("%d", &t);
	while (t > 0)
	{
		scanf("%d%d", &v, &e);
		arr = (node **)malloc(sizeof(node *) * v);
		for (i = 0; i < v; i++)
		{
			arr[i] = (node *)malloc(sizeof(node));
			arr[i]->next = NULL;
			arr[i]->repr = arr[i];
			arr[i]->len = 1;
			arr[i]->d = i;
		}
		edg = (edge *)malloc(sizeof(edge) * e);
		for (i = 0; i < e; i++)
		{
			scanf("%d%d%d", &edg[i].v1,&edg[i].v2, &edg[i].wt);
			edg[i].flag = 0;
		}
		qsort(edg, e, sizeof(edg[0]), cmp);
		int max = 0;
		i = 0;
		while(max != v - 1)
		{
			rep1 = find(edg[i].v1);
			rep2 = find(edg[i].v2);
			if (rep1 != rep2)
			{
				union_set(rep1, rep2);
				edg[i].flag = 1;
				max++;
			}
			i++;
		}
		for (i = 0; i < e; i++)
			if (edg[i].flag == 1)
				printf("%d %d %d\n", edg[i].v1, edg[i].v2, edg[i].wt);
		t--;
	}
	return 0;
}