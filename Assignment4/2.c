#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int d;
	struct node *lc;
	struct node *rc;
} node;

int n, count;

void preOrder(node *root, node *first)
{
	if (root == NULL)
		return;
	if (root == first)
		printf("%d", root->d);
	else
		printf(" %d", root->d);
	preOrder(root->lc, first);
	preOrder(root->rc, first);
}

void postOrder(node *root, node *first)
{
	if (root == NULL)
		return;
	postOrder(root->lc, first);
	postOrder(root->rc, first);
	if (count == 0)
		printf("%d", root->d);
	else
		printf(" %d", root->d);
	count++;
}

int findMin(int *inp, int start, int end)
{
	int i, min;
	min = start;
	for (i = start; i <= end; i++)
	{
		if (inp[i] < inp[min])
			min = i;
	}
	return min;
}

void makeTree(node *head, int *inp, int start, int end, int flag)
{
	int min_index;
	if (start > end)
		return;
	min_index = findMin(inp, start, end);
	if (start == 0 && end == n-1)
	{
		head->d = inp[min_index];
		head->lc = NULL;
		head->rc = NULL;
		makeTree(head, inp, start, min_index - 1, 0);
		makeTree(head, inp, min_index + 1, end, 1);
	}
	else if (flag == 0)
	{
		node *tmp;
		tmp = (node *)malloc(sizeof(node));
		tmp->d = inp[min_index];
		tmp->lc = NULL;
		tmp->rc = NULL;
		head->lc = tmp;
		makeTree(head->lc, inp, start, min_index - 1, 0);
		makeTree(head->lc, inp, min_index + 1, end, 1);
	}
	else if (flag == 1)
	{
		node *tmp;
		tmp = (node *)malloc(sizeof(node));
		tmp->d = inp[min_index];
		tmp->lc = NULL;
		tmp->rc = NULL;
		head->rc = tmp;
		makeTree(head->rc, inp, start, min_index - 1, 0);
		makeTree(head->rc, inp, min_index + 1, end, 1);
	}
}	


int main()
{
	int t, i, *inp;
	node *root = NULL;
	scanf("%d", &t);
	while (t > 0)
	{
		scanf("%d", &n);
		inp = (int *)malloc(sizeof(int) * n);
		for (i = 0; i < n; i++)
			scanf("%d", &inp[i]);
		root = (node *)malloc(sizeof(node));
		root->lc = NULL;
		root->rc = NULL;
		makeTree(root, inp, 0, n-1, 0);
		count = 0;
		preOrder(root, root);
		printf("\n");
		count = 0;
		postOrder(root, root);
		printf("\n");
		t--;
	}
	return 0;
}