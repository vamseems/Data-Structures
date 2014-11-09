#include <stdio.h>
#include <stdlib.h>

int j = 1;
int k = 1;

void check_max_heap(int *max_heap, int start)
{
	int parent;
	parent = start / 2;
	while ( start != 1 )
	{
		if (max_heap[parent] < max_heap[start])
		{
			int tmp;
			tmp = max_heap[start];
			max_heap[start] = max_heap[parent];
			max_heap[parent] = tmp;
		}
		start = parent;
		parent = start / 2;
	}
	return;
}

void check_min_heap(int *min_heap, int start)
{
	int parent;
	parent = start / 2;
	while ( start != 1 )
	{
		if (min_heap[parent] > min_heap[start])
		{
			int tmp;
			tmp = min_heap[start];
			min_heap[start] = min_heap[parent];
			min_heap[parent] = tmp;
		}
		start = parent;
		parent = start / 2;
	}
	return;
}


int delete_min_heap(int *heap)
{
	int out = heap[1];
	heap[1] = heap[k - 1];
	k--;
	int i = 1;
	while (1)
	{
		if ((2*i) + 1 <= k)
		{
			if (heap[i] > heap[2*i] || heap[i] > heap[(2*i) + 1])
			{
				if (heap[2*i] < heap[(2*i) + 1])
				{
					int tmp;
					tmp = heap[i];
					heap[i] = heap[2*i];
					heap[2*i] = tmp;
					i = 2 * i;
				}
				else
				{
					int tmp;
					tmp = heap[i];
					heap[i] = heap[(2*i) + 1];
					heap[(2*i) + 1] = tmp;
					i = (2 * i) + 1;
				}
			}
			else
				break;
		}
		else
		{
			if (2*i <= k)
			{
				if(heap[i] > heap[2*i])
				{
					int tmp;
					tmp = heap[i];
					heap[i] = heap[2*i];
					heap[2*i] = tmp;
					i = 2 * i;	
				}
				else
					break;
			}
		}
		if (2 * i > k && (2 * i) + 1 > k)
			break;
	}
	return out;
}


int delete_max_heap(int *heap)
{
	int out = heap[1];
	heap[1] = heap[j - 1];
	j--;
	int i = 1;
	while (1)
	{
		if ((2*i) + 1 <= j)
		{
			if (heap[i] < heap[2*i] || heap[i] < heap[(2*i) + 1])
			{
				if (heap[2*i] > heap[(2*i) + 1])
				{
					int tmp;
					tmp = heap[i];
					heap[i] = heap[2*i];
					heap[2*i] = tmp;
					i = 2 * i;
				}
				else
				{
					int tmp;
					tmp = heap[i];
					heap[i] = heap[(2*i) + 1];
					heap[(2*i) + 1] = tmp;
					i = (2 * i) + 1;
				}
			}
			else
				break;
		}
		else
		{
			if (2*i <= j)
			{
				if(heap[i] < heap[2*i])
				{
					int tmp;
					tmp = heap[i];
					heap[i] = heap[2*i];
					heap[2*i] = tmp;
					i = 2 * i;	
				}
				else
					break;
			}
		}
		if (2 * i > j && (2 * i) + 1 > j)
			break;
	}
	return out;
}

int main()
{
	int t, choice, num, count = 0;
	scanf("%d", &t);
	int *max_heap, *min_heap;
	min_heap = (int *)calloc(t + 1, sizeof(int));
	max_heap = (int *)calloc(t + 1, sizeof(int));
	while (t > 0)
	{	
		scanf("%d", &choice);
		if (choice == 1)
		{
		//	printf("j is %d\n",j);
			if (count >= 4)
				printf("%d\n", min_heap[1]);				
			else
				printf("-1\n");
		}
		else if (choice == 2)
		{
			scanf("%d", &num);
			count++;
			if (count < 4)
			{
				if (count % 4 != 0)
				{
					max_heap[j] = num;
					check_max_heap(max_heap, j);
					j++;
				}
				else
				{
					if (num >= max_heap[1])
					{
						min_heap[k] = num;
						check_min_heap(min_heap, k);
						k++;
					}
					else
					{
						min_heap[k] = delete_max_heap(max_heap);
						max_heap[j] = num;
						check_min_heap(min_heap, k);
						check_max_heap(max_heap, j);
						j++;
						k++;
					}
				}
			}
			else
			{
				if (count % 4 != 0)
				{
					if (num > min_heap[1])
					{
						max_heap[j] = delete_min_heap(min_heap);
						min_heap[k] = num;
						check_max_heap(max_heap, j);
						check_min_heap(min_heap, k);
						j++;
						k++;
					}
					else
					{
						max_heap[j] = num;
						check_max_heap(max_heap, j);
						j++;
					}
				}
				else
				{
					if (num <= max_heap[1])
					{
						min_heap[k] = delete_max_heap(max_heap);
						max_heap[j] = num;
						check_max_heap(max_heap, j);
						check_min_heap(min_heap, k);
						k++;
						j++;
					}
					else
					{
						min_heap[k] = num;
						check_min_heap(min_heap, k);
						k++;
					}	
				}
			}

		}
		t--;
	}
	return 0;
}
