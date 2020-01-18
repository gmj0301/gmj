#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include "create_sudo.h"
int shift[8] = { 3, 6, 1, 4, 7, 2, 5, 8 };
int c1[3] = { 3, 4, 5 };
int c2[3] = { 6, 7, 8 };
int snum1 = 1, snum2 = 1, flag_first = 0;

void produce(int sudo[9][9])  //��һ����֪��ͨ���任�õ������������վ�
{
	for (int i = 1; i < 9; i++)
		for (int j = 0; j < 9; j++)
			sudo[i][j] = sudo[0][(j + shift[i - 1]) % 9];
	//��i���ǵ�һ������shift[i]�õ���  ��sudo[i][j] = sudo[0][j����shift[i]]
	//j���ƺ���ܳ���9������Ҫģ9ȡ��
}

void swap(int& a, int& b) //��������������a��b
{
	int temp = a;
	a = b;
	b = temp;
}

bool nextPermutation(int* p, int n)
{
	int last = n - 1;
	int i, j, k;
	//�Ӻ���ǰ���ң�����û�к����������ǰ������������������ͣ�ں�һ������λ�á�   
	i = last;
	while (i > 0 && p[i] < p[i - 1])
		i--;
	//��û�к����������ǰ������������˵���Ѿ��������һ�����У�����false��   
	if (i == 0)
		return false;
	//�Ӻ�鵽i�����Ҵ���p[i - 1]����С����������k   
	k = i;
	for (j = last; j >= i; j--)
		if (p[j] > p[i - 1] && p[j] < p[k])
			k = j;
	//����p[k]��p[i - 1]   
	swap(p[k], p[i - 1]);
	//����p[last]��p[i]   
	for (j = last, k = i; j > k; j--, k++)
		swap(p[j], p[k]);

	return true;
}

void jiaohan_1(int s1, int* c1)     //�м�4��5��6�еı任
{
	if (s1 == 1) { c1[0] = 3; c1[1] = 4; c1[2] = 5; }
	if (s1 == 2) { c1[0] = 3; c1[1] = 5; c1[2] = 4; }
	if (s1 == 3) { c1[0] = 4; c1[1] = 3; c1[2] = 5; }
	if (s1 == 4) { c1[0] = 4; c1[1] = 5; c1[2] = 3; }
	if (s1 == 5) { c1[0] = 5; c1[1] = 3; c1[2] = 4; }
	if (s1 == 6) { c1[0] = 5; c1[1] = 4; c1[2] = 3; }
}

void jiaohan_2(int s2, int* c2)     //���7��8��9�еı任
{
	if (s2 == 1) { c2[0] = 6; c2[1] = 7; c2[2] = 8; }
	if (s2 == 2) { c2[0] = 6; c2[1] = 8; c2[2] = 7; }
	if (s2 == 3) { c2[0] = 7; c2[1] = 6; c2[2] = 8; }
	if (s2 == 4) { c2[0] = 7; c2[1] = 8; c2[2] = 6; }
	if (s2 == 5) { c2[0] = 8; c2[1] = 6; c2[2] = 7; }
	if (s2 == 6) { c2[0] = 8; c2[1] = 7; c2[2] = 6; }
}

void init(int sudo[9][9], int p[8]) //��ʼ�����涨���Ͻǵ�һ��Ϊ1����һ��Ϊ123456789
{
	sudo[0][0] = 1;
	for (int i = 1; i < 9; i++)
		sudo[0][i] = i + 1;
	for (int i = 0; i < 8; i++)
		p[i] = i + 2;
}

void output(int sudo[9][9], FILE* fp)  //�������
{
	jiaohan_1(snum1, c1);
	jiaohan_2(snum2, c2); //�жϵ�ǰ����������ʾ������˳��

	char s[18];
	if (flag_first != 0) fprintf(fp, "\n");
	else flag_first = 1;
	//�������
	for (int i = 0; i < 9; i++)
	{
		int k = i;
		if (k >= 3 && k <= 5) k = c1[k - 3]; //�����ǰ���м����У�����˳�����
		else if (k > 5) k = c2[k - 6];       //�����ǰ���м����У�����˳�����

		for (int j = 0; j <= 8; j++) {
			int kt = j * 2;
			s[kt] = sudo[k][j] + '0';
			s[kt + 1] = ' ';

		}
		s[17] = '\0';
		fputs(s, fp);         //д���ļ�
		if(i != 8) fprintf(fp, "\n");
	}
}

void change()
{
	if (snum2 == 6) {
		snum2 = 1;
		if (snum1 == 6) snum1 = 1;
		else snum1++;
	}
	else snum2++;
}

void create(int N)
{
	int p[8], sudo[9][9];

	FILE* fp = fopen("sudoku.txt", "w");
	/*��дģʽ("w")���ļ�user.txt,���������,���Զ�����*/

	init(sudo, p); //��ʼ�����Լ����õ�һ������

	for (int i = 0; i < N; i++)
	{
		if (i > 0) fprintf(fp, "\n");    //�Ѿ������һ����������Ҫ��һ��

		if (snum1 == 1 && snum2 == 1)    //֮ǰ���������б任�Ѿ����
		{
			if (i > 0) //i=0˵�����ǳ�ʼ��������������Ҫ����ȫ����
			{
				nextPermutation(p, 8);
				for (int j = 1; j < 9; j++)
					sudo[0][j] = p[j - 1];
			}
			produce(sudo); //�ɵ�һ����������������
		}

		output(sudo, fp);

		change();
	}
	fclose(fp);/*�ر��ļ�*/
}