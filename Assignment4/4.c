#include <stdio.h>
#include <stdlib.h>

int *paths, n;

findpath(int **adj, int i)
{
	if (i == n-1)
		return;
}

int main()
{
	int t, r, i, u, v, w;
	scanf("%d", &t);
	while (t > 0)
	{
		scanf("%d%d", &n, &r);
		int **adj;
		paths = (int *)calloc(r, sizeof(int));
		adj = (int **)calloc(n, sizeof(int *));
		for (i = 0; i < n; i++)
			adj[i] = (int *)calloc(n, sizeof(int));
		for (i = 0; i < r; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			adj[u-1][v-1] = w;
			adj[v-1][u-1] = w;
		}
		findpath(adj, 0);
		t--;
	}
	return 0;
}