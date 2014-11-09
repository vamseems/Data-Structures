#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int d;
	struct node *lc;
	struct node *rc;
}node;

int count;

void inOrder(int *inp_inorder, int n)
{
	int i;
	printf("%d", inp_inorder[0]);
	for (i = 1; i < n; i++)
		printf(" %d", inp_inorder[i]);
	printf("\n");
}

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

int main()
{
	int t, n, *inp_inorder, *inp_preorder, i, req_root;
	node *root, *curr, *prev;
	scanf("%d", &t);
	while (t > 0)
	{
		scanf("%d", &n);
		inp_inorder = (int *)malloc(sizeof(int) * n);
		inp_preorder = (int *)malloc(sizeof(int) * n);
		root = (node *)malloc(sizeof(node));
		root->rc = NULL;
		root->lc = NULL;
		for (i = 0; i < n; i++)
			scanf("%d", &inp_preorder[i]);
		for (i = 0; i < n; i++)
			scanf("%d", &inp_inorder[i]);
		scanf("%d", &req_root);
		root->d = inp_preorder[0];
		for (i = 1; i < n; i++)
		{
			node *tmp;
			tmp = (node *)malloc(sizeof(node));
			tmp->lc = NULL;
			tmp->rc = NULL;
			tmp->d = inp_preorder[i];
			curr = root;
			while (curr != NULL)
			{
				if (tmp->d > curr->d)
				{
					prev = curr;
					curr = curr->rc;
				}
				else if (tmp->d < curr->d)
				{
					prev = curr;
					curr = curr->lc;
				}
			}
			if (tmp->d > prev->d)
				prev->rc = tmp;
			else if(tmp->d < prev->d)
				prev->lc = tmp;
		}
		node *tmp;
		while (root->d != req_root)
		{
			curr = root;
			while(curr->d != req_root)
			{
				if (req_root > curr->d)
				{
					prev = curr;
					curr = curr->rc;
				}
				else if (req_root < curr->d)
				{
					prev = curr;
					curr = curr->lc;
				}
			}
			if (prev == root)
			{
				if (root->rc == curr)
				{
					tmp = curr->lc;
					curr->lc = prev;
					prev->rc = tmp;
					root = curr;
				}
				else
				{
					tmp = curr->rc;
					curr->rc = prev;
					prev->lc = tmp;
					root = curr;
				}
			}
			else
			{
				node *parent;
				tmp = root;
				while(tmp->d != prev->d)
				{
					parent = tmp;
					if (prev->d > tmp->d)
						tmp = tmp->rc;
					else if(prev->d < tmp->d)
						tmp = tmp->lc;
				}
				if (parent->rc == prev)
				{
					if (prev->rc == curr)
					{
						tmp = curr->lc;
						curr->lc = prev;
						prev->rc = tmp;
						parent->rc = curr;
					}
					else
					{
						tmp = curr->rc;
						curr->rc = prev;
						prev->lc = tmp;
						parent->rc = curr;
					}
				}
				else if (parent->lc == prev)
				{
					if (prev->rc == curr)
					{
						tmp = curr->lc;
						curr->lc = prev;
						prev->rc = tmp;
						parent->lc = curr;
					}
					else
					{
						tmp = curr->rc;
						curr->rc = prev;
						prev->lc = tmp;
						parent->lc = curr;
					}
				}
			}
		}
		inOrder(inp_inorder, n);
		preOrder(root, root);
		printf("\n");
		count = 0;
		postOrder(root, root);
		printf("\n");
		t--;
	}
	return 0;
}