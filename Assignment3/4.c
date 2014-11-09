#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int d;
	struct node *prev;
	struct node *rc;
	struct node *lc;
	char child;
	int ht;
} node;

int global_flag = 0, n;
node *ir = NULL;

void print(node *root)
{
	if (root == NULL)
		return;
	print(root->lc);
	printf("(%d,%d)  ", root->d, root->ht);
	print(root->rc);
	return;
}

void insert(node *root)
{
	node *tmp, *curr, *prev;
	int num;
	tmp = (node *)malloc(sizeof(node));
	scanf("%d", &(tmp->d));
	num = tmp->d;
	tmp->rc = NULL;
	tmp->lc = NULL;
	curr = root;
	while (curr != NULL)
	{
		prev = curr;
		if (num > curr->d)
			curr = curr->rc;
		else if (num < curr->d)
			curr = curr->lc;
		else
			return;
	}
	tmp->prev = prev;
	tmp->ht = prev->ht + 1;
	if (num > prev->d)
	{
		prev->rc = tmp;
		tmp->child = 'r';
	}
	else
	{
		prev->lc = tmp;
		tmp->child = 'l';
	}
	return;
}

node* find(node *root, int myNode)
{
	while (root != NULL)
	{
		if (myNode > root->d)
			root = root->rc;
		else if (myNode < root->d)
			root = root->lc;
		else
			return root;
	}
	return root;
}

void kMin(node *IR, int k, int *arr, int *j)
{
	if (global_flag == 1)
		return;
	if (IR == NULL)
		return;
	kMin(IR->lc, k, arr, j);
	if (*j < k)
	{
		arr[*j] = IR->d;
		(*j)++;
	}
	else
	{
		global_flag = 1;
		return;
	}
	if (global_flag == 1)
		return;
	kMin(IR->rc, k, arr, j);
}

int findIR(node *curr, int level, int *lvl, int *i)
{
	if (curr == NULL)
		return *i;
	findIR(curr->lc,level, lvl, i);	
	//printf("\t%d\n",curr->d );

	if (curr->ht == level)
	{
		lvl[*i] = curr->d;
		(*i)++;
	}
	findIR(curr->rc,level, lvl, i);
	return *i;
}

void IRnode(node *root, int myNode, int k)
{
	node *curr, *IR;
	curr = find(root, myNode);
	if (curr == NULL)
	{
		printf("$ $\n");
		return;
	}
	else
	{
		int level, *lvl;
		level = curr->ht;
		lvl = (int *)calloc(n, sizeof(int));
		if (curr == root)
			printf("$ $\n");
		else
		{
			int j = 0, i, flag = 0;
			findIR(root, level, lvl, &j);
			//for (i = 0 ;i<n;i++)
			//printf("\"%d\"", j);
			if (j > 1)
			{
				for (i = 0; i < j; i++)
				{
					if(lvl[i] == myNode)
					{
						flag = 1;
						break;
					}
				}
				if (flag == 1 && i+1 < j)
					ir = find(root, lvl[i+1]);	
				else
					ir = NULL;
			}
			else
				ir = NULL;
			IR = ir;
			if (IR == NULL)
				printf("$ $\n");
			else
			{
				printf("%d ", IR->d);
				global_flag = 0;
				j = 0;
				int *arr;
				arr = (int *)calloc(k,sizeof(int));
				kMin(IR, k, arr, &j);
				//for(i = 0;i<k;i++)
				//printf("\"%d\" ",arr[i] );
				if (arr[k-1] != 0)
					printf("%d\n", arr[k-1]);
				else
					printf("$\n");
			}
		}
	}
	return;
}

int main()
{
	int t,  myNode, k, i;
	scanf("%d", &t);
	while (t--)
	{
		node *root;
		global_flag = 0;
		ir = NULL;
		root = (node *)malloc(sizeof(node));
		root->prev = NULL;
		root->rc = NULL;
		root->lc = NULL;
		root->child = '0';
		root->ht = 0;
		scanf("%d", &n);
		scanf("%d", &(root->d));
		for (i = 1; i < n; i++)
			insert(root);
		scanf("%d%d", &myNode, &k);
		//print(root);
		//printf("\n");
		IRnode(root, myNode, k);
		
	}
	return 0;
}