#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/**************************************************************************************
Author:LPR
Date:2023/04/26
Function:��    ��׺���ʽ     ת��Ϊ���ʽ�������Ҽ���ֵ���������������ڵ㣬�����ҽڵ�����ݣ�������ڣ�
Remark:�����ʽ������ǰ��/����/���������������Ӧ���ǰ׺/��׺/��׺���ʽ
	   !!!δ����free���������ܵ����ڴ�й¶!!!
**************************************************************************************/
struct num_or_op //����or���������λ��)
{
	int num;
	char op;
}p[1000], stack[1000];
struct tree {
	struct num_or_op a;
	struct tree* l;
	struct tree* r;
}*stack_op[4000];
int top_p, top_stack, top_stack_op;
int cal(struct tree* root)
{
	if (root->l == NULL && root->r == NULL)
		return root->a.num;
	else
	{
		switch (root->a.op)
		{
		case '+':
			return cal(root->l) + cal(root->r);
			break;
		case '-':
			return cal(root->l) - cal(root->r);
			break;
		case '*':
			return cal(root->l) * cal(root->r);
			break;
		case '/':
			return cal(root->l) / cal(root->r);
			break;
		}
	}
}
int main()
{
	char ch = getchar();
	int n = 0;
	while (ch != '=')
	{
		if (isdigit(ch))
		{
			n = 0;
			while (isdigit(ch))
			{
				n = ch - '0' + n * 10;
				ch = getchar();
			}
			p[top_p++].num = n;
			continue;
		}
		else if (ch == '+' || ch == '-')
		{
			if (top_stack == 0)//ջ��
				stack[top_stack++].op = ch;
			else
			{
				for (int i = top_stack - 1;stack[i].op != '(' && top_stack != 0;i--)
				{
					p[top_p++] = stack[i];
					top_stack--;
				}
				stack[top_stack++].op = ch;
			}
		}
		else if (ch == '(')
		{
			stack[top_stack++].op = ch;
		}
		else if (ch == '/' || ch == '*')
		{
			if (top_stack == 0)//ջ��
				stack[top_stack++].op = ch;
			else
			{
				for (int i = top_stack - 1;stack[i].op != '(' && stack[i].op != '+' && stack[i].op != '-' && top_stack != 0;i--)
				{
					p[top_p++] = stack[i];
					top_stack--;
				}
				stack[top_stack++].op = ch;
			}
		}
		else if (ch == ')')
		{
			for (int i = top_stack - 1;stack[i].op != '(' && top_stack != 0;i--)
			{
				p[top_p++] = stack[i];
				top_stack--;
			}
			stack[top_stack--].op = '\0';
		}
		ch = getchar();
	}
	while (top_stack--)
	{
		p[top_p++] = stack[top_stack];
	}
	struct tree* temp = NULL, * T1 = NULL, * T2 = NULL;
	for (int i = 0;i < top_p;i++)
	{
		if (!p[i].op)//����
		{
			temp = (struct tree*)malloc(sizeof(struct tree));
			temp->l = NULL;temp->r = NULL;
			temp->a = p[i];
			stack_op[top_stack_op++] = temp;
			temp = NULL;
		}
		else
		{
			T1 = stack_op[top_stack_op - 2];
			T2 = stack_op[top_stack_op - 1];
			temp = (struct tree*)malloc(sizeof(struct tree));
			temp->l = T1;temp->r = T2;
			temp->a = p[i];
			stack_op[top_stack_op - 2] = temp;
			top_stack_op = top_stack_op - 1;
		}
	}
	if (!stack_op[0]->a.op)
		printf("%d ", stack_op[0]->a.num);
	else
		printf("%c ", stack_op[0]->a.op);
	if (stack_op[0]->l != NULL)
	{
		if (!stack_op[0]->l->a.op)
			printf("%d ", stack_op[0]->l->a.num);
		else
			printf("%c ", stack_op[0]->l->a.op);
	}
	if (stack_op[0]->r != NULL)
	{
		if (!stack_op[0]->r->a.op)
			printf("%d ", stack_op[0]->r->a.num);
		else
			printf("%c ", stack_op[0]->r->a.op);
	}
	printf("\n%d", cal(stack_op[0]));
	return 0;
}