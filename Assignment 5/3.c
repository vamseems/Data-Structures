#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int d;
	int parent;
} node;

int *max, *tmp, **adj, j = 0, v;
node *arr;

void DFS (int s)
{
	int i;
	for (i = 0;i < v; i++)
	{
		if (adj[s][i] != 0)
		{
			if (tmp[i] < tmp[s] + adj[s][i])
			{
				tmp[i] = max[s] + adj[s][i];
				arr[i].parent = s;
			}
			if (tmp[i] > max[i])
				max[i] = tmp[i];
			DFS(i);	
		}
	}
	return;
}

int main()
{
	int t, e, i, v1, v2, w, s;
	scanf("%d", &t);
	while (t > 0)
	{
		j = 0;
		scanf("%d%d", &v, &e);
		adj = (int **)calloc(v, sizeof(int *));
		tmp = (int *)calloc(v, sizeof(int));
		max = (int *)calloc(v, sizeof(int));
		for (i = 0; i < v; i++)
			adj[i] = (int *)calloc(v, sizeof(int));
		for (i = 0; i < e; i++)
		{
			scanf("%d%d%d", &v1, &v2, &w);
			adj[v1][v2] = w;
		}
		arr = (node *)malloc(sizeof(node) * v);
		for (i = 0; i < v; i++)
		{
			arr[i].d = i;
			arr[i].parent = -1;
		}
		scanf("%d", &s);
		DFS(s);



		for (i = 0; i < v - 1; i++)
		{
			if (i == s)
				printf("0 ");
			else if (max[i] != 0 )
				printf("%d ",max[i] );
			else
				printf("INF ");
		}
		if (s == v-1)
			printf("0\n");
		else if (max[i] != 0 )
			printf("%d\n",max[i] );
		else
			printf("INF\n");
		t--;
	}
	return 0;
}