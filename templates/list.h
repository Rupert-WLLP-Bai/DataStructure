/**
 * @file list.h
 * @brief 线性表的抽象基类
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0.0
 * @date 2021-11-07
 * 
 * @copyright Copyright (c) 2021  Laobai
 * 
 */

#pragma once
template <class T>
class LinearList {
   public:
    LinearList()= default;
    ~LinearList()= default;
    virtual int length() const = 0;                          //求长度
    virtual int search(T& x) const = 0;                      //搜索
    virtual int locate(int i) const = 0;                     //定位
    virtual bool getData(int i, T& x) const = 0;             //读取
    virtual bool setData(int i, T&& x) = 0;                  //修改
    virtual bool insert(int i, T& x) = 0;                    //插入
    virtual bool remove(int i, T& x) = 0;                    //删除
    virtual bool empty() const = 0;                          //判断空
    virtual bool full() const = 0;                           //判断满
     virtual void output() = 0;                               //输出
    virtual LinearList<T>& operator=(LinearList<T>& L) = 0;  //复制
};
