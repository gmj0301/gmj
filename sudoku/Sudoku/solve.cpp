#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "solve_sudo.h"
int sudo[9][9];
int judge_all = 0, num_1 = 0;
int numl[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int serch() //�����пհ׸�������
{
	int min = 0, first = 0;
	for (int i = 0; i < 9; i++)
	{
		if (numl[i] != 0 && first == 0) //0���հ׾�˵�����в�����Թ�
		{
			min = i;
			first = 1;
		}
		if (numl[i] < numl[min] && numl[i] != 0 && first == 1)
			min = i;
	}
	if (first == 0) return -1; //����0������-1
	else return min;
}

int mmin(int j) //����һ�е�һ����0���±�
{
	int res = 0;
	for (int i = 0; i < 9; i++)
		if (res == 0 && sudo[i][j] == 0)
			return i;
	return -1;
}

void write()
{
	FILE* fp;
	if (num_1 == 0)
	{
        fp = fopen("solve_sudo.txt", "w");   //��ǰ�ǵ�һ��Ľ⣬��Ҫ����ļ�������������� 
        num_1++;    //�����ⲻ�ǵ�һ����
	}	                               
	else
	{
		fp = fopen("solve_sudo.txt", "a+"); //��ǰ���ǵ�һ��Ľ⣬��Ҫ�����ļ�������������ݣ������������д���µĽ�
		fprintf(fp, "\n\n");           //���˵�һ�⣬ÿһ�ⶼҪ�����һ���ո�����������⣬��ǰ��Ĵ𰸷ֿ�
	} 
	char s[18];
	int k;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			k = j * 2;
			s[k] = sudo[i][j] + '0';
			s[k + 1] = ' ';
		}
		s[17] = '\0';
		fputs(s, fp);
		if(i != 8) fprintf(fp, "\n");
	}
	fclose(fp);        
}

bool judge(int h, int l) {
	for (int i = 0; i < 9; i++)
		if ((sudo[i][l] == sudo[h][l] && i != h) || (sudo[h][l] == sudo[h][i] && i != l))       //���ͬһ�д����뵱ǰλ����ͬ�����֣������
		{
			return false;
		}
	int x = (h / 3) * 3;
	int y = (l / 3) * 3;
	for (int i = x; i < x + 3; i++)
		for (int j = y; j < y + 3; j++)
			if (sudo[h][l] == sudo[i][j] && i != h && j != l)       //���ͬһ�Ź�������뵱ǰλ����ͬ�����֣������
				return false;
	return true;       //û�г������������򷵻�true
}

void solve_sudo(int i, int j) {
	if (judge_all == 1) return;

	int k, h;
	numl[j]--;        //��ǰ�еĿհ׸�����һ
	for (k = sudo[i][j] + 1; k <= 9; k++) {
		sudo[i][j] = k;
		if (judge(i, j)) {    //��ǰλ�ÿ�����������i
			if (numl[j] > 0)   //��ǰ�л��пհ�
				solve_sudo(mmin(j), j);
			else 
			{
				h = serch();
				if (h == -1)
				{
					judge_all = 1;              //�����еĿհ׸�����Ϊ0��˵��������Ŀ������
					return;                     //����
				}
				else solve_sudo(mmin(h), h);
			}
			if (judge_all == 1) return;     //����
		}

	}
	//1-9��9�����ֶ������ˣ�û�з��ϵ�����
	//˵����һ��λ�ó�����������ˣ���ǰλ����0���ص���һ��λ��
	sudo[i][j] = 0;
	numl[j]++;
	return;
}


void solve(const char* txt)
{
	FILE* fp;
	fp = fopen(txt, "r");

	while (!feof(fp))
	{
		char p[25];

		int num, i;
		for (i = 0; i < 9; i++) {
			fgets(p, 25, fp);
			if (p[0] < '0' || p[0] > '9') break;
			int k = 0;
			for (int j = 0; j < 20; j++) {
				if (p[j] <= '9' && p[j] >= '0') {
					sudo[i][k] = p[j] - '0';
					if (sudo[i][k] == 0)
						numl[k]++;   //����ÿһ�пհ׵ĸ���
					k++;
				}
			}
		}
		if (i < 9) continue;
		num = serch();  i = mmin(num);   //�ҵ��հ׸������ٵ���һ�еĵ�һ���հ׵��±�
		if (num != -1) solve_sudo(i, num); 
		write();
		judge_all = 0;
		for (int i = 0; i < 9; i++)  
			numl[i] = 0;
	}
	fclose(fp);
	return;
}