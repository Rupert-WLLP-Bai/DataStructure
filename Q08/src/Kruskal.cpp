/**
 * @file Kruskal.cpp
 * @brief 最小生成树
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-12-14
 *
 * @copyright Copyright (c) 2021  Laobai
 *
 */

#include "Kruskal.h"
#include <iostream>

using namespace std;

/**
 * @brief Construct a new Kruskal:: Kruskal object
 * @param  num_of_edges     边数
 * @param  num_of_nodes     顶点数
 */
Kruskal::Kruskal(int num_of_edges, int num_of_nodes) {
    this->num_of_edges = num_of_edges;
    this->num_of_nodes = num_of_nodes;
    this->min_value = 0;
    this->father = new int[MAX_V];
    input_data();
    calculate_min_value();
}

/**
 * @brief Destroy the Kruskal:: Kruskal object
 */
Kruskal::~Kruskal() {
    delete[] father;
}

/**
 * @brief 计算最小代价并输出
 */
void Kruskal::calculate_min_value() {
    int num = 0;
//    while (!min_heap.empty() && num != num_of_nodes - 1) {
//        Edge temp = min_heap.top();
//        min_heap.pop();
//        int father_x = find(temp.from);
//        int father_y = find(temp.to);
//        if (father_x != father_y) {
//            father[father_y] = find(father[father_x]);
//            cout << temp.from << " --> " << temp.to << " = " << temp.cost << endl;
//            min_value += temp.cost;
//            num++;
//        }
//    }
    while (minHeap.getSize()!=0 && num != num_of_nodes - 1) {
        Edge temp = minHeap.getTop();
        minHeap.remove(minHeap.getTop());
        int father_x = find(temp.from);
        int father_y = find(temp.to);
        if (father_x != father_y) {
            father[father_y] = find(father[father_x]);
            cout << temp.from << " --> " << temp.to << " = " << temp.cost << endl;
            min_value += temp.cost;
            num++;
        }
    }
    for (int i = 1; i <= num_of_nodes; i++) {
        father[i] = find(father[i]);
    }
    if (judge()) {
        cout << "min_value = " << min_value << endl;
    } else {
        cout << "min_value doesn't exist!" << endl;
    }
}

/**
 * @brief 并查集find函数
 * @param  x
 * @return int 父节点
 */
inline int Kruskal::find(int x) {
    return x == father[x] ? x : find(father[x]);
}

/**
 * @brief 判断是否存在最小生成树
 * @return true 存在
 */
inline bool Kruskal::judge() {
    int flag = father[1];
    for (int i = 2; i != num_of_nodes + 1; i++) {
        if (flag != find(father[i])) {
            return false;
        }
    }
    return true;
}

/**
 * @brief 读取输入
 */
void Kruskal::input_data() {
    for (int i = 1; i <= num_of_nodes; i++) {
        father[i] = i;
    }
    for (int i = 0; i < num_of_edges; i++) {
        int from;
        int to;
        int cost;
        while (true) {
            cout << "依次输入第" << i+1 << "条边的参数(起始顶点、终止顶点、权值)" << endl;
            cin >> from >> to >> cost;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(0xffff, '\n');
                cerr << "Bad input" << endl;
                continue;
            }
            break;
        }
        Edge a{};
        a.from = from;
        a.to = to;
        a.cost = cost;
        minHeap.insert(a);
    }
}