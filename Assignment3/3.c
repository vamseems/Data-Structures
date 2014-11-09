#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int d;
	struct node *lc;
	struct node *rc;
	int ht;
} node;

void print(node *curr, node *root)
{
	if (curr == NULL)
		return;
	if (curr != root)
		printf(" %d", curr->d);
	print(curr->lc, root);
	print(curr->rc, root);

	return;
}

node *rotate_right(node *y)
{
	node *x = y->lc;
	node *t = x->rc;
	int ht_lc, ht_rc;

	x->rc = y;
	y->lc = t;

	if (y->lc == NULL)
		ht_lc = 0;
	else
		ht_lc = y->lc->ht;

	if (y->rc == NULL)
		ht_rc = 0;
	else
		ht_rc = y->rc->ht;

	y->ht = (ht_lc > ht_rc)?ht_lc + 1:ht_rc + 1;

	if (x->lc == NULL)
		ht_lc = 0;
	else
		ht_lc = x->lc->ht;

	if (x->rc == NULL)
		ht_rc = 0;
	else
		ht_rc = x->rc->ht;

	x->ht = (ht_lc > ht_rc)?ht_lc + 1:ht_rc + 1;

	return x;	
}

node* rotate_left(node *x)
{
	node *y = x->rc;
	node *t = y->lc;
	int ht_rc, ht_lc;

	y->lc = x;
	x->rc = t;


	if (x->lc == NULL)
		ht_lc = 0;
	else
		ht_lc = x->lc->ht;

	if (x->rc == NULL)
		ht_rc = 0;
	else
		ht_rc = x->rc->ht;

	x->ht = (ht_lc > ht_rc)?ht_lc + 1:ht_rc + 1;

	if (y->lc == NULL)
		ht_lc = 0;
	else
		ht_lc = y->lc->ht;

	if (y->rc == NULL)
		ht_rc = 0;
	else
		ht_rc = y->rc->ht;

	y->ht = (ht_lc > ht_rc)?ht_lc + 1:ht_rc + 1;

	return y;

}

int Balance(node *curr)
{
	int ht_rc, ht_lc;
	if (curr == NULL)
		return 0;

	if (curr->lc == NULL)
		ht_lc = 0;
	else
		ht_lc = curr->lc->ht;

	if (curr->rc == NULL)
		ht_rc = 0;
	else
		ht_rc = curr->rc->ht;

	return ht_lc - ht_rc;
}

node* delete(node *curr, int num)
{
	if (curr == NULL)
		return curr;

	if (num > curr->d)
		curr->rc = delete(curr->rc, num);
	else if (num < curr->d)
		curr->lc = delete(curr->lc, num);
	else
	{
		if (curr->rc == NULL && curr->lc == NULL)
		{
			curr = NULL;
		}
		else if (curr->rc == NULL || curr->lc == NULL)
		{
			node *tmp;
			if (curr->lc == NULL)
				tmp	= curr->rc;
			else
				tmp = curr->lc;

			*curr = *tmp;

			free(tmp);
		}
		else
		{
			node *tmp = NULL;
			tmp = curr->rc;
			while (tmp->lc != NULL)
				tmp = tmp->lc;

			curr->d = tmp->d;

			curr->rc = delete(curr->rc, curr->d);
		}
	}

	if (curr == NULL)
		return curr;

	int balance, ht_lc, ht_rc;

	if (curr->lc == NULL)
		ht_lc = 0;
	else
		ht_lc = curr->lc->ht;

	if (curr->rc == NULL)
		ht_rc = 0;
	else
		ht_rc = curr->rc->ht;

	curr->ht = (ht_lc > ht_rc)?ht_lc + 1:ht_rc + 1;

	if (curr == NULL)
		balance = 0;
	else
	{
		if (curr->lc == NULL)
		ht_lc = 0;
	else
		ht_lc = curr->lc->ht;

	if (curr->rc == NULL)
		ht_rc = 0;
	else
		ht_rc = curr->rc->ht;

		balance = ht_lc - ht_rc;
	}

	if (balance > 1 && Balance(curr->lc) >= 0)
		return rotate_right(curr);
	else if (balance > 1 && Balance(curr->lc) < 0)
	{
		curr->lc = rotate_left(curr->lc);
		return rotate_right(curr);
	}
	else if (balance < -1 && Balance(curr->rc) <= 0)
		return rotate_left(curr);
	else if (balance < -1 && Balance(curr->rc) > 0)
	{
		curr->rc = rotate_right(curr->rc);
		return rotate_left(curr);
	}

	return curr;
}

node* insert(node *curr, int num)
{
	int balance, ht_lc, ht_rc;

	if (curr == NULL)
	{
		node *tmp;
		tmp = (node *)malloc(sizeof(node));
		tmp->lc = NULL;
		tmp->rc = NULL;
		tmp->d = num;
		tmp->ht = 1;
		return tmp;
	}
	else if (num > curr->d)
		curr->rc = insert(curr->rc, num);
	else if (num < curr->d)
		curr->lc = insert(curr->lc, num); 

	if (curr->lc == NULL)
		ht_lc = 0;
	else
		ht_lc = curr->lc->ht;

	if (curr->rc == NULL)
		ht_rc = 0;
	else
		ht_rc = curr->rc->ht;

	curr->ht = (ht_lc > ht_rc)?ht_lc + 1:ht_rc + 1;

	balance = Balance(curr);

	if (balance > 1 && num < curr->lc->d)
		return rotate_right(curr);
	else if (balance > 1 && num > curr->lc->d)
	{
		curr->lc = rotate_left(curr->lc);
		return rotate_right(curr);
	}
	else if (balance < -1 && num > curr->rc->d)
		return rotate_left(curr);
	else if (balance < -1 && num < curr->rc->d)
	{
		curr->rc = rotate_right(curr->rc);
		return rotate_left(curr);
	}

	return curr;
}

int main()
{
    int t, n, num;
    char choice;
    scanf("%d", &t);
    while (t--)
    {
    	node *root;
    	root = NULL;
        scanf("%d", &n);
        while(n--)
        {
            getchar();
            scanf("%c", &choice);
 			node *tmp;
            switch(choice)
            {
                case 'i':
                        scanf("%d", &num);
                        root = insert(root, num);
                        break;
                case 'd':
                        scanf("%d", &num);
                        root = delete(root, num);
                        break;
                case 'p':
                		if (root != NULL)
                			printf("%d", root->d);
                        print(root, root);
                		printf("\n");
                        break;
            }
        }
        free(root);
    }
  	return 0;
}