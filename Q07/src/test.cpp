//
// Created by Administrator on 2021/12/21.
//

#include "BinaryTree.h"
#include <iostream>
#include <iomanip>
#include "SuffixExpression.h"

void outputResult(const BinaryTree &binary_tree);
void visit(BinaryTreeNode *binary_tree_node);
using namespace std;



int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    cout << "输入合法的表达式: ";
    string str;
    getline(cin, str);
    LinkedQueue<string> result = SuffixExpression::suffixExpression(str);
    BinaryTree binary_tree = SuffixExpression::buildTree(result);
    outputResult(binary_tree);
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

/**
 * 输出表达式遍历结果
 * @param binary_tree
 */
void outputResult(const BinaryTree &binary_tree) {
    cout << setiosflags(ios::left) << setfill(' ') << setw(30) << "前序遍历(波兰式): ";
    binary_tree.preOrder(visit);
    cout << endl;
    cout << setiosflags(ios::left) << setfill(' ') << setw(30) << "中序遍历(中缀表达式): ";
    binary_tree.inOrder(visit);
    cout << endl;
    cout << setiosflags(ios::left) << setfill(' ') << setw(30) << "后序遍历(逆波兰式): ";
    binary_tree.postOrder(visit);
    cout << endl;
}

/**
 * visit函数
 * @param binary_tree_node
 */
void visit(BinaryTreeNode *binary_tree_node) {
    cout << binary_tree_node->data << " ";
}

