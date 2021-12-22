/**
 * @file Solution.cpp
 * @brief 
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021  Laobai
 * 
 */
#include "Solution.h"
#include <iostream>
using namespace std;

void Solution::test() {
    int num_of_nodes;
    int num_of_edges;
    cout << "输入电网的顶点数和边数: ";
    while (true) {
        cin >> num_of_nodes >> num_of_edges;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(0xffff, '\n');
            cerr << "Bad input_expression" << endl;
            continue;
        }
        break;
    }
    Kruskal k1(num_of_edges, num_of_nodes);
}