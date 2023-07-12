#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>
char stack_op[10000], op, calc[1000000];
double data[10000], temp = 0.0;
int i = 0, j = 0, k = 0;
void cal()
{
	if (stack_op[j - 1] == '+')
	{
		data[i - 2] += data[i - 1];
		i--;
		data[i] = 0;
		stack_op[j - 1] = '\0';
	}
	if (stack_op[j - 1] == '-')
	{
		data[i - 2] -= data[i - 1];
		i--;
		data[i] = 0;
		stack_op[j - 1] = '\0';
	}
	if (stack_op[j - 1] == '*')
	{
		data[i - 2] *= data[i - 1];
		i--;
		data[i] = 0;
		stack_op[j - 1] = '\0';
	}
	if (stack_op[j - 1] == '/')
	{
		data[i - 2] /= data[i - 1];
		i--;
		data[i] = 0;
		stack_op[j - 1] = '\0';
	}
}
int main()
{
	fgets(calc, 100000, stdin);//读入一个=结尾的中缀表达式
	while ((op = calc[k++]) != '=')
	{
		if (op == ' ')
			continue;
		if (isdigit(op))
		{
			for (;isdigit(op);op = calc[k++])
			{
				temp = (op - '0') + temp * 10;
			}
			data[i] = temp;
			temp = 0.0;
			i++;
		}
		if (op == '(' || op == '+' || op == '*' || op == '/' || op == '-')
		{
			if (op == '+' || op == '-')//如果读入的是‘+’或‘-’
			{
				for (j;j > 0 && stack_op[j - 1] != '(';j--)
					cal();//向前寻找直到遇到‘（’将所有计算符计算
			}
			else if (op == '*' || op == '/')//如果是这样
			{
				for (j;j > 0 && stack_op[j - 1] != '(' && stack_op[j - 1] != '+' && stack_op[j - 1] != '-';j--)
					cal();//向前计算，直到遇到‘（’或比其运算等级小的就结束
			}
			stack_op[j] = op;
			j++;//将读入的运算符保存
		}
		else if (op == ')')
		{
			for (j;stack_op[j - 1] != '(';j--)
				cal();
			stack_op[j - 1] = '\0';
			j--;
		}
		else if (op == '=')
			break;

	}
	for (j;j > 0;j--)
		cal();//最后直接清空全部
	printf("%.2lf", data[0]);
	return 0;
}