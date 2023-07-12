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
	fgets(calc, 100000, stdin);//����һ��=��β����׺���ʽ
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
			if (op == '+' || op == '-')//���������ǡ�+����-��
			{
				for (j;j > 0 && stack_op[j - 1] != '(';j--)
					cal();//��ǰѰ��ֱ�����������������м��������
			}
			else if (op == '*' || op == '/')//���������
			{
				for (j;j > 0 && stack_op[j - 1] != '(' && stack_op[j - 1] != '+' && stack_op[j - 1] != '-';j--)
					cal();//��ǰ���㣬ֱ���������������������ȼ�С�ľͽ���
			}
			stack_op[j] = op;
			j++;//����������������
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
		cal();//���ֱ�����ȫ��
	printf("%.2lf", data[0]);
	return 0;
}