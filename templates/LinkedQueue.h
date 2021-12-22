//
// Created by Laobai on 2021/12/22.
// 链式队列
//

#ifndef DATASTRUCTURE_TEMPLATES_LINKEDQUEUE_H_
#define DATASTRUCTURE_TEMPLATES_LINKEDQUEUE_H_

#include "queue.h"
#include <iostream>
/**
 * 定义队列结点
 * @tparam T
 */
template<class T>
struct QueueNode {
    T data;
    QueueNode<T> *link;

    explicit QueueNode(QueueNode<T> *ptr = nullptr) {
        link = ptr;
    }

    explicit QueueNode(const T &item, QueueNode<T> *ptr = nullptr) {
        data = item;
        link = ptr;
    }
};

/**
 * 实现链式队列
 * @tparam T
 */
template<class T>
class LinkedQueue : public Queue<T> {
public:
    virtual ~LinkedQueue();
    LinkedQueue();
    unsigned int size() const override;
    T &front() override;
    void push(T &x) override;
    void push(const T &x) override;
    void pop() override;
    T &back() override;
    bool empty() override;
private:
    unsigned int queue_size{};
    QueueNode<T> *head;//头指针
    QueueNode<T> *rear;//尾指针
};

/**
 * 求队列元素数量
 * @tparam T
 * @return 队列元素数量
 */
template<class T>
unsigned int LinkedQueue<T>::size() const {
    return this->queue_size;
}

/**
 * 求队列头部元素
 * @tparam T
 * @return 队列头部元素
 */
template<class T>
T &LinkedQueue<T>::front() {
    if (this->queue_size == 0) {
        throw std::runtime_error("queue is empty!");
    }
    return this->head->data;
}

template<class T>
void LinkedQueue<T>::push(T &x) {
    auto *newNode = new QueueNode<T>(x);
    if (newNode == nullptr) {
        throw std::bad_alloc();
    }
    /* 空队列时，新结点同时为队头和队尾 */
    if (this->head == nullptr) {
        this->head = this->rear = newNode;
        this->queue_size++;
    } else {
        /* 接到队尾之后*/
        this->rear->link = newNode;
        this->rear = newNode;
        this->queue_size++;
    }
}

template<class T>
void LinkedQueue<T>::push(const T &x) {
    auto *newNode = new QueueNode<T>(x);
    if (newNode == nullptr) {
        throw std::bad_alloc();
    }
    /* 接到队尾之后*/
    this->rear->link = newNode;
    this->rear = newNode;
    this->queue_size++;
}

/**
 * 弹出队头元素
 * @tparam T
 */
template<class T>
void LinkedQueue<T>::pop() {
    if (this->queue_size == 0) {
        throw std::runtime_error("queue is empty!");
    }
    /* 队头指针向下一个位置移动 */
    QueueNode<T> *temp = this->head;
    this->head = this->head->link;
    delete temp;
    this->queue_size--;
}

/**
 * 求队列尾部元素
 * @tparam T
 * @return 队列尾部元素
 */
template<class T>
T &LinkedQueue<T>::back() {
    if (this->queue_size == 0) {
        throw std::runtime_error("queue is empty!");
    }
    return this->rear->data;
}

/**
 * 队列判空
 * @tparam T
 * @return
 */
template<class T>
bool LinkedQueue<T>::empty() {
    return this->queue_size == 0;
}

template<class T>
LinkedQueue<T>::LinkedQueue() {
    this->queue_size = 0;
    this->head = nullptr;
    this->rear = nullptr;
}

template<class T>
LinkedQueue<T>::~LinkedQueue() {
    delete this->head;
    delete this->rear;
}

#endif //DATASTRUCTURE_TEMPLATES_LINKEDQUEUE_H_
