#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int d;
	int start;
	int finish;
	int state;
} node;

int v, timed, **adj;
node *arr;

int cmp (const void * a, const void * b)
{
   return (((node*)b)->finish - ((node*)a)->finish)  ;
}

int find(int a)
{
	int i;
	for (i = 0 ; i < v ; i++)
	{
		if (arr[i].d == a)
			return i;
	} 
}

void DFS(int u)
{
	int i;
	for(i = 0; i < v; i++)
	{
		if (adj[u][i] == 1)
		{
			if (arr[i].state == -1)
			{
				arr[i].state = 0;
				arr[i].start = timed++;
				DFS(i);
			}
		}
	}
	arr[u].state = 1;
	arr[u].finish = timed++;
	return;
}

void DFS1(int u)
{
	int i, j;
	for(i = 0; i < v; i++)
	{
		if (adj[i][u] == 1)
		{
			j = find(i);
			if (arr[j].state == -1)
			{
				arr[j].state = 0;
				DFS1(i);
			}
		}
	}
	arr[j].state = 1;
	return;
}

int main()
{
	int t, e, i, v1, v2;
	scanf("%d", &t);
	while (t > 0)
	{
		scanf("%d%d", &v, &e);
		adj = (int **)malloc(sizeof(int *) * v);
		for (i = 0; i < v; i++)
			adj[i] = (int *)calloc(v, sizeof(int));
		for (i = 0; i < e; i++)
		{
			scanf("%d%d", &v1, &v2);
			adj[v1][v2] = 1;
		}
		arr = (node *)calloc(v, sizeof(node));
		for (i = 0; i < v; i++)
		{
			arr[i].d = i;
			arr[i].state = -1;
		}
		timed = 1;
		for (i = 0; i < v; i++)
		{
			if (arr[i].state == -1)
			{
				arr[i].state = 0;
				arr[i].start = timed++;
				DFS(i);
			}
		}
		qsort(arr, v, sizeof(node), cmp);
		for (i = 0; i < v; i++)
		{
			arr[i].state = -1;
		}
		int count = 0;
		for (i = 0; i < v; i++)
		{
			if (arr[i].state == -1)
			{
				arr[i].state = 0;
				DFS1(arr[i].d);
				count++;
			}
		}
		printf("%d\n", count);
		t--;
	}
	return 0;
}