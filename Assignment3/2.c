#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
	int num;
	int gener;
} node;

void print(node *tree, int n)
{
	int i, x = 4;
	printf("(%d,%d)\n", tree[1].num, tree[1].gener);
	for (i = 2; i < n + 1; i++)
	{
		if (i >= x)
		{
			x = x * 2;
			printf("\n");
		}
		printf("(%d,%d)  ", tree[i].num,tree[i].gener);
	}
	return;
}

void make_tree(node *tree, int n)
{
	int i, x = 4, c = 1;
	tree[1].num = 1;
	tree[1].gener = 0;
	for (i = 2; i < n + 1; i++)
	{
		if (i >= x)
		{
			x = x * 2;
			c++;
		}
		tree[i].num = i;
		tree[i].gener = c;
	}
	return;
}

int descendant(node *tree, int a, int b)
{
	while ( a!=b )
	{
		a = a / 2;
		b = b / 2;
	}
	return a;
}

int gener_level(node *tree, int a, int b)
{
	int d;
	if (a > b)
	{
		while(tree[a].gener != tree[b].gener)
			a = a / 2;
	}
	else
	{
		while(tree[a].gener != tree[b].gener)
			b = b / 2;
	}
	if (a == 1 || b == 1)
		return 1; 
	d = descendant(tree, a, b);
	return d;
}

int main()
{
	int t, n, a, b, out;
	scanf("%d",&t);
	while(t--)
	{
		node *tree;
		scanf("%d%d%d", &n, &a, &b);
		n = pow(2, n) - 1;
		tree = (node *)malloc(sizeof(node)*(n + 1));
		make_tree(tree, n);
		//print(tree, n);
		out = gener_level(tree, a, b);
		printf("%d\n", out);
		free(tree);
	}
	return 0;
}