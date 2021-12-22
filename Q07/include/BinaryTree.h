//
// Created by Administrator on 2021/12/21.
//

#ifndef DATASTRUCTURE_BINARYTREE_H
#define DATASTRUCTURE_BINARYTREE_H

#include <string>

using std::string;

struct BinaryTreeNode {
    std::string data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
};

class BinaryTree {
public:
    BinaryTree();
    explicit BinaryTree(const string &input);
    BinaryTree(const BinaryTree &binaryTree);
    virtual ~BinaryTree();
    BinaryTreeNode *getRoot() const;
    void setRoot(BinaryTreeNode *root);
    BinaryTree &operator=(const BinaryTree &rhs);
    static BinaryTree mergeTree(const BinaryTree &binaryTree1,
                                const BinaryTree &binaryTree2,
                                const BinaryTree &binaryTree3);
    void preOrder(void(*visit)(BinaryTreeNode *)) const;    //前序
    void inOrder(void(*visit)(BinaryTreeNode *)) const;     //中序
    void postOrder(void(*visit)(BinaryTreeNode *)) const;   //后序
private:
    BinaryTreeNode *root;//根节点
    void destroyTree(BinaryTreeNode *subTree);
    static BinaryTreeNode *copyTree(const BinaryTreeNode *binaryTreeNode);
    void preOrder(void(*visit)(BinaryTreeNode *), BinaryTreeNode *subTree) const;
    void inOrder(void(*visit)(BinaryTreeNode *), BinaryTreeNode *subTree) const;
    void postOrder(void(*visit)(BinaryTreeNode *), BinaryTreeNode *subTree) const;
};

#endif //DATASTRUCTURE_BINARYTREE_H
