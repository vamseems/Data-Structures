#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int power;
	int coeff;
}node;

int compare (const void *a, const void *b)
{
	return ((node *)b)->power - ((node *)a)->power;
}

int find (int power, node *arr, int start, int end)
{
	int m;
	if (start <= end)
	{
		m = (start+end)/2;
		if ( arr[m].power == power)
			return m;
		else if (arr[m].power > power)
			find (power, arr, m+1, end);
		else
			find (power, arr, 0, m-1);
    }
    else
    	return -1;
}

int main()
{
	int t, n, m, i, j, max, count, k;
	scanf("%d", &t);
	while (t>0)
	{
		node *poly1, *poly2;
		scanf("%d%d", &m, &n);
		poly1 = (node *)malloc(sizeof(node)*m);
		poly2 = (node *)malloc(sizeof(node)*n);
		for ( i = 0 ; i < m ; i++ )
			scanf("%d%d", &poly1[i].power, &poly1[i].coeff);
		for ( i = 0 ; i < n ; i++ )
			scanf("%d%d", &poly2[i].power, &poly2[i].coeff);
		qsort(poly1, m, sizeof(node), compare);
		qsort(poly2, n, sizeof(node), compare);	
		//for ( i = 0 ; i < m ; i++ )
		//	printf("%d\t%d\n", poly1[i].power, poly1[i].coeff);
		node *add, *sub, *mult;
		add = (node *)calloc((m+n),sizeof(node));
		//if (poly1[0].power > poly2[0].power)
		//{
		max = m;
			for ( i = 0 ; i < m ; i++ )
				add[i] = poly1[i];
			for ( i = 0 ; i < n ; i++ )
			{
				j = find(poly2[i].power, add, 0, max);
				if (j ==-1 )
				{
					j = max;
					max++;
				}
				add[j].coeff = add[j].coeff + poly2[i].coeff;
				add[j].power = poly2[i].power;
			}
		//}
	/*	else
		{
			for ( i = 0 ; i < n ; i++ )
				add[i] = poly2[i];
			max = n;
			for ( i = 0 ; i < m ; i++ )
			{
				j = find(poly1[i].power, add, 0, max);
				if (j ==-1 )
				{
					j = max;
					max++;
				}
				add[j].coeff = add[j].coeff + poly1[i].coeff;
				add[j].power = poly1[i].power;
			}
		}*/
		count = 0;
		qsort(add, max, sizeof(node), compare);
		printf("%d\n", max);
		for (i=0;i<max;i++)
			printf("%d %d\n", add[i].power, add[i].coeff);
		free(add);
		sub = (node *)calloc(m+n, sizeof(node));
		for ( i = 0 ; i < m ; i++ )
			sub[i] = poly1[i];
		max = m;
		for ( i = 0 ; i < n ; i++ )
		{
			j = find(poly2[i].power, add, 0, max);
			if (j == -1)
			{
				j = max;
				max++;
			}
			sub[j].coeff = sub[j].coeff - poly2[i].coeff;
			sub[j].power = poly2[i].power;
		}
		for (i = 0; i < max ; i++)
			if (sub[i].coeff != 0)
				count++;
		qsort(sub, max, sizeof(node), compare);
		printf("%d\n", count);
		for (i = 0; i < max ; i++)
			if (sub[i].coeff != 0)
				printf("%d %d\n", sub[i].power, sub[i].coeff);
		free(sub);
		int tmp_power;
		mult = (node *)calloc(m+n, sizeof(node));
		/*for ( i = 0 ; i < m ; i++ )
		{
			mult[i]=poly1[i];
			//printf("%d  ", mult[i].power);
		}
		//printf("\n");*/
		max = 0;
		for ( i = 0 ; i < n ; i++ )
		{
			for ( k = 0; k < m ; k++ )
			{
				tmp_power = poly1[k].power + poly2[i].power;
				j = find( tmp_power , mult, 0 , max );
			//	printf("\tpow=%d\tj=%d\n", tmp_power, j);
				if ( j ==-1 )
				{
					j = max;
					max++;
				}
				mult[j].coeff = mult[j].coeff + (poly1[k].coeff*poly2[i].coeff);
				mult[j].power =  tmp_power;
				qsort(mult, max, sizeof(node), compare);
			}
			//m = max;
		}
		count = 0;
		for (i = 0; i < max ; i++)
			if (mult[i].coeff != 0)
				count++;
		printf("%d\n", count);
		for (i = 0; i < max ; i++)
			if (mult[i].coeff != 0)
				printf("%d %d\n", mult[i].power, mult[i].coeff);
		//free(mult);
		t--;
	}
	return 0;
}