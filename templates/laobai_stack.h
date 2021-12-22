//
// Created by Laobai on 2021/12/21.
//

#ifndef DATASTRUCTURE_LAOBAI_STACK_H
#define DATASTRUCTURE_LAOBAI_STACK_H

template<class T>
class Stack {
public:
    virtual bool empty() = 0;
    virtual void pop() = 0;
    virtual T top() = 0;
    virtual void push(const T &data) = 0;
    virtual unsigned int size() = 0;

private:
    unsigned int _size{};
};

#endif //DATASTRUCTURE_LAOBAI_STACK_H
