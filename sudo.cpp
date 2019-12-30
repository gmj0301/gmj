#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<time.h>
int sudo[9][9];
int snum1 = 1, snum2 = 1;
int* p;
char x;

int shift[8] = { 3, 6, 1, 4, 7, 2, 5, 8 };

void create() {
	for (int i = 1; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			sudo[i][j] = sudo[0][(j + shift[i - 1]) % 9];
			//第i行第j个是第一行左移shift[i]得到的
			//相当于 sudo[i][j] = sudo[0][j右移shift[i]]
			//j右移后可能超出9，所以要模9取余
		}
	}
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}



bool nextPermutation(int* p, int n)
{
	int last = n - 1;
	int i, j, k;   
	//从后向前查找，看有没有后面的数大于前面的数的情况，若有则停在后一个数的位置。   
	i = last;
	while (i > 0 && p[i] < p[i - 1])
		i--;
	//若没有后面的数大于前面的数的情况，说明已经到了最后一个排列，返回false。   
	if (i == 0)
		return false;
	//从后查到i，查找大于p[i - 1]的最小的数，记入k   
	k = i;
	for (j = last; j >= i; j--)
		if (p[j] > p[i - 1] && p[j] < p[k])
			k = j;
	//交换p[k]和p[i - 1]   
	swap(p[k], p[i - 1]);
	//倒置p[last]到p[i]   
	for (j = last, k = i; j > k; j--, k++)
		swap(p[j], p[k]);
	return true;
}

int c1[3] = { 3, 4, 5 };
int c2[3] = { 6, 7, 8 };

void jiaohan_1(int s1) {
	if (s1 == 2) { c1[0] = 3; c1[1] = 5; c1[2] = 4;}
	if (s1 == 3) { c1[0] = 4; c1[1] = 3; c1[2] = 5;}
	if (s1 == 4) { c1[0] = 4; c1[1] = 5; c1[2] = 3;}
	if (s1 == 5) { c1[0] = 5; c1[1] = 3; c1[2] = 4;}
	if (s1 == 6) { c1[0] = 5; c1[1] = 4; c1[2] = 3;}
}

void jiaohan_2(int s2) {
	if (s2 == 2) { c2[0] = 6; c2[1] = 8; c2[2] = 7;}
	if (s2 == 3) { c2[0] = 7; c2[1] = 6; c2[2] = 8;}
	if (s2 == 4) { c2[0] = 7; c2[1] = 8; c2[2] = 6;}
	if (s2 == 5) { c2[0] = 8; c2[1] = 6; c2[2] = 7;}
	if (s2 == 6) { c2[0] = 8; c2[1] = 7; c2[2] = 6;}
}

int main() {
	int N;
	scanf_s("%d", &N);
	FILE* fp = fopen("sudoku.txt", "w");/*以写模式("w")打开文件user.txt,如果不存在,会自动创建*/
	int start = clock();
	//fputs(pas, fp);/*将名称和密码以字符串形式写入文件*/
	sudo[0][0] = 1;
	//fprintf(fp, "请输入\n");
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
			create();
		}
		jiaohan_1(snum1); 
		jiaohan_2(snum2); //判断当前两个参数表示哪两种顺序
		//输出数独
		for (int i = 0; i < 9; i++)
		{
			int k = i;
			if (k >= 3 && k <= 5) k = c1[k - 3]; //如果当前是中间三行，按照顺序输出
			else if (k > 5) k = c2[k - 6];       //如果当前是中间三行，按照顺序输出

			for (int j = 0; j < 8; j++) {
				x = sudo[k][j] + '0'; //转换成字符型
				fputc(x, fp);         //写入文件
				fprintf(fp, " ");      
			}
			x = sudo[k][8] + '0';
			fputc(x, fp);
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
	int end = clock();
	printf("消耗的时间为：%dms\n", end - start);
	return 0;
}



