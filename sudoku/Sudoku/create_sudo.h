#pragma once
void produce(int sudo[9][9]);  //第一行已知，通过变换得到完整的数独终局

void swap(int& a, int& b); //交换函数，交换a和b

bool nextPermutation(int* p, int n); //全排列函数

void jiaohan_1(int s1, int* c1);     //中间4，5，6行的变换

void jiaohan_2(int s2, int* c2);     //最后7，8，9行的变换

void init(int sudo[9][9], int p[8]); //初始化，规定左上角第一个为1，第一行为123456789

void output(int sudo[9][9], FILE* fp);  //输出函数

void change(); //行变换的参数设置

void create(int N); //生成N个数独终局并写入文件