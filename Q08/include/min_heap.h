/**
 * @file min_heap.h
 * @brief 最小堆
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-11-08
 *
 * @copyright Copyright (c) 2021  Laobai
 *
 */

#pragma once

#include<iostream>

using namespace std;

/*小顶堆类定义*/
template<typename T>
class MinHeap {
public:
    MinHeap();
    ~MinHeap();
    bool insert(T val);                     //往二叉堆中插入元素
    bool remove(T data);                    //移除元素
    T getTop();                             //获取堆顶元素
    bool createMinHeap(T a[], int length);  //根据指定的数组来创建一个最小堆
    int getSize() const;

private:
    int capacity;  //容量，也即是数组的大小
    int size;      //堆小小，也即是数组中有效元素的个数
    T *heap;       //底层的数组
    void filterUp(int index);             //从index所在节点，往根节点调整堆
    void filterDown(int current, int end);  //从begin所在节点开始，向end方向调整堆
};

/*默认构造函数*/
template<typename T>
MinHeap<T>::MinHeap()
        : capacity(10), size(0), heap(nullptr) {
    heap = new T[capacity];
}

/*析构函数*/
template<typename T>
MinHeap<T>::~MinHeap() {
    delete[] heap;
}

/*获取堆顶元素*/
template<typename T>
T MinHeap<T>::getTop() {
    if (size == 0)
        throw runtime_error("nothing here");
    return heap[0];
}

/*插入元素*/
template<typename T>
bool MinHeap<T>::insert(T val) {
    if (size == capacity)  //如果数组已满，则返回false
        return false;
    heap[size] = val;
    filterUp(size);
    size++;
    return true;
}
/*从下到上调整堆*/
/*插入元素时候使用*/
template<typename T>
void MinHeap<T>::filterUp(int index) {
    T value = heap[index];  //插入节点的值，图中的12

    while (index > 0)  //如果还未到达根节点，继续调整
    {
        int indexParent = (index - 1) / 2;  //求其双亲节点
        if (value >= heap[indexParent])
            break;
        else {
            heap[index] = heap[indexParent];
            index = indexParent;
        }
    }
    heap[index] = value;  //12插入最后的位置
}

/*根据指定的数组来创建一个最小堆*/
template<typename T>
bool MinHeap<T>::createMinHeap(T a[], int length) {
    if (length > capacity)  //	堆的容量不足以创建
        return false;
    for (int i = 0; i < length; i++) {
        insert(a[i]);
    }
    return true;
}

/*删除元素*/
template<typename T>
bool MinHeap<T>::remove(T data) {
    if (size == 0)  //如果堆是空的
        return false;
    int index;
    for (index = 0; index < size; index++)  //获取值在数组中的索引
    {
        if (heap[index] == data)
            break;
    }
    if (index == size)  //数组中没有该值
        return false;

    heap[index] = heap[size - 1];  //使用最后一个节点来代替当前结点，然后再向下调整当前结点。

    filterDown(index, size--);

    return true;
}
/*从上到下调整堆*/
/*删除元素时候使用*/
template<typename T>
void MinHeap<T>::filterDown(int current, int end) {
    int child = current * 2 + 1;  //当前结点的左孩子

    T value = heap[current];  //保存当前结点的值

    while (child <= end) {
        if (child < end && heap[child] > heap[child + 1])  //选出两个孩子中较小的孩子
            child++;
        if (value < heap[child])  //无须调整；调整结束
            break;
        else {
            heap[current] = heap[child];  //孩子节点覆盖当前结点
            current = child;              //向下移动
            child = child * 2 + 1;
        }
    }
    heap[current] = value;
}

template<typename T>
int MinHeap<T>::getSize() const {
    return size;
}