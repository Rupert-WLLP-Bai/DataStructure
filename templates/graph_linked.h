/**
 * @file graph_linked.h
 * @brief 邻接表表示的图
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021  Laobai
 * 
 */

#pragma once
#include <iostream>
#include "graph.h"
using namespace std;
template <class T, class E>
struct Edge {
    int dest;          //边节点顶点号
    E weight;          //边的权职
    Edge<T, E>* link;  //下一个邻接点链接
    Edge() {}          //构造函数
    Edge(int num, E cost)
        : dest(num), weight(cost), link(NULL) {}  //构造函数
    bool operator!=(Edge<T, E>& R) const {        //判断不等否
        return (dest != R.dest)
    }
};
template <class T, class E>
struct Vertex {       //顶点的定义
    T data;           //顶点的信息
    Edge<T, E>* adj;  //边链表的头指针
    Vertex()
        : adj(NULL) {}
};

template <class T, class E>
class Graphlnk : public Graph<T, E> {                             //邻接表图，带权无向图
    friend istream& operator>>(istream& in, Graphmtx<T, E>& G);   //输入
    friend ostream& operator<<(ostream& out, Graphmtx<T, E>& G);  //输出
   public:
    Graphlnk(int sz = DefaultVertices);  //构造函数
    ~Graphlnk();                         //析构函数
    T getValue(int i) {                  //取得位置为i的顶点的值
        return (i > -1 && i < numVertices) ? NodeTable[i].data : 0;
    }
    E getWeight(int v1, int v2);              //返回边的权值
    bool insertVertex(const T& vertex);       //插入顶点
    bool insertEdge(int v1, int v2, E cost);  //插入边
    bool removeEdge(int v1, int v2);          //删除边
    bool removeVertex(int v);                 //删除一个顶点v
    int getFirstNeighbor(int v);              //取顶点v的第一个邻接点
    int getNextNeighbor(int v, int w);        //取v的邻接点w的下一个邻接点
    int getVertexPos(const T& vertex) {       //给出顶点vertex在图中的位置
        for (int i = 0; i < numVertices; i++) {
            if (NodeTable[i].data == vertex)
                return i;
        }
        return -1;
    }

   private:
    Vertex<T, E>* NodeTable;  //顶点表
};

template <class T, class E>
Graphlnk<T, E>::Graphlnk(int sz) {
    //构造函数，建立一个空邻接表
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    NodeTable = new Vertex<T, E>[maxVertices];  //创建邻接表
    if (NodeTable == NULL) {
        cerr << "存储分配失败";
        exit(1);
    }
};
template <class T, class E>
Graphlnk<T, E>::~Graphlnk() {
    //析构函数，释放链接表空间
    for (int i = 0; i < numVertices; i++) {
        Edge<T, E>* p = NodeTable[i].adj;  //找到其对应边链表的首节点
        while (p != NULL) {                //不断的删除第一个节点
            NodeTable[i].adj = p->link;
            delete p;
            p = NodeTable[i].adj;
        }
    }
    delete[] NodeTable;  //删除顶点表数组
};

template <class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {  //取顶点v的第一个邻接点
    //成功返回邻接点位子，否则返回-1
    if (v != -1) {                         //顶点v存在
        Edge<T, E>* p = NodeTable[v].adj;  //对应链表的第一个邻接点
        if (p != NULL)
            return p->dest;  //存在返回第一个邻接点
    }
    return -1;
};
template <class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) {
    //取顶点v的邻接点w的下一个邻接点的位置，若有返回下一个邻接点，否则返回-1。
    if (v != -1 && w != -1) {
        Edge<T, E>* p = NodeTable[v].adj;
        while (p != NULL && p->link != NULL) {
            if (p->dest == w)
                return p->link->dest;  //返回下一个邻接点
        }
    }
    return -1;  //下一个邻接点不存在
};
template <class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2) {
    //函数返回边(v1,v2)上的权值, 若该边不在图中, 则函数返回最大整数值。
    if (v1 != -1 && v2 != -1) {
        Edge<T, E>* p = NodeTable[v1].adj;  //v1的第一条关联边
        while (p != NULL && p->dest != v2)  //单入口，单出口
            p = p->link;
        if (p != NULL)
            return p->dest;  //找到
    }
    return maxWeight;  //找不到(v1,v2)，返回最大整数值
};
template <class T, class E>
bool Graphlnk<T, E>::insertVertex(const T& vertex) {
    //在图的顶点表中插入一个新顶点vertex。若插入成功，函数返回true, 否则返回false。
    if (numVertices == maxVertices)
        return false;
    else {
        NodeTable[numVertices].data = vertex;  //插在表尾
        numVertices++;
        return true;
    }
};
template <class T, class E>
bool Graphlnk<T, E>::removeVertex(int v) {
    //在图中删除一个指定顶点v, v 是顶点号。若删除成功, 函数返回true, 否则返回false。
    if (numVertices == 1 || v < 0 || v >= numVertices)  //表空或顶点号超出范围
        return false;

    if (v != numVertices - 1) {
        NodeTable[v].data = NodeTable[numVertices - 1].data;
        NodeTable[v].adj = NodeTable[numVertices - 1].adj;
    }

    Edge<T, E>*p, *q = NULL;
    for (int i = 0; i < numVertices - 2; i++) {  //逐行删除边节点v
        p = NodeTable[i].adj;
        while (p != NULL && p->dest != v) {
            q = p;
            p = p->link;
        }
        if (p != NULL) {                //找到（i，v）
                                        //以i为头删（i，v）
            if (p == NodeTable[i].adj)  //（i，v）在头节点
                NodeTable[i].adj = p->link;
            else  //不是
                q->link = p->link;
            delete p;
        }
    }

    for (int i = 0; i < numVertices - 2; i++) {  //逐行删除边节点v
        p = NodeTable[i].adj;
        while (p != NULL && p->dest != numVertices - 2) {
            p = p->link;
        }
        if (p != NULL) {
            p->dest = v;
        }
    }

    return true;
};

template <class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
    //在带权图中插入一条边(v1,v2), 若此边存在或参数不合理，函数返回false, 否则返回
    //true。对于非带权图, 最后一个参数weight 不要。算法中相应语句也不要。
    if (v1 != -1 && v1 >= 0 && v1 < numVertices &&
        v2 != -1 && v2 >= 0 && v2 < numVertices) {
        Edge<T, E>*q, *p = NodeTable[v1].adj;  //v1 对应的边链表头指针
        while (p != NULL && p->dest != v2)     //寻找邻接顶点v2
            p = p->link;
        if (p != NULL)
            return false;    //找到此边, 不插入
        p = new Edge<T, E>;  //否则, 创建新结点
        p->dest = v2;
        p->weight = weight;
        p->link = NodeTable[v1].adj;  //链入v1 边链表表头
        NodeTable[v1].adj = p;
        q = new Edge<T, E>;  //否则,创建新结点
        q->dest = v1;
        q->weight = weight;
        q->link = NodeTable[v2].adj;  //链入v2 边链表表头
        NodeTable[v2].adj = q;
        numEdges++;
        return true;
    }
    return false;
};
template <class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2) {
    //在图中删除一条边(v1, v2)
    if (v1 != -1 && v2 != -1) {
        Edge<T, E>*p = NodeTable[v1].adj, *q = NULL;
        while (p != NULL && p->dest != v2) {
            q = p;
            p = p->link;
        }
        if (p != NULL) {  //找到（v1，v2）
            //以v1为头删（v1，v2）
            if (p == NodeTable[v1].adj)  //（v1，v2）在头节点
                NodeTable[v1].adj = p->link;
            else  //不是
                q->link = p->link;
            delete p;

            p = NodeTable[v2].adj;  //再以v2为头删（v2，v1）
            while (p->dest != v1) {
                q = p;
                p = p->link;
            }  //寻找被删边结点
            if (p == NodeTable[v2].adj)
                NodeTable[v2].adj = p->link;  //该结点是边链表首结点
            else
                q->link = p->link;  //不是, 重新链接
            delete p;
            return true;
        }
    }
    return false;
};
