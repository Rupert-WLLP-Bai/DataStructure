/**
 * @file graph.h
 * @brief 图的定义
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021  Laobai
 * 
 */
#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_HW
const int maxWeight = 0x7fffffff;  //代表无穷大的值
const int DefaultVertices = 30;    //默认最大顶点数(=n)
template <class T, class E>
class Graph {  //图的类定义
   public:
    bool GraphEmpty() const {  //判图空否
        if (numEdges == 0)
            return true;
        else
            return false;
    }
    bool GraphFull() const {  //判图满否
        if (numVertices == maxVertices ||
            numEdges == maxVertices * (maxVertices - 1) / 2)
            return true;
        else
            return false;
    }
    int NumberOfVertices() { return numVertices; }        //返回当前顶点数
    int NumberOfEdges() { return numEdges; }              //返回当前边数
    virtual T getValue(int i) = 0;                        //取顶点i 的值,i 不合理返回0
    virtual E getWeight(int v1, int v2) = 0;              //取边(v1,v2)上的权值
    virtual int getFirstNeighbor(int v) = 0;              //取顶点v 的第一个邻接顶点
    virtual int getNextNeighbor(int v, int w) = 0;        //取邻接顶点w 的下一邻接顶点
    virtual bool insertVertex(const T& vertex) = 0;       //插入一个顶点vertex
    virtual bool insertEdge(int v1, int v2, E cost) = 0;  //插入边(v1,v2),权为cost
    virtual bool removeVertex(int v) = 0;                 //删去顶点v 和所有与相关联边
    virtual bool removeEdge(int v1, int v2) = 0;          //在图中删去边(v1,v2)
    virtual int getVertexPos(const T& vertex) = 0;        //给出顶点vertex 在图中位置
   protected:
    int maxVertices;  //图中最大顶点数
    int numEdges;     //当前边数
    int numVertices;  //当前顶点数
};

#endif  //DATASTRUCTURE_GRAPH_H
