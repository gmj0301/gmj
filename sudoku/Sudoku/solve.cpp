#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include "solve_sudo.h"
int sudo[9][9];
int judge_all = 0, num_1 = 0;

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

	int k, h, l, temp;
	for (k = sudo[i][j] + 1; k <= 9; k++) {
		sudo[i][j] = k;
		if (judge(i, j)) {    //��ǰλ�ÿ�����������i

			h = i;            //��¼�µ�ǰλ���Աߵ��±�[h,l]
			l = j + 1;
			temp = 0;
			for (; h < 9; h++) {
				for (; l < 9; l++)
					if (sudo[h][l] == 0) {   //���[h,l]������Ϊ0
						temp = 1;            //temp=1���
						break;
					}
				if (temp == 1) break;
				else l = 0;
			}
			if (temp == 1) solve_sudo(h, l);  //[h,l]������Ϊ0������solve_sudo����
			else {
				judge_all = 1;              //����λ�ö���Ϊ0��˵��������Ŀ������
				return;                     //����
			}
			if (judge_all == 1) return;     //����
		}

	}
	//1-9��9�����ֶ������ˣ�û�з��ϵ�����
	//˵����һ��λ�ó�����������ˣ���ǰλ����0���ص���һ��λ��
	sudo[i][j] = 0;
	return;
}


void solve(const char* txt)
{
	FILE* fp;
	fp = fopen(txt, "r");

	while (!feof(fp))
	{
		char p[25];

		if (num_1 != 0) fgets(p, 2, fp);
		int num = 0, w, s;
		for (int i = 0; i < 9; i++) {
			fgets(p, 25, fp);
			int k = 0;
			for (int j = 0; j < 20; j++) {
				if (p[j] <= '9' && p[j] >= '0') {
					sudo[i][k] = p[j] - '0';
					if (num == 0 && sudo[i][k] == 0) {
						w = i;
						s = k;
						num++;
					}
					k++;
				}
			}
		}

		solve_sudo(w, s);
		write();
		judge_all = 0;
	}
	fclose(fp);
	return;
}