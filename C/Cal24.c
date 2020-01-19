/*
# Copyright 2018  Alex(xuyc@sina.com).
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0
*/
#include <stdio.h>
#include <string.h>
#if !defined(__cplusplus)
typedef enum
{
	false = 0,
	true = 1
} bool;
#endif

char paiLie[4 * 3 * 2 * 1][4]; /*用来存放数字的排列*/
int nPaiLie = 0;

char Precedence[256] = {0}; //各个运算符的优先级
void init()
{
	Precedence['+'] = 4;
	Precedence['-'] = 4;
	Precedence['*'] = 3;
	Precedence['/'] = 3;
}

bool is_OP(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// if 3 ops have the same Priority,so one kind of tree is enough
bool only_tree(int op1, int op2, int op3)
{
	return (Precedence[op1] == Precedence[op2] && Precedence[op3] == Precedence[op2]);
}

void print_tree(char ch0, char ch1, char ch2, char ch3, char ch4, char ch5, char ch6, char ch7,
				char ch8, char ch9, char ch10)
{
	char str_expr[12] = {0};
	str_expr[0] = ch0;
	str_expr[1] = ch1;
	str_expr[2] = ch2;
	str_expr[3] = ch3;
	str_expr[4] = ch4;
	str_expr[5] = ch5;
	str_expr[6] = ch6;
	str_expr[7] = ch7;
	str_expr[8] = ch8;
	str_expr[9] = ch9;
	str_expr[10] = ch10;
	int i;
	char ch;
	for (i = 0; i < strlen(str_expr); i++)
	{
		ch = str_expr[i];
		if (is_OP(ch) || ch == '(' || ch == ')')
			printf("%c", ch);
		else
			printf("%d", ch);
	}
	printf("\n");
}

int add_PaiLie(char a, char b, char c, char d)
{
	int i;
	for (i = 0; i < nPaiLie; i++)
	{
		if (a == paiLie[i][0] && b == paiLie[i][1] && c == paiLie[i][2] && d == paiLie[i][3])
			return i;
	}

	paiLie[nPaiLie][0] = a;
	paiLie[nPaiLie][1] = b;
	paiLie[nPaiLie][2] = c;
	paiLie[nPaiLie][3] = d;
	nPaiLie++;
	return 0;
}

void form_PaiLie(char input[])
{
	nPaiLie = 0;
	int i, j, k, l;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == j)
				continue;
			for (k = 0; k < 4; k++)
			{
				if (k == i || k == j)
					continue;
				for (l = 0; l < 4; l++)
				{
					if (l == i || l == j || l == k)
						continue;
					add_PaiLie(input[i], input[j], input[k], input[l]); /*排列形成*/
				}
			}
		}
	}
}

int cal_polish(char ch0, char ch1, char ch2, char ch3, char ch4, char ch5, char ch6)
{
	char polish[8] = {0};
	polish[0] = ch0;
	polish[1] = ch1;
	polish[2] = ch2;
	polish[3] = ch3;
	polish[4] = ch4;
	polish[5] = ch5;
	polish[6] = ch6;

	float a, b, res;
	float stack[10]; //stck[0] is not used
	int top = 0;
	char ch;
	int i;

	for (i = 0; i < strlen(polish); i++)
	{
		ch = polish[i];
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			if (top < 2)
				return -1; //wrong equation
			b = stack[top--];
			a = stack[top--];
			switch (ch)
			{
			case '+':
				if (a > b)
					return -2;
				res = a + b;
				break;
			case '-':
				res = a - b;
				break;
			case '*':
				if (a > b)
					return -3;
				res = a * b;
				break;
			case '/':
				if (b < 0.01 && b > -0.01)
					return -4;
				res = a / b;
				break;
			} //switch
			stack[++top] = res;
		}
		else
		{
			stack[++top] = ch;
		}
	}
	if ((res - 24) < 0.01 && (24 - res) < 0.01)
		return 0;
	else
		return -6;
}

void form_invPolish()
{
	const char op[] = "+-*/";
	char a, b, c, d;
	int i, j, k, l;

	for (i = 0; i < nPaiLie; i++)
	{
		a = paiLie[i][0];
		b = paiLie[i][1];
		c = paiLie[i][2];
		d = paiLie[i][3];

		for (j = 0; j < 4; j++)
			for (k = 0; k < 4; k++)
				for (l = 0; l < 4; l++) /*任选三个操作符 */
				{
					if (0 == cal_polish(a, b, c, d, op[j], op[k], op[l]))
					{
						print_tree(a, op[l], '(', b, op[k], '(', c, op[j], d, ')', ')');
						if (only_tree(op[j], op[k], op[l]))
							continue;
					}

					if (0 == cal_polish(a, b, c, op[j], d, op[k], op[l]))
					{
						print_tree(a, op[l], '(', '(', b, op[j], c, ')', op[k], d, ')');
						if (only_tree(op[j], op[k], op[l]))
							continue;
					}

					if (0 == cal_polish(a, b, c, op[j], op[k], d, op[l]))
					{
						print_tree('(', a, op[k], '(', b, op[j], c, ')', ')', op[l], d);
						if (only_tree(op[j], op[k], op[l]))
							continue;
					}

					if (0 == cal_polish(a, b, op[j], c, d, op[k], op[l]))
					{
						print_tree('(', a, op[j], b, ')', op[l], '(', c, op[k], d, ')');
						if (only_tree(op[j], op[k], op[l]))
							continue;
					}

					if (0 == cal_polish(a, b, op[j], c, op[k], d, op[l]))
						print_tree('(', '(', a, op[j], b, ')', op[k], c, ')', op[l], d);

				} //for l

	} //for i
}

int main(int argc, char *argv[])
{
	char input[4];
	int in;
	char note[] = " n1 n2 n3 n4 (n1~n4 are 2~10)\n";

	if (argc != 5)
		return printf("%s %s", argv[0], note);
	int i;
	for (i = 0; i < 4; i++)
	{
		sscanf(argv[i + 1], "%d", &in);
		if (in > 10 || in < 1)
			return printf("%s %s", argv[0], note);
		input[i] = in;
	}
	printf("----------------------\n");
	init();
	form_PaiLie(input);
	form_invPolish();
	return 0;
}
