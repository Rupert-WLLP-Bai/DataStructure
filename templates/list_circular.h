/**
 * @file list_circular.h
 * @brief 单向循环链表
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-11-07
 * 
 * @copyright Copyright (c) 2021  Laobai
 * 
 */

/*
update notes:

v1.0.0 2021年10月22日11:07:25
      in v1.0.1:
        1. 注释的位置放在某一行的上一行(***改掉行尾注释)

v1.0.1 2021年10月23日11:53:47
      in v1.0.2
        1. 继承list.h 最后整合在一个头文件里
*/

#pragma once
#include <iomanip>
#include <iostream>
#include "list.h"
using namespace std;

//链表结点定义
template <class T>
struct CircLinkNode
{
    T data;
    CircLinkNode<T>* Link;
    explicit CircLinkNode(CircLinkNode<T>* Link = NULL)
        : data(0), Link(Link){};
    explicit CircLinkNode(T d, CircLinkNode<T>* Link = NULL)
        : data(d), Link(Link) {}
};

//循环链表
template <class T>
class CircList {
   public:
    CircList();                                            //无参构造函数
    explicit CircList(const T& x);                                  //构造函数
    CircList(CircList<T>& L);                              //复制构造函数
    ~CircList()= default;                                        //析构函数
    int length() const { return len; }                  //计算循环链表长度
    bool empty() { return len == 0; }  //判空
    CircLinkNode<T>* getHead() const { return head; }      //返回附加头结点地址
    CircLinkNode<T>* search(T x);                          //搜索含数据x的元素
    CircLinkNode<T>* locate(int i);                        //搜索第i个元素的地址
    T* getData(int i);                                     //取出第i个元素的值
    void setData(int i, T& x);                             //用x修改第i个元素的值
    bool insert(int i, T& x);                              //在第i个元素后插入x
    bool remove(int i, T& x);                              //删除第i个元素，x返回该元素的值
    void output();                                         //输出

   private:
    CircLinkNode<T>* head;  //头指针
    int len;             //链表长度
};

//无参构造
template <class T>
CircList<T>::CircList() {
    len = 0;
    head = new CircLinkNode<T>;
    head->Link = head;
}

//带参构造
template <class T>
CircList<T>::CircList(const T& x) {
    len = 0;
    head = new CircLinkNode<T>;
    CircLinkNode<T>* newNode = new CircLinkNode<T>(x);
    head->Link = newNode;
    newNode->Link = head;
    len++;
}

//拷贝构造
template <class T>
CircList<T>::CircList(CircList<T>& L) {
    len = 0;
    T value;
    CircLinkNode<T>* srcptr = L.getHead();  //被复制链表的头结点位置
    head = new CircLinkNode<T>;
    CircLinkNode<T>* destptr = head;
    while (srcptr->Link != L.getHead()) {
        //逐个节点复制
        value = srcptr->Link->data;
        destptr->Link = new CircLinkNode<T>(value);
        destptr = destptr->Link;
        srcptr = srcptr->Link;
        len++;
    }
    destptr->Link = head;
}

//搜索元素x的地址
template <class T>
CircLinkNode<T>* CircList<T>::search(T x) {
    CircLinkNode<T>* current = head->Link;
    while (current != head) {
        if (current->data == x)
            return current;
        else
            current = current->Link;
    }
    return NULL;  //未找到
}

//定位
template <class T>
CircLinkNode<T>* CircList<T>::locate(int i) {
    if (i < 0 || i > len)
        return NULL;
    CircLinkNode<T>* current = head;
    while (i--) {
        current = current->Link;
    }
    return current;
}

//定位到第i个元素的位置,返回data的地址
template <class T>
T* CircList<T>::getData(int i) {
    if (i <= 0 || i > len)
        return NULL;
    CircLinkNode<T>* current = locate(i);
    return &current->data;
}

//设置value
template <class T>
void CircList<T>::setData(int i, T& x) {
    if (i <= 0 || i > len)
        return;
    else {
        CircLinkNode<T>* current = locate(i);
        current->data = x;
    }
}

//插入
template <class T>
bool CircList<T>::insert(int i, T& x) {
    CircLinkNode<T>* current = locate(i);
    if (current == NULL)
        return false;  //插入不成功
    CircLinkNode<T>* newNode = new CircLinkNode<T>(x);
    if (newNode == NULL) {
        cerr << "存储分配错误！" << endl;
        exit(1);
    }
    newNode->Link = current->Link;  //链接到current之后
    current->Link = newNode;
    len++;     //长度+1
    return true;  //插入成功
}

//将链表中的第i个元素删去，通过引用型参数x返回该元素的值
template <class T>
bool CircList<T>::remove(int i, T& x) {
    if (empty() == true)
        return false;  //空表,删除失败
    CircLinkNode<T>* current = locate(i - 1);
    if (current == NULL)
        return false;  //位置不对
    CircLinkNode<T>* del = current->Link;
    current->Link = del->Link;
    x = del->data;
    delete del;
    len--;
    return true;  //删除成功
}

//输出
template <class T>
void CircList<T>::output() {
    if (len == 0)
        cout << "(HEAD)NULL ， 空表" << endl;
    else {
        int num = 1;
        CircLinkNode<T>* current = head;
        while (current->Link != head) {
            current = current->Link;
            cout << current->data;
            cout << "(ID:" << num++ << ")";  //输出Id
            cout << " --> ";
        }
        cout << head->Link->data << "(HEAD)"
             << "  链表长度为：" << len << endl;
    }
}