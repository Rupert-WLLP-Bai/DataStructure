#include "solution.h"
#include <iostream>
#include "binary_search_tree.h"
#include "tools.h"

using namespace std;

//1. 获取操作 第一次只能选择建立(可以输入为空)
void first_input(binary_search_tree<int>& tree) {
    while (true) {
        print_menu();
        int choice = fetch_choice();
        if (choice == QUIT) {
            cout << "Exit in first input" << endl;
            tree.destory();
            exit(0);
        } else if (choice != CREATE) {
            cout << "第一次只能选择建立操作，输入回车即建立空树,按回车继续" << endl;
            getchar();  //输入回车继续
#ifdef _WIN32
            int res = system("cls");
#else
            int res = system("clear");
#endif
            continue;
        } else {
            int temp;
            cout << "输入一些数(用空格分隔)以建立二叉排序树，输入回车则建立空树,任意输入一个字母为终止符"
                 << endl;
            while (cin >> temp) {
                tree.insert(temp);
            }
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "------ 建 立 成 功 ------" << endl;
            cout << "Binary_search_tree is :" << endl;
            tree.inOrder();
            cout << endl;
            cout << "--------------------" << endl;
            return;
        }
    }
}

//2. 第二次开始禁用建立操作 只能选择插入 查询 退出
void other_input(binary_search_tree<int>& tree) {
    while (true) {
        print_menu();
        int choice = fetch_choice();
        if (choice == QUIT) {
            cout << "Exit in input" << endl;
            tree.destory();
            exit(0);
        } else if (choice == CREATE) {
            cout << "BSTree已存在，请使用插入和查询操作" << endl;
            continue;
        } else if (choice == INSERT) {
            while (true) {
                int temp;
                cout << "输入插入的数" << endl;
                cin >> temp;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT32_MAX, '\n');
                    cout << "输入错误！" << endl;
                    continue;
                } else {
                    tree.insert(temp);
                    cout << "------ 插 入 成 功 ------" << endl;
                    break;
                }
            }

        } else if (choice == SEARCH) {
            while (true) {
                int temp;
                cout << "输入搜索的数" << endl;
                cin >> temp;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT32_MAX, '\n');
                    cout << "输入错误！" << endl;
                    continue;
                } else if (choice == SEARCH) {
                    BSNode<int>* val = tree.search_recursion(temp);
                    if (val != nullptr)
                        cout << "查找成功" << endl;
                    else
                        cout << "查找失败" << endl;
                    break;
                }
            }
        } else {
            cout << "---------- 输 出 ----------" << endl;
            tree.print();
            cout << "----------结 束 ----------" << endl;
        }
    }
}

//主循环 (程序主体)
void solution() {
    binary_search_tree<int> tree;
    //第一次输入建立
    first_input(tree);
    //其他输入
    other_input(tree);
}