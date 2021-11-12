/**
 * @file expression_tree.h
 * @brief 表达式树声明
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-11-12
 * 
 * @copyright Copyright (c) 2021  Laobai
 * 
 */

#ifndef DATASTRUCTURE_EXPRESSION_TREE_H
#define DATASTRUCTURE_EXPRESSION_TREE_H

#include <string>
using namespace std;

struct ExpressionTreeNode {
    char op;                    //操作符
    string data;                //数据
    ExpressionTreeNode* left;   //左指针
    ExpressionTreeNode* right;  //右指针
};

class ExpressionTree {
   private:
    ExpressionTreeNode* root;  //根节点

   public:
    ExpressionTree();
    ~ExpressionTree();
};

#endif  //DATASTRUCTURE_EXPRESSION_TREE_H
