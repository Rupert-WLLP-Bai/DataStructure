#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
using namespace std;

#define CLEAR 0
#define CREATE 1
#define INSERT 2
#define SEARCH 3
#define QUIT 4
#define PRINT 5
//菜单
void print_menu();
//获取选择
int fetch_choice();

void print_menu() {
    cout << "**                    二叉排序树                    **" << endl;
    cout << "======================================================" << endl;
    cout << "**                0.刷新屏幕                        **" << endl;
    cout << "**                1.建立二叉排序树                  **" << endl;
    cout << "**                2.插入元素                        **" << endl;
    cout << "**                3.搜索元素                        **" << endl;
    cout << "**                4.退出程序                        **" << endl;
    cout << "**                5.输出二叉排序树                  **" << endl;
    cout << "======================================================" << endl;
    cout << "注: 数据范围(" << INT32_MIN << " ~ " << INT32_MAX << ")" << endl;
    cout << endl;
}

int fetch_choice() {
    int choice;
    while (1) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT32_MAX, '\n');
            cout << "输入错误！" << endl;

            continue;
        } else if (choice < 0 || choice > 5) {
            cout << "输入超限！" << endl;
            continue;
        } else if (choice == CLEAR) {
#ifdef _WIN32
            int res = system("cls");
#else
            int res = system("clear");
#endif
            print_menu();
        } else
            return choice;
    }
}

#endif