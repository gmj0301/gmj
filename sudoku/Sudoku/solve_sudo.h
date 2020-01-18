#pragma once

void write(); //把解写入数独答案文件

bool judge(int h, int l); //剪枝函数，判断当前位置是否能放该数字

void solve_sudo(int i, int j); //深度优先搜素

void solve(const char* txt); //读数独题目文件，解数独，写入