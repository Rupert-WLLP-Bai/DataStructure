/*
@name:		  main.cpp
@description: 主函数
@version:     v1.0.1
@author:      Laobai
@time:        2021年11月4日23:15:59
*/

/*
update notes:
v1.0.0 2021年10月22日11:06:54
v1.0.1 2021年11月4日23:15:59
*/

#include "joseph.h"
int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    Solution();
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}