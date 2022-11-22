//
// Created by Administrator on 2021/12/21.
//

#include "BinaryTree.h"
#include <stack>

using namespace std;

BinaryTree::BinaryTree() {
    this->root = nullptr;
//    cout << "无参构造" << endl;
}

BinaryTree::BinaryTree(const std::string &input) {
    this->root = new BinaryTreeNode;
    this->root->data = input;
    this->root->left = nullptr;
    this->root->right = nullptr;
//    cout << "有参构造，input = " << input << endl;
}

BinaryTree::~BinaryTree() {
//    cout << "析构，_top->data = " << root->data << endl;
    destroyTree(root);
}

BinaryTreeNode *BinaryTree::getRoot() const {
    return root;
}

void BinaryTree::setRoot(BinaryTreeNode *pNode) {
    BinaryTree::root = pNode;
}

void BinaryTree::destroyTree(BinaryTreeNode *subTree) {
    if (subTree != nullptr) {
        destroyTree(subTree->left);
        destroyTree(subTree->right);
        delete subTree;
    }
}

BinaryTree::BinaryTree(const BinaryTree &binaryTree) {
    this->root = new BinaryTreeNode;
    this->root->left = nullptr;
    this->root->right = nullptr;
    this->root = copyTree(binaryTree.getRoot());
//    cout << "复制构造" << endl;
}

BinaryTreeNode *BinaryTree::copyTree(const BinaryTreeNode *binaryTreeNode) {
    if (binaryTreeNode == nullptr) {
        return nullptr;
    }
    auto *temp = new BinaryTreeNode;
    temp->data = binaryTreeNode->data;
    temp->left = copyTree(binaryTreeNode->left);
    temp->right = copyTree(binaryTreeNode->right);
    return temp;
}

BinaryTree &BinaryTree::operator=(const BinaryTree &rhs) {
    if (this == &rhs) {
        return *this;
    }
    this->root = copyTree(rhs.getRoot());
//    cout << "赋值" << endl;

    return *this;
}

BinaryTree BinaryTree::mergeTree(const BinaryTree &binaryTree1,
                                 const BinaryTree &binaryTree2,
                                 const BinaryTree &binaryTree3) {
    BinaryTree binaryTree;
    binaryTree.setRoot(copyTree(binaryTree2.getRoot()));
    binaryTree.getRoot()->left = copyTree(binaryTree1.getRoot());
    binaryTree.getRoot()->right = copyTree(binaryTree3.getRoot());
    return binaryTree;
}

void BinaryTree::preOrder(void (*visit)(BinaryTreeNode *)) const {
    preOrder(visit, root);
}

void BinaryTree::inOrder(void (*visit)(BinaryTreeNode *)) const {
    inOrder(visit, root);
}

void BinaryTree::postOrder(void (*visit)(BinaryTreeNode *)) const {
    postOrder(visit, root);
}

void BinaryTree::preOrder(void (*visit)(BinaryTreeNode *), BinaryTreeNode *subTree) const {
    if (subTree == nullptr) {
        return;
    }
    visit(subTree);
    preOrder(visit, subTree->left);
    preOrder(visit, subTree->right);
}

void BinaryTree::inOrder(void (*visit)(BinaryTreeNode *), BinaryTreeNode *subTree) const {
    if (subTree == nullptr) {
        return;
    }
    inOrder(visit, subTree->left);
    visit(subTree);
    inOrder(visit, subTree->right);
}

void BinaryTree::postOrder(void (*visit)(BinaryTreeNode *), BinaryTreeNode *subTree) const {
    if (subTree == nullptr) {
        return;
    }
    postOrder(visit, subTree->left);
    postOrder(visit, subTree->right);
    visit(subTree);
}
