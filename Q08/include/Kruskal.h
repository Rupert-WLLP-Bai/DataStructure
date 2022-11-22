/**
 * @file Kruskal.h
 * @brief 最小生成树
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-12-14
 *
 * @copyright Copyright (c) 2021  Laobai
 *
 */
//#include <queue>

#define MAX_V 1000

#include "min_heap.h"

/**
 * @brief 边的定义
 */
struct Edge {
    int from, to;
    int cost;

    bool operator==(const Edge &rhs) const {
        return cost == rhs.cost;
    }

    bool operator!=(const Edge &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Edge &rhs) const {
        return cost < rhs.cost;
    }

    bool operator>(const Edge &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Edge &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Edge &rhs) const {
        return !(*this < rhs);
    }
};

class Kruskal {
private:
    //std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> min_heap;  //小顶堆
    MinHeap<Edge> minHeap;
    int find(int x);                                                      // find函数
    bool judge();                                                         //判断是否存在最小生成树
    int *father;                                                          //并查集
    int num_of_edges;                                                     //边数
    int num_of_nodes;                                                     //顶点数
    int min_value;                                                              //最小生成树
    void calculate_min_value();                                           //计算最小代价并输出
    void input_data();                                                    //读取输入
public:
    Kruskal(int num_of_edges, int num_of_nodes);  //构造
    ~Kruskal();                                   //析构
};
