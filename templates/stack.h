//栈的类定义
#pragma once
const int maxSize = 50;
template <class T>
class Stack {
   public:
    Stack(){};                            //构造函数
    virtual void push(const T& x) = 0;    //元素x进栈
    virtual bool pop(T& x) = 0;           //栈顶元素出栈，由x返回
    virtual bool getTop(T& x) const = 0;  //读取栈顶元素，由x返回
    virtual bool empty() const = 0;
    virtual bool full() const = 0;
    virtual int getSize() const = 0;  //计算栈中元素个数
};