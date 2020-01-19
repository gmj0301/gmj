#include "pch.h"
#include "CppUnitTest.h"
#include "../sudoku/create_sudo.h"
#include "../sudoku/solve_sudo.h"
#include "../sudoku/solve.cpp"
#include "../sudoku/create.cpp"
#include "../sudoku/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod_produce) //测create.cpp中的produce函数
		{
			for (int i = 0; i < 9; i++)
				sudo[0][i] = i + 1;
			produce(sudo);
			Assert::AreEqual(sudo[1][0] == 4, true);
			Assert::AreEqual(sudo[2][0] == 7, true);
			Assert::AreEqual(sudo[3][0] == 2, true);
			Assert::AreEqual(sudo[4][0] == 5, true);
			Assert::AreEqual(sudo[5][0] == 8, true);
			Assert::AreEqual(sudo[6][0] == 3, true);
			Assert::AreEqual(sudo[7][0] == 6, true);
			Assert::AreEqual(sudo[8][0] == 9, true);
		}
		TEST_METHOD(TestMethod_swap)   //测create.cpp中的swap函数
		{
			int a = 19650, b = 1698;
			swap(a, b);
			Assert::AreEqual(a == 1698, true);
			Assert::AreEqual(b == 19650, true);
			a = 1; b = 2;
			swap(a, b);
			Assert::AreEqual(a == 2, true);
			Assert::AreEqual(b == 1, true);
		}
		TEST_METHOD(TestMethod_nextPermutation) //测create.cpp中的nextPermutation函数
		{
			int s[8] = { 1,2,3,4,5,6,7,8 };
			nextPermutation(s, 8);
			Assert::AreEqual(s[0], 1);
			Assert::AreEqual(s[1], 2);
			Assert::AreEqual(s[2], 3);
			Assert::AreEqual(s[3], 4);
			Assert::AreEqual(s[4], 5);
			Assert::AreEqual(s[5], 6);
			Assert::AreEqual(s[6], 8);
			Assert::AreEqual(s[7], 7);

		}
		TEST_METHOD(TestMethod_jiaohan_1)  //测create.cpp中的jiaohan_1函数
		{
			jiaohan_1(1, c1);
			Assert::AreEqual(c1[0] == 3, true);
			jiaohan_1(2, c1);
			Assert::AreEqual(c1[2] == 4, true);
			jiaohan_1(3, c1);
			Assert::AreEqual(c1[0] == 4, true);
			jiaohan_1(4, c1);
			Assert::AreEqual(c1[2] == 3, true);
			jiaohan_1(5, c1);
			Assert::AreEqual(c1[0] == 5, true);
			jiaohan_1(6, c1);
			Assert::AreEqual(c1[1] == 4, true);
		}

		TEST_METHOD(TestMethod_jiaohan_2)  //测create.cpp中的jiaohan_2函数
		{
			jiaohan_2(1, c2);
			Assert::AreEqual(c2[0] == 6, true);
			jiaohan_2(2, c2);
			Assert::AreEqual(c2[1] == 8, true);
			jiaohan_2(3, c2);
			Assert::AreEqual(c2[2] == 8, true);
			jiaohan_2(4, c2);
			Assert::AreEqual(c2[0] == 7, true);
			jiaohan_2(5, c2);
			Assert::AreEqual(c2[0] == 8, true);
			jiaohan_2(6, c2);
			Assert::AreEqual(c2[1] == 7, true);
		}
		TEST_METHOD(TestMethod_init)  //测create.cpp中的init函数
		{
			int p[8];
			init(sudo, p);
			Assert::AreEqual(sudo[0][0] == 1, true);
			Assert::AreEqual(sudo[0][2] == 3, true);
			Assert::AreEqual(sudo[0][4] == 5, true);
			Assert::AreEqual(sudo[0][6] == 7, true);
			Assert::AreEqual(p[0] == 2, true);
			Assert::AreEqual(p[2] == 4, true);
			Assert::AreEqual(p[4] == 6, true);
			Assert::AreEqual(p[6] == 8, true);
		}
		TEST_METHOD(TestMethod_change)   //测create.cpp中的change函数
		{
			snum1 = 4; snum2 = 6;
			change();
			Assert::AreEqual(snum1 == 5, true);
			Assert::AreEqual(snum2 == 1, true);
			snum1 = 6; snum2 = 6;
			change();
			Assert::AreEqual(snum1 == 1, true);
			Assert::AreEqual(snum2 == 1, true);
			snum1 = 4; snum2 = 2;
			change();
			Assert::AreEqual(snum1 == 4, true);
			Assert::AreEqual(snum2 == 3, true);
		}
		TEST_METHOD(TestMethod_judge)  //测solve.cpp中的judge函数
		{
			sudo[0][0] = 1; sudo[2][2] = 1;
			Assert::AreEqual(judge(2, 2), false);
			sudo[0][0] = 1; sudo[0][2] = 1;
			Assert::AreEqual(judge(0, 2), false);
			sudo[0][0] = 1; sudo[2][0] = 1;
			Assert::AreEqual(judge(2, 0), false);
		}
		TEST_METHOD(TestMethod_solve_sudo) //测solve.cpp中的solve_sudo函数
		{
			int p[8];
			init(sudo, p);
			produce(sudo);
			for (int i = 0; i < 9; i++)
				sudo[0][i] = 0;
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					if (sudo[i][j] == 0)
						numl[j]++;
			solve_sudo(0, 0);
			Assert::AreEqual(sudo[0][0] == 1, true);
			Assert::AreEqual(sudo[0][1], 2);
			Assert::AreEqual(sudo[0][2], 3);
			Assert::AreEqual(sudo[0][3], 4);
		}

	};
}
