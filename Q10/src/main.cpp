/*
@name:		  main.cpp
@description: 主函数
@version:     v1.0.0
@author:      Laobai
@time:        2021年10月19日17:41:13
*/

/*
update notes:

v1.0.0 2021年10月19日17:41:13
*/
#include <iostream>
#include "mymenu.h"
using namespace std;

int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    mainloop();
    return 0;
}
