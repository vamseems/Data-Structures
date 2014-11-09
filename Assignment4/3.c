#include <stdio.h>
#include <stdlib.h>

#define VISITED 1
#define NOT_VISITED 0
#define IN_PROGRESS -1

int main()
{
	int t, n, **adj, l, i, j, max, flag, k;
	scanf("%d", &t);
	while (t > 0)
	{
		max = 0;
		scanf("%d", &n);
		adj = (int **)malloc(sizeof(int *) * n);
		for (i = 0; i < n; i++)
			adj[i] = (int *)malloc(sizeof(int) * n);
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				scanf("%d", &adj[i][j]);
		int *state, m, *queue, count = 0;
		k = 0;
		state = (int *)calloc(n, sizeof(int));
		queue = (int *)malloc(sizeof(int) * n);
		while(1)
		{
			flag = 1;
			i = 0;
			k = 0;
			count = 0;
			while (state[i] != NOT_VISITED)
				i++;
			queue[k] = i;
			state[i] = IN_PROGRESS;
			k++;
			m = 0;
			for (l = i; m < k; m++)
			{
				for (j = 0; j < n; j++)
				{
					if (adj[l][j] == 1)
					{
						if (state[j] == NOT_VISITED)
						{
							queue[k] = j;
							state[j] = IN_PROGRESS;
							k++;
						}
					}
				}
				state[l] = VISITED;
				count++;
				//printf("%d.)\t%d\n", count, l);
				l = queue[m+1];
			}
			if (count > max)
				max = count;
			for (j = 0; j < n; j++)
				if (state[j] == NOT_VISITED)
					flag = 0;
			if (flag == 1)
			{
				printf("%d\n", max);
				break;
			}

		}
		t--;
	}
	return 0;
}