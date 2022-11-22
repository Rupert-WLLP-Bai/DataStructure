// 队列接口
#pragma once

template<class T>
class Queue {
public:
    virtual unsigned int size() const = 0;
    virtual T &front() = 0;
    virtual void push(T &x) = 0;
    virtual void push(const T &x) = 0;
    virtual void pop() = 0;
    virtual T &back() = 0;
    virtual bool empty() = 0;
};