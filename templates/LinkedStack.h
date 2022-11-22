//
// Created by Administrator on 2021/12/21.
//

#ifndef DATASTRUCTURE_STACK_LINKED_H
#define DATASTRUCTURE_STACK_LINKED_H

#include "laobai_stack.h"
#include<iostream>

template<class T>
struct StackNode {
    T data;
    StackNode<T> *link;

    explicit StackNode(StackNode<T> *ptr = nullptr) {
        link = ptr;
    }

    explicit StackNode(const T &item, StackNode<T> *ptr = nullptr) {
        data = item;
        link = ptr;
    }
};

template<class T>
class LinkedStack : public Stack<T> {
public:
    LinkedStack();
    ~LinkedStack();
    bool empty() override;
    void pop() override;
    void push(const T &data) override;
    T top() override;
    unsigned int size() override;
private:
    unsigned int _size{};
    StackNode<T> *_top;
};

/**
 * 构造函数，初始化栈的大小为0，给根节点分配空间
 * @tparam T
 */
template<class T>
LinkedStack<T>::LinkedStack() {
    this->_size = 0;
    this->_top = nullptr;
}

/**
 * 析构函数，释放头结点
 * @tparam T
 */
template<class T>
LinkedStack<T>::~LinkedStack() {
    delete this->_top;
}

/**
 * 判断栈是否为空
 * @tparam T
 * @return 栈空返回true
 */
template<class T>
inline bool LinkedStack<T>::empty() {
    return _size == 0;
}

/**
 * 从栈中弹出元素
 * @tparam T
 */
template<class T>
void LinkedStack<T>::pop() {
    if (this->_size == 0) {
        throw std::runtime_error("stack is empty!");
    }
    StackNode<T> *temp = this->_top;
    this->_top = this->_top->link;
    delete temp;
    this->_size--;
}

/**
 * 获取栈顶元素
 * @tparam T
 * @return 栈顶元素
 */
template<class T>
T LinkedStack<T>::top() {
    if (this->_size == 0) {
        throw std::runtime_error("stack is empty!");
    }
    return this->_top->data;
}

/**
 * 将元素压入栈中
 * @tparam T
 * @param data
 */
template<class T>
void LinkedStack<T>::push(const T &data) {
    auto *newTop = new StackNode<T>(data, this->_top);
    if (newTop == nullptr) {
        throw std::bad_alloc();
    }
    this->_top = newTop;
    this->_size++;
}

/**
 * 获取栈内元素的数量
 * @tparam T
 * @return 元素的数量
 */
template<class T>
unsigned int LinkedStack<T>::size() {
    return this->_size;
}

#endif //DATASTRUCTURE_STACK_LINKED_H
