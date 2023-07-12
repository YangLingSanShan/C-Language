#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef struct Tree
{
	int data;
	struct Tree* lchild, * rchild;
}Node;
//遍历叶子节点 
void leaves(struct Tree* root, int n)
{
	if (root)
	{
		if (!root->lchild && !root->rchild)
			printf("%d %d\n", root->data, n);
		leaves(root->lchild, n + 1);
		leaves(root->rchild, n + 1);
	}
}
int** levelOrder(struct Tree* root, int* returnSize, int** returnColumnSizes) {
	int** ans = (int**)malloc(sizeof(int*) * 2000);
	*returnSize = 0;
	if (!root) return NULL;//要在return前给出*returnSize的取值不然过不去；！！
	int columnSizes[2000];//记录每一行的列数（每层结点数），因为要给出* returnColumnSizes
	struct Tree* queue[2000];//模拟队列
	int rear = 0;int head = 0;//记录队列头尾
	queue[rear++] = root;//录入根结点

	while (rear != head) {//队列不为空
		ans[(*returnSize)] = (int*)malloc(sizeof(int) * (rear - head));
		columnSizes[(*returnSize)] = rear - head;
		int start = head;//记录遍历开始位置，即为本层的头
		head = rear;//本层的尾部成为下次的头，因为所有的元素均弹出队列
		//在这里下层的头head同时作为遍历结束的位置，因为在遍历中rear会不断改变，成为下层的尾
		for (int i = start;i < head;i++) {//弹出start到未变化的rear（即为head）之间的所有元素
			ans[(*returnSize)][i - start] = queue[i]->data;
			if (queue[i]->lchild) queue[rear++] = queue[i]->lchild;
			if (queue[i]->rchild) queue[rear++] = queue[i]->rchild;//rear不断改变
		}
		(*returnSize)++;//一层遍历完*returnSize加一；

	}
	*returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));//给出*returnColumnSizes
	for (int i = 0;i < *returnSize;i++) (*returnColumnSizes)[i] = columnSizes[i];
	return ans;
}
//递归遍历
void order(struct Tree* root, int* res, int* resSize) {
	if (root == NULL) {
		return;
	}
	order(root->lchild, res, resSize);//这里是后序遍历
	order(root->rchild, res, resSize);
	res[(*resSize)++] = root->data;
	/*中序遍历
	 postorder(root->lchild, res, resSize);
	 res[(*resSize)++] = root->data; 
	 postorder(root->rchild, res, resSize);
	*/
	/*前序遍历
	 res[(*resSize)++] = root->data;
	 postorder(root->lchild, res, resSize);
	 postorder(root->rchild, res, resSize);
	*/
}
int* postorderTraversal(struct Tree* root, int* returnSize) {
	int* res = (int*)malloc(sizeof(int) * 2001);
	*returnSize = 0;
	order(root, res, returnSize);
	return res;
}

//中序遍历 左中右
int* inorderTraversal(struct Tree* root, int* returnSize) {
    struct Tree* stack[10000];//建立一个栈
    int top = -1;//栈顶
    *returnSize = 0;//初始为0;
    int* res = (int*)malloc(sizeof(int) * 1000);//建立结果数组

    if (root == NULL)
    {
        return NULL;
    }//如果是空树,返回空
    //中序遍历 左根右
    while (root != NULL || top >= 0)
    {
        while (root)
        {
            top++;//进栈
            stack[top] = root;
            root = root->lchild;//更新根结点.让左子节点进栈
        }
        //以出栈的子节点作为根节点，判断是否存在右节点
        root = stack[top];//出栈操作
        top--;
        res[(*returnSize)++] = root->data;
        root = root->rchild;
    }
    return res;
}
//前序遍历 
int* preorderTraversal(struct Tree* root, int* returnSize) {
	int* res = (int*)malloc(sizeof(int) * 2000);
	struct Tree* stack[10000];
	*returnSize = 0;
	if (root == NULL) {
		return res;
	}
	struct Tree* node = root;
	int stk_top = 0;
	while (stk_top > 0 || node != NULL) {
		while (node != NULL) {
			res[(*returnSize)++] = node->data;
			stack[stk_top++] = node;
			node = node->lchild;
		}
		node = stack[--stk_top];
		node = node->rchild;
	}
	return res;
}
//后序遍历
int* postorderTraversal(struct Tree* root, int* returnSize) {
	int* res = (int*)malloc(sizeof(int) * 2001);
	*returnSize = 0;
	if (root == NULL) {
		return res;
	}
	struct Tree** stk = (struct Tree**)malloc(sizeof(struct Tree*) * 2001);
	int top = 0;
	struct Tree* prev = NULL;
	while (root != NULL || top > 0) {
		while (root != NULL) {
			stk[top++] = root;
			root = root->lchild;
		}
		root = stk[--top];
		if (root->rchild == NULL || root->rchild == prev) {
			res[(*returnSize)++] = root->data;
			prev = root;
			root = NULL;
		}
		else {
			stk[top++] = root;
			root = root->rchild;
		}
	}
	return res;
}

/*中序遍历，字符串版 
void insert_Node(char words[], struct BSTree* root)
{
	if (strcmp(root->str, words) > 0)
	{
		if (root->lchild == NULL)
		{
			root->lchild = (struct BSTree*)malloc(sizeof(struct BSTree));
			strcpy(root->lchild->str, words);
			root->lchild->lchild = NULL;
			root->lchild->rchild = NULL;
			root->lchild->time = 1;
		}
		else
		{
			insert_Node(words, root->lchild);
		}
	}
	else if (strcmp(root->str, words) < 0)
	{
		if (root->rchild == NULL)
		{
			root->rchild = (struct BSTree*)malloc(sizeof(struct BSTree));
			strcpy(root->rchild->str, words);
			root->rchild->lchild = NULL;
			root->rchild->rchild = NULL;
			root->rchild->time = 1;
		}
		else
		{
			insert_Node(words, root->rchild);
		}
	}
	else
		root->time++;
}*/
//给出前序遍历，中序遍历构造树
//前序：[ 根节点, [左子树的前序遍历结果], [右子树的前序遍历结果] ]
//中序：[ [左子树的中序遍历结果], 根节点, [右子树的中序遍历结果] ]
struct Tree* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
	if (preorderSize == 0 || inorderSize == 0)
		return NULL;

	struct Tree* root = (struct Tree*)malloc(sizeof(struct Tree));
	int index;
	root->data = preorder[0];
	for (index = 0;index < inorderSize;index++)
		if (inorder[index] == preorder[0])
			break;
	root->lchild = buildTree(preorder + 1, index, inorder, index);
	root->rchild = buildTree(preorder + index + 1, preorderSize - index - 1, inorder + index + 1, preorderSize - index - 1);
	return root;
}
//查找最底层最左端的节点数据（BFS层次遍历，依次存入非空右节点、非空左节点，那么最后一个入队的就是所求）
//右侧与之类似
int findBottomLeftValue(struct Tree* root) {
	if (root == NULL)
		return -1;//error
	struct Tree* queue[10001];
	queue[0] = root;
	int head = 1, tail = 0;
	while (head != tail)
	{
		if (queue[tail]->rchild != NULL)
		{
			queue[head++] = queue[tail]->rchild;
		}
		if (queue[tail]->lchild != NULL)
		{
			queue[head++] = queue[tail]->lchild;
		}
		tail++;
	}
	return queue[head - 1]->data;
}
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int* largestValues(struct Tree* root, int* returnSize)
{
	if (!root)
	{
		*returnSize = 0;
		return NULL;
	}
	int head = 1, tail = 0, max, pos = 0;
	*returnSize = 0;
	int* res = (int*)malloc(sizeof(int) * 10005);
	struct Tree* queue[10001];
	queue[0] = root;
	while (head != tail)
	{
		int len = head - tail;
		max = INT_MIN;
		while (len)
		{
			len--;
			if (queue[tail]->rchild != NULL)
			{
				queue[head++] = queue[tail]->rchild;
			}
			if (queue[tail]->lchild != NULL)
			{
				queue[head++] = queue[tail]->lchild;
			}
			max = (max > queue[tail]->data) ? max : queue[tail]->data;
			tail++;
		}
		res[pos++] = max;
	}
	*returnSize = pos;
	return res;
}
//查找树的深度
int Depth(struct Tree* root) {
	if (!root) {
		return 0;
	}
	return fmax(Depth(root->lchild), Depth(root->rchild)) + 1;
}
int main()
{
	
	return 0;
}