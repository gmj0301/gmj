#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "solve_sudo.h"
int sudo[9][9];
int judge_all = 0, num_1 = 0;
int numl[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int serch() //找哪列空白个数最少
{
	int min = 0, first = 0;
	for (int i = 0; i < 9; i++)
	{
		if (numl[i] != 0 && first == 0) //0个空白就说明这列不用填，略过
		{
			min = i;
			first = 1;
		}
		if (numl[i] < numl[min] && numl[i] != 0 && first == 1)
			min = i;
	}
	if (first == 0) return -1; //都是0，返回-1
	else return min;
}

int mmin(int j) //求这一列第一个是0的下标
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
        fp = fopen("solve_sudo.txt", "w");   //当前是第一题的解，需要清空文件里面的所有内容 
        num_1++;    //表明这不是第一题了
	}	                               
	else
	{
		fp = fopen("solve_sudo.txt", "a+"); //当前不是第一题的解，需要保存文件里面的所有内容，在其基础上再写入新的解
		fprintf(fp, "\n\n");           //除了第一题，每一题都要先输出一个空格符，再输出其解，与前面的答案分开
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
		if ((sudo[i][l] == sudo[h][l] && i != h) || (sudo[h][l] == sudo[h][i] && i != l))       //如果同一行存在与当前位置相同的数字，则出错
		{
			return false;
		}
	int x = (h / 3) * 3;
	int y = (l / 3) * 3;
	for (int i = x; i < x + 3; i++)
		for (int j = y; j < y + 3; j++)
			if (sudo[h][l] == sudo[i][j] && i != h && j != l)       //如果同一九宫格存在与当前位置相同的数字，则出错
				return false;
	return true;       //没有出现上述错误，则返回true
}

void solve_sudo(int i, int j) {
	if (judge_all == 1) return;

	int k, h;
	numl[j]--;        //当前列的空白个数减一
	for (k = sudo[i][j] + 1; k <= 9; k++) {
		sudo[i][j] = k;
		if (judge(i, j)) {    //当前位置可以填入数字i
			if (numl[j] > 0)   //当前列还有空白
				solve_sudo(mmin(j), j);
			else 
			{
				h = serch();
				if (h == -1)
				{
					judge_all = 1;              //所有列的空白个数均为0，说明数独题目解完了
					return;                     //返回
				}
				else solve_sudo(mmin(h), h);
			}
			if (judge_all == 1) return;     //返回
		}

	}
	//1-9这9个数字都填完了，没有符合的数字
	//说明上一个位置出的数字填错了，当前位置置0，回到上一个位置
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
						numl[k]++;   //计算每一列空白的个数
					k++;
				}
			}
		}
		if (i < 9) continue;
		num = serch();  i = mmin(num);   //找到空白个数最少的那一列的第一个空白的下标
		if (num != -1) solve_sudo(i, num); 
		write();
		judge_all = 0;
		for (int i = 0; i < 9; i++)  
			numl[i] = 0;
	}
	fclose(fp);
	return;
}