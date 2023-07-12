#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef struct Tree
{
	int data;
	struct Tree* lchild, * rchild;
}Node;
//����Ҷ�ӽڵ� 
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
	if (!root) return NULL;//Ҫ��returnǰ����*returnSize��ȡֵ��Ȼ����ȥ������
	int columnSizes[2000];//��¼ÿһ�е�������ÿ������������ΪҪ����* returnColumnSizes
	struct Tree* queue[2000];//ģ�����
	int rear = 0;int head = 0;//��¼����ͷβ
	queue[rear++] = root;//¼������

	while (rear != head) {//���в�Ϊ��
		ans[(*returnSize)] = (int*)malloc(sizeof(int) * (rear - head));
		columnSizes[(*returnSize)] = rear - head;
		int start = head;//��¼������ʼλ�ã���Ϊ�����ͷ
		head = rear;//�����β����Ϊ�´ε�ͷ����Ϊ���е�Ԫ�ؾ���������
		//�������²��ͷheadͬʱ��Ϊ����������λ�ã���Ϊ�ڱ�����rear�᲻�ϸı䣬��Ϊ�²��β
		for (int i = start;i < head;i++) {//����start��δ�仯��rear����Ϊhead��֮�������Ԫ��
			ans[(*returnSize)][i - start] = queue[i]->data;
			if (queue[i]->lchild) queue[rear++] = queue[i]->lchild;
			if (queue[i]->rchild) queue[rear++] = queue[i]->rchild;//rear���ϸı�
		}
		(*returnSize)++;//һ�������*returnSize��һ��

	}
	*returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));//����*returnColumnSizes
	for (int i = 0;i < *returnSize;i++) (*returnColumnSizes)[i] = columnSizes[i];
	return ans;
}
//�ݹ����
void order(struct Tree* root, int* res, int* resSize) {
	if (root == NULL) {
		return;
	}
	order(root->lchild, res, resSize);//�����Ǻ������
	order(root->rchild, res, resSize);
	res[(*resSize)++] = root->data;
	/*�������
	 postorder(root->lchild, res, resSize);
	 res[(*resSize)++] = root->data; 
	 postorder(root->rchild, res, resSize);
	*/
	/*ǰ�����
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

//������� ������
int* inorderTraversal(struct Tree* root, int* returnSize) {
    struct Tree* stack[10000];//����һ��ջ
    int top = -1;//ջ��
    *returnSize = 0;//��ʼΪ0;
    int* res = (int*)malloc(sizeof(int) * 1000);//�����������

    if (root == NULL)
    {
        return NULL;
    }//����ǿ���,���ؿ�
    //������� �����
    while (root != NULL || top >= 0)
    {
        while (root)
        {
            top++;//��ջ
            stack[top] = root;
            root = root->lchild;//���¸����.�����ӽڵ��ջ
        }
        //�Գ�ջ���ӽڵ���Ϊ���ڵ㣬�ж��Ƿ�����ҽڵ�
        root = stack[top];//��ջ����
        top--;
        res[(*returnSize)++] = root->data;
        root = root->rchild;
    }
    return res;
}
//ǰ����� 
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
//�������
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

/*����������ַ����� 
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
//����ǰ��������������������
//ǰ��[ ���ڵ�, [��������ǰ��������], [��������ǰ��������] ]
//����[ [������������������], ���ڵ�, [������������������] ]
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
//������ײ�����˵Ľڵ����ݣ�BFS��α��������δ���ǿ��ҽڵ㡢�ǿ���ڵ㣬��ô���һ����ӵľ�������
//�Ҳ���֮����
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
//�����������
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