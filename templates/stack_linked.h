//链式栈
#include <assert.h>
#include <iostream>
#include "stack.h"
using namespace std;

template <class T>
struct LinkNode  //结点
{
    T data;
    LinkNode<T>* link;
    LinkNode(LinkNode<T>* ptr = NULL) {
        link = ptr;
    }
    LinkNode(const T& item, LinkNode<T>* ptr = NULL) {
        data = item;
        link = ptr;
    }
};

template <class T>
class LinkedStack : public Stack<T> {
   public:
    LinkedStack()
        : top(NULL) {}
    ~LinkedStack() { makeEmpty(); }
    void push(const T& x);
    bool pop(T& x);
    bool pop();
    bool getTop(T& x) const;
    T top() { return top->data; }
    bool empty() const { return top == NULL; }
    bool full() const { return false; }
    int getSize() const;
    void makeEmpty();  //清空栈的内容
    friend ostream& operator<<(ostream& os, LinkedStack<T>& s);

   private:
    LinkNode<T>* _top;  //栈顶指针，即链头指针
};

template <class T>
void LinkedStack<T>::makeEmpty() {
    LinkNode<T>* p;
    while (_top != NULL) {
        p = _top;
        _top = _top->link;
        delete p;
    }
}

template <class T>
void LinkedStack<T>::push(const T& x) {
    _top = new LinkNode<T>(x, _top);
    assert(_top != NULL);
}

template <class T>
bool LinkedStack<T>::pop(T& x) {
    //删除栈顶结点，返回被删除栈顶元素的值
    if (IsEmpty() == true)
        return false;
    LinkNode<T>* p = _top;
    _top = top->link;
    x = p->data;
    delete p;
    return true;
}

template <class T>
bool LinkedStack<T>::pop() {
    if (IsEmpty() == true)
        return false;
    LinkNode<T>* p = _top;
    _top = _top->link;
    delete p;
    return true;
}

template <class T>
bool LinkedStack<T>::getTop(T& x) const {
    if (IsEmpty() == true)
        return false;
    x = _top->data;
    return true;
}

template <class T>
int LinkedStack<T>::getSize() const {
    LinkNode<T>* p = _top;
    int k = 0;
    while (p != NULL) {
        p = p->link;
        k++;
    }
    return k;
}

template <class T>
ostream& operator<<(ostream& os, LinkedStack<T>& s) {
    os << "栈中元素的个数 = " << s.getSize() << endl;
    LinkNode<T>* p = s._top;
    int i = 0;
    while (p != NULL) {
        os << ++i << "：" << p->data << endl;
    }
    return os;
}

//LinkNode<T> *s =new LinkNode<T>[n]; 同时使用n个链式栈