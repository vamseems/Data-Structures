#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int d;
	int num;
	int low;
	int parent;
	int state;
	int flag;
} node;

int counter, **adj, points, v;
node *arr;

void AssignNum(int u)
{
	int i;
	arr[u].num = counter++;	
	arr[u].state = 1;
	for(i = 0; i < v; i++)
	{
		if (adj[u][i] == 1)
		{
			if (arr[i].state == -1)
			{
				arr[i].parent = u;
				AssignNum(i);
			}
		}
	}
	return;
}

void AssignLow(int u)
{
	int i;
	arr[u].low = arr[u].num;
	for(i = 0; i < v; i++)
	{
		if (adj[u][i] == 1)
		{
			if (arr[i].num > arr[u].num)
			{
				AssignLow(i);
				if (arr[i].low >= arr[u].num)
				{
					if (arr[u].flag == 0 && u != v-1)
					{
						if (points !=0)
							printf(" %d", arr[u].d);
						else
							printf("%d", arr[u].d);
						points++;
						arr[u].flag = 1;
					}
				}
				arr[u].low = (arr[u].low > arr[i].low)?arr[i].low:arr[u].low;
			}
			else
			{
				if (arr[u].parent != i)
				{
					arr[u].low = (arr[u].low > arr[i].num)?arr[i].num:arr[u].low;
				}
			}
		}
	}
	return;
}


int main()
{
	int t, e, i, v1, v2;
	scanf("%d",&t);
	while (t > 0)
	{
		scanf("%d%d", &v, &e);
		adj = (int **)malloc(sizeof(int *) * v);
		arr = (node *)calloc(v, sizeof(node));
		for (i = 0; i < v; i++)
		{
			adj[i] = (int *)calloc(v, sizeof(int));
			arr[i].d = i;
			arr[i].flag = 0;
			arr[i].state = -1;
		}
		for (i = 0; i < e; i++)
		{
			scanf("%d%d", &v1, &v2);
			adj[v1][v2] = 1;
			adj[v2][v1] = 1;
		}
		counter = 1;
		points = 0;
		AssignNum(v-1);
		AssignLow(v-1);
 		if (points == 0)
			printf("NONE");
		printf("\n");
		t--;
	}
	return 0;
}