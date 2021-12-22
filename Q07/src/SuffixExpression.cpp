//
// Created by Laobai on 2021/12/21.
//

#include "SuffixExpression.h"

using namespace std;

/**
 * 拆分输入的表达式
 * @param input_expression
 * @return
*/
LinkedQueue<std::string> SuffixExpression::suffixExpression(std::string input_expression) {
    const string operators = "+-*/()";    // 保存所有的计算符号
    LinkedStack<char> ops;
    LinkedQueue<string> result;
    ops.push('#');
    string tempStr;
    for (size_t i = 0; i < input_expression.size(); i++) {   // 检查是否是带符号的数字
        // 1. 带正负号且前一个字符为运算符（i=0时直接带正负号的也是数字）
        // 2. 当前字符为数字
        if (((input_expression[i] == '-' || input_expression[i] == '+')
            && (i == 0 || string("+-/*(").find(input_expression[i - 1]) != string::npos))
            || isdigit(input_expression[i])) {   // 把操作数加入到后缀式中
            // 如果是正号就不用加入，负号或者数字本身都要加入
            tempStr = input_expression[i] != '+' ? input_expression.substr(i, 1) : "";
            while (i + 1 < input_expression.size() && operators.find(input_expression[i + 1]) == string::npos) {
                tempStr += input_expression[++i];
            }
            result.push(tempStr);
            //cout << "queue push1 " << tempStr << endl;
        } else { // 出现操作符
            if (input_expression[i] == '(')
                ops.push(input_expression[i]);
            else if (input_expression[i] == ')') {
                while (ops.top() != '(') {
                    result.push(string(1, ops.top()));
                    //cout << "queue push2 " << string(1, ops.top()) << endl;
                    ops.pop();
                }
                ops.pop();
            } else {
                while (getPriority(input_expression[i]) <= getPriority(ops.top())) {
                    result.push(string(1, ops.top()));
                    //cout << "queue push3 " << string(1, ops.top()) << endl;
                    ops.pop();
                }
                ops.push(input_expression[i]);
            }
        }
    }
    while (ops.size() > 1) {
        result.push(string(1, ops.top()));
        // cout << "queue push4 " << string(1, ops.top()) << endl;
        ops.pop();
    }
    return result;
}

/**
 * 后缀表达式建立二叉树
 * @param expression_queue
 * @return
 */
BinaryTree SuffixExpression::buildTree(LinkedQueue<std::string> result) {
    if (result.empty()) {
        throw invalid_argument("输入的表达式为空");
    }
    LinkedStack<BinaryTree> num;//数据栈
    //LinkedStack<BinaryTree> op;//运算符栈
    BinaryTree tree;
    try {
        while (result.size()) {
            string front = result.front();
            //cout << front << ' ';
            /* 碰到数直接放进数据栈 */
            if(!isOperator(front)){
                num.push(BinaryTree(front));
            }else{
                /* 如果碰到运算符，从数据栈中取出两个元素，和符号合并为一棵树，放回数据栈 */
                BinaryTree right_num = num.top();
                num.pop();
                BinaryTree left_num = num.top();
                num.pop();
                BinaryTree ops(front);  //符号结点
                /* 合并 */
                BinaryTree mergeResult = BinaryTree::mergeTree(left_num,ops,right_num);
                /* 放回数据栈 */
                num.push(mergeResult);
            }
            result.pop();
            //cout<<"size = "<<result.size()<<endl;
        }
    }
    catch (exception &e) {
        cerr << e.what() << endl;
    }
    cout << endl;
    tree = num.top();
    return tree;
    /* -4.5*(7+2*(9+6)-3)+5 */
}

/**
 * 判断是否为运算符
 * @param c
 * @return
 */
bool SuffixExpression::isOperator(char c) {
    if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/') {
        return true;
    }
    return false;
}

/**
 * 判断是否为运算符
 * @param c
 * @return
 */
bool SuffixExpression::isOperator(const std::string& c) {
    if (c == "(" || c == ")" || c == "+" || c == "-" || c == "*" || c == "/") {
        return true;
    }
    return false;
}

/**
 * 获取运算符优先级
 * @param c
 * @return
 */
int SuffixExpression::getPriority(const char &c) {
    int priority;
    switch (c) {
        case '#':
            priority = 0;
            break;
        case '(':
            priority = 1;
            break;
        case '+':
        case '-':
            priority = 2;
            break;
        case '*':
        case '/':
            priority = 3;
            break;
        default:
            priority = 0;
            break;
    }
    return priority;
}

/**
 * 字符串转为char取第一个位置
 * @param c
 * @return
 */
int SuffixExpression::getPriority(const std::string &c) {
    const char _c = c.c_str()[0];
    return getPriority(_c);
}



