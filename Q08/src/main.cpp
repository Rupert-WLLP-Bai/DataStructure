/**
 * @file main.cpp
 * @brief 主函数
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021  Laobai
 * 
 */
#include "Solution.h"
#include <iostream>
int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    Solution::test();
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

