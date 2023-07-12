#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct BSTree
{
	int data;
	struct BSTree* lchild, * rchild;
}BSNode;
void insert_Node(int datum, struct BSTree* root)
{
	if (root->data > datum)
	{
		if (root->lchild == NULL)
		{
			root->lchild = (struct BSTree*)malloc(sizeof(struct BSTree));
			root->lchild->data = datum;
			root->lchild->lchild = NULL;
			root->lchild->rchild = NULL;
		}
		else
		{
			insert_Node(datum, root->lchild);
		}
	}
	else
	{
		if (root->rchild == NULL)
		{
			root->rchild = (struct BSTree*)malloc(sizeof(struct BSTree));
			root->rchild->data = datum;
			root->rchild->lchild = NULL;
			root->rchild->rchild = NULL;
		}
		else
		{
			insert_Node(datum, root->rchild);
		}
	}
}
void create_BST(struct BSTree* root)
{
	root = (struct BSTree*)malloc(sizeof(struct BSTree));
	root->lchild = NULL;
	root->rchild = NULL;
	scanf("%d", &root->data);
	int datum;
	while ((scanf("%d", &datum) != EOF))
	{
		insert_Node(datum, root);
	}

}
int main()
{
	struct BSTree* root = (struct BSTree*)malloc(sizeof(struct BSTree));
	root->lchild = NULL;
	root->rchild = NULL;
	create_BST(root);
}