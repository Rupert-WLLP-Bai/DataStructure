/*
@file:        main.cpp
@description: 主函数
@version:     v1.0.1
@author:      Laobai
@time:        2021年10月25日22:27:39
*/

/*
update notes:
v1.0.0 2021年10月10日10:20:39
	  in v1.0.1:
		1. 加入递归解法，之后修改菜单
v1.0.1 2021年10月25日22:27:39
	  in v1.0.2:
        1. 加入多线程解法的菜单(在Java下已实现)
*/

/*
@name:		  main.cpp
@description: 主函数
@version:     v1.0.1
@author:      Laobai
@time:        2021年11月4日23:21:03
*/

/*
update notes:

v1.0.0 2021年10月26日16:11:39
v1.0.1 2021年11月4日23:21:03
*/

#include <iostream>
#include "N_Queen.h"
#include "tool.h"
using namespace std;

int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif

    enum methods {
        RECURSIVE = 1,
        NO_RECURSIVE,
        MULTITHREADING
    };
    int max;     //N的大小
    int method;  //递归或者非递归
    get_input(max, 1, 20, "N皇后问题，请输入N的大小(≤20): ");
    get_input(method, RECURSIVE, MULTITHREADING, "请选择解法,1为递归方式，2为非递归方式，3为多线程方式: ");
    N_Queen N(max);
    switch (method) {
        case RECURSIVE:
            N.solve_Recursive();
            break;
        case NO_RECURSIVE:
            N.solve_noRecursive();
            break;
        case MULTITHREADING:
            N.solve_Multithreading();
        default:
            throw runtime_error("无效参数");
    }
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
