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

	int k, h, l, temp;
	for (k = sudo[i][j] + 1; k <= 9; k++) {
		sudo[i][j] = k;
		if (judge(i, j)) {    //当前位置可以填入数字i

			h = i;            //记录下当前位置旁边的下标[h,l]
			l = j + 1;
			temp = 0;
			for (; h < 9; h++) {
				for (; l < 9; l++)
					if (sudo[h][l] == 0) {   //如果[h,l]处数字为0
						temp = 1;            //temp=1标记
						break;
					}
				if (temp == 1) break;
				else l = 0;
			}
			if (temp == 1) solve_sudo(h, l);  //[h,l]处数字为0，调用solve_sudo函数
			else {
				judge_all = 1;              //所有位置都不为0，说明数独题目解完了
				return;                     //返回
			}
			if (judge_all == 1) return;     //返回
		}

	}
	//1-9这9个数字都填完了，没有符合的数字
	//说明上一个位置出的数字填错了，当前位置置0，回到上一个位置
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
