//
// Created by Laobai on 2021/12/21.
//

#ifndef DATASTRUCTURE_Q07_DEVELOP_INCLUDE_SUFFIXEXPRESSION_H_
#define DATASTRUCTURE_Q07_DEVELOP_INCLUDE_SUFFIXEXPRESSION_H_

#include "BinaryTree.h"
#include "LinkedQueue.h"
#include "LinkedStack.h"
#include <iostream>
#include <string>

/**
 * 1. 完成表达式的拆分和转后缀表达式
 * 2. 将后缀表达式放进二叉树中
 */
class SuffixExpression {
public:
    static LinkedQueue<std::string> suffixExpression(std::string input_expression);
    static BinaryTree buildTree(LinkedQueue<std::string> expression_queue);
    static bool isOperator(char c);
    static bool isOperator(const std::string& c);
    static int getPriority(const char &c);
    static int getPriority(const std::string &c);
};

#endif //DATASTRUCTURE_Q07_DEVELOP_INCLUDE_SUFFIXEXPRESSION_H_
