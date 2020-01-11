#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "create_sudo.h"
#include "solve_sudo.h"

int c1[3] = { 3, 4, 5 };
int c2[3] = { 6, 7, 8 };
int sudo[9][9],snum1 = 1, snum2 = 1,N;
int* p, n;
char x;


int main(int argc, char* argv[])
{
	FILE* fp1 = fopen(argv[2], "r");
	if (strcmp(argv[1], "-s") == 0 && fp1 == NULL)
	{
		printf("非法输入!\n");
		return 0;
	}
	if (argc == 3 && strcmp(argv[1], "-c") == 0)
	{
		int len = strlen(argv[2]); //将命令行字符串转换为整数 
		for (int i = 0; i < len; i++)
		{
			if (argv[2][i] >= '0' && argv[2][i] <= '9')
			{
				int value = argv[2][i] - '0';
				for (int j = 1; j <= len - 1; j++)
					value *= 10;
				n += value;
			}
			else
			{
				printf("Please input a legal number!\n");
				return 0;
			}
		}
		if (n > 1000000 || n <= 0)
		{
			printf("Please input a number from 1 to 1000000!\n");
			return 0;
		}
		FILE* fp = fopen("sudoku.txt", "w");/*以写模式("w")打开文件user.txt,如果不存在,会自动创建*/
		int start = clock();
		//fputs(pas, fp);/*将名称和密码以字符串形式写入文件*/
		sudo[0][0] = 1;
		for (int i = 1; i < 9; i++)
			sudo[0][i] = i + 1;
		p = new int[8];
		for (int i = 0; i < 8; i++)
			p[i] = i + 2;
		for (int i = 0; i < N; i++) {
			if (i > 0) fprintf(fp, "\n");

			if (snum1 == 1 && snum2 == 1) {
				if (i > 0) {
					nextPermutation(p, 8);
					for (int j = 1; j < 9; j++)
						sudo[0][j] = p[j - 1];
				}
				create(sudo);
			}
			jiaohan_1(snum1, c1);
			jiaohan_2(snum2, c2); //判断当前两个参数表示哪两种顺序
			//输出数独
			for (int i = 0; i < 9; i++)
			{
				int k = i;
				if (k >= 3 && k <= 5) k = c1[k - 3]; //如果当前是中间三行，按照顺序输出
				else if (k > 5) k = c2[k - 6];       //如果当前是中间三行，按照顺序输出

				for (int j = 0; j <= 8; j++) {
					x = sudo[k][j] + '0'; //转换成字符型
					fputc(x, fp);         //写入文件
					if (j != 8) fprintf(fp, " ");
				}
				fprintf(fp, "\n");
			}

			if (snum2 == 6) {
				snum2 = 1;
				if (snum1 == 6) snum1 = 1;
				else snum1++;
			}
			else snum2++;
		}
		fclose(fp);/*关闭文件*/
	}
	else if (argc == 3 && strcmp(argv[1], "-s") == 0)
	{
		s();
	}
	else
		printf("非法输入!\n");
	return 0;
}
