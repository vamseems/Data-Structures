#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	long long int d;
	long long int sum;
} node;

int main()
{
	int t, n, i, num, j, N;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		node *arr, *out;
		arr = (node *)malloc(sizeof(node) * n);
		out = (node *)malloc(sizeof(node) * n);
		for (i = 0 ; i < n ; i++)
		{
			scanf("%lld", &arr[i].d);
			arr[i].sum = 0;
		}
		i = 0;
		j = 0;
		N = n;
		while(n)
		{
			num = arr[j].d;
			if (num < 0)
			{
				if (i-1 >= 0)
					if (out[i-1].d > num)
						break;
				out[i] = arr[j];
				i++;
				j++;
			}	
			else
			{
				if (i == 0)
					break;
				else if (i-1 >= 0 && out[i-1].d * -1 != num)
					break;
				else
				{
					if (i-2 >= 0)
						out[i-2].sum += num;
					if(i-1 >= 0)
						if (out[i-1].sum >= -1 * out[i-1].d)
							break;
						else
						{
							out[i-1].sum = 0;
							out[i-1].d = 0;
						}
					i--;
					j++;
				}
			}
			if (i == 0 && j != N)
				break;
			n--;
		}
		if (n == 0)
			printf(":-) Matrioshka!\n");
		else
			printf(":-( Try again.\n");
	}
	return 0;
}