#pragma once
void produce(int sudo[9][9]);  //��һ����֪��ͨ���任�õ������������վ�

void swap(int& a, int& b); //��������������a��b

bool nextPermutation(int* p, int n); //ȫ���к���

void jiaohan_1(int s1, int* c1);     //�м�4��5��6�еı任

void jiaohan_2(int s2, int* c2);     //���7��8��9�еı任

void init(int sudo[9][9], int p[8]); //��ʼ�����涨���Ͻǵ�һ��Ϊ1����һ��Ϊ123456789

void output(int sudo[9][9], FILE* fp);  //�������

void change(); //�б任�Ĳ�������

void create(int N); //����N�������վֲ�д���ļ�