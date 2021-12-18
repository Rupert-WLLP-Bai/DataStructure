/*
@name:		  main.cpp
@description: 主函数
@version:     v1.0.2
@author:      Laobai
@time:        2021年10月22日22:03:38
*/

/*
update notes:

v1.0.0 2021年9月21日10:56:35
    TODO in v1.0.1
        1. 注释的位置放在某一行的上一行(***改掉行尾注释)

v1.0.1 2021年10月22日22:03:38

v1.0.2 2021年11月4日14:48:15
    1.兼容Linux和Windows
*/

#include <iostream>
#include "core.h"

int main() {
    
#ifdef _WIN32
    system("chcp 65001");
#endif
    int ret;
    Table T;
    /* 创建并输出现有的表 */
    T.Spawn();
    T.Print();
    /* 进入主循环 */
    while (true) {
        fetch_choice(ret, T);
        if (ret == 0) {
            cout << "退出程序" << endl;
            break;
        }
    }
    return 0;
}
