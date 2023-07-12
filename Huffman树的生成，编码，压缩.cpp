//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode* left, * right;
};
int Ccount[128] = { 0 };			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode* Root = NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE] = { {0} }; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step = 0;						//ʵ�鲽�� 
FILE* Src, * Obj;


void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode* p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

int main()
{
	if ((Src = fopen("D:\\input.txt", "r")) == NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if ((Obj = fopen("D:\\output.txt", "w")) == NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d", &Step);					//���뵱ǰʵ�鲽�� 

	statCount();
	createHTree();
	makeHCode();
	switch (Step)
	{
	case 1:
		print1();
		break;
	case 2:

		print2(Root);
		break;
	case 3:

		print3();
		break;
	case 4:
		atoHZIP(), print4();
	}//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
			//���ʵ�鲽��1���	
						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
		//���ʵ�鲽��2���	
						//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
			//���ʵ�鲽��3���
	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

	return 0;
}

//��ʵ�鲽��1����ʼ 

void statCount()
{
	Ccount[0] = 1;
	char ch = fgetc(Src);
	while (ch != EOF)
	{
		if (ch == '\n')
			continue;
		Ccount[ch]++;
		ch = fgetc(Src);
	}

}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ
int cmp(const void* a, const void* b)
{
	struct tnode** p1 = (struct tnode**)a;
	struct tnode** p2 = (struct tnode**)b;
	return (*p1)->weight == (*p2)->weight ? (*p1)->c - (*p2)->c : (*p1)->weight - (*p2)->weight;
}
void createHTree()
{
	struct tnode* p = NULL;
	struct tnode* F[128] = { NULL }, * NEWF[128] = { NULL };
	int i = 0, j = 0, flag = 0, k = 0;
	for (i = 0, j = 0; i < 128; i++)
		if (Ccount[i] > 0)
		{
			p = (struct tnode*)malloc(sizeof(struct tnode));
			p->c = i;
			p->weight = Ccount[i];
			p->left = NULL;
			p->right = NULL;
			F[j++] = p;
		}
	qsort(F, j, sizeof(struct tnode*), cmp);
	while (j > 1)
	{
		p = (struct tnode*)malloc(sizeof(struct tnode));
		p->weight = F[0]->weight + F[1]->weight;
		p->left = (struct tnode*)malloc(sizeof(struct tnode));
		p->right = (struct tnode*)malloc(sizeof(struct tnode));
		memcpy(p->left, F[0], sizeof(struct tnode));
		memcpy(p->right, F[1], sizeof(struct tnode));
		flag = 0;
		F[0]->weight = 0;
		F[1]->weight = 0;
		for (i = 0, k = 0;i < j;i++)
		{
			if (F[i] != NULL && F[i]->weight != 0)
			{
				NEWF[k] = (struct tnode*)malloc(sizeof(struct tnode));
				memcpy(NEWF[k++], F[i], sizeof(struct tnode));
			}
			if (flag == 0 && F[i] != NULL && F[i]->weight != 0 && (F[i + 1] == NULL || (p->weight < F[i + 1]->weight)))//����ͬ������β��
			{
				NEWF[k] = (struct tnode*)malloc(sizeof(struct tnode));
				memcpy(NEWF[k++], p, sizeof(struct tnode));
				flag = 1;
			}
		}
		memset(F, 0, sizeof(F));
		for (i = 0;i < k;i++)
		{
			F[i] = (struct tnode*)malloc(sizeof(struct tnode));
			memcpy(F[i], NEWF[i], sizeof(struct tnode));
		}
		memset(NEWF, 0, sizeof(NEWF));
		j -= 1;
	}
	Root = p;
}

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

void visitHTree(struct tnode* root, char code[], int time)
{
	if (root != NULL)
	{
		if (root->left == NULL && root->right == NULL)
		{
			code[time] = '\0';
			strcpy(HCode[root->c], code);
			return;
		}
		code[time] = '0';
		visitHTree(root->left, code, time + 1);
		code[time] = '1';
		visitHTree(root->right, code, time + 1);
	}

}
void makeHCode()
{
	char code[200] = { '\0' };
	visitHTree(Root, code, 0);
}

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ
char s[1000000];
void atoHZIP()
{
	rewind(Src);
	int i = 0, k = 0;
	char c = fgetc(Src);
	while (c != EOF)
	{
		while (HCode[c][i])
		{
			s[k++] = HCode[c][i++];
		}
		c = fgetc(Src);
		i = 0;
	}
	while (HCode[0][i])
	{
		s[k++] = HCode[0][i++];
	}
	int hc = 0;
	for (i = 0; s[i] != '\0'; i++)
	{
		hc = (hc << 1) | (s[i] - '0');
		if ((i + 1) % 8 == 0)
		{
			fputc(hc, Obj);     //�����Ŀ�꣨ѹ�����ļ���
			printf("%x", hc);   //��ʮ�������������Ļ��
			hc = 0;
		}
	}


}

//��ʵ�鲽��4������

void print1()
{
	int i;
	printf("NUL:1\n");
	for (i = 1; i < 128; i++)
		if (Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode* p)
{
	if (p != NULL) {
		if ((p->left == NULL) && (p->right == NULL))
			switch (p->c) {
			case 0: printf("NUL ");break;
			case ' ':  printf("SP ");break;
			case '\t': printf("TAB ");break;
			case '\n':  printf("CR ");break;
			default: printf("%c ", p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;

	for (i = 0; i < 128; i++) {
		if (HCode[i][0] != 0) {
			switch (i) {
			case 0: printf("NUL:");break;
			case ' ':  printf("SP:");break;
			case '\t': printf("TAB:");break;
			case '\n':  printf("CR:");break;
			default: printf("%c:", i); break;
			}
			printf("%s\n", HCode[i]);
		}
	}
}

void print4()
{
	long int in_size, out_size;

	fseek(Src, 0, SEEK_END);
	fseek(Obj, 0, SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);

	printf("\nԭ�ļ���С��%ldB\n", in_size);
	printf("ѹ�����ļ���С��%ldB\n", out_size);
	printf("ѹ���ʣ�%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}