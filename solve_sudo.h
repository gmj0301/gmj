#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
int sudo[9][9];
int temp = 0, judge_all = 0;


void write()
{
	FILE* fp = fopen("solve_sudo.txt", "w");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			char x = sudo[i][j] + '0'; //转换成字符型
			fputc(x, fp);         //写入文件
			if (j != 8) fprintf(fp, " ");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

bool judge(int h, int l) {
	for (int i = 0; i < 9; i++)
		if (sudo[i][l] == sudo[h][l] && i != h)
			return false;
	for (int i = 0; i < 9; i++)
		if (sudo[h][l] == sudo[h][i] && i != l)
			return false;
	int x = (h / 3) * 3;
	int y = (l / 3) * 3;
	for (int i = x; i < x + 3; i++)
		for (int j = y; j < y + 3; j++)
			if (sudo[h][l] == sudo[i][j] && i != h && j != l)
				return false;
	return true;
}

void solve_sudo(int i, int j) {
	if (judge_all == 1) return;

	int k, h, l, temp = 0;
	for (k = sudo[i][j] + 1; k <= 9; k++) {
		sudo[i][j] = k;
		if (judge(i, j)) {

			h = i; l = j + 1;
			for (; h < 9; h++) {
				for (; l < 9; l++)
					if (sudo[h][l] == 0) {
						temp = 1;
						break;
					}
				if (temp == 1) break;
				else l = 0;
			}
			if (temp == 1) solve_sudo(h, l);
			else {
				judge_all = 1;
				return;
			}
			if (judge_all == 1) return;
		}

	}
	sudo[i][j] = 0;
	return;
}


void solve(const char* txt)
{

	FILE* fp = fopen(txt, "r");

	//if (!strcmp(txt, "wert.txt")) return;
	if (fp == NULL)
	{
		printf("Please enter the correct address!\n");
		return; //失败返回1
	}

	while (!feof(fp))
	{
		char p[25];

		int num = 0, w, s;
		for (int i = 0; i < 9; i++) {
			fgets(p, 25, fp);
			int k = 0;
			for (int j = 0; j < 20; j++) {
				if (p[j] <= '9' && p[j] >= '0') {
					sudo[i][k] = p[j] - '0';
					if (num == 0 && sudo[i][j] == 0) {
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

		fgets(p, 25, fp);
	}
	fclose(fp);
	return;
}
