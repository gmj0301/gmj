#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "create_sudo.h"
#include "solve_sudo.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Please enter the correct command!\n");
		return 0;
	}
	int start = clock(); 
	int end = 0;
	if (!strcmp(argv[1], "-s"))
	{
		solve(argv[2]);
		end = clock();
		printf("求解成功！\n");
	}
	else if (!strcmp(argv[1], "-c"))
	{
		int n = atoi(argv[2]);
		if (n <= 0 || n > 1000000)
		{
			printf("Please enter the correct data range!\n");
			return 0;
		}

		create(n);
		end = clock();
		printf("生成成功！\n");
	}

	printf("消耗时间：%dms\n", end - start);
	return 0;
}
