#include<string>
#include<iostream>
#include<stack>
using namespace std;
typedef struct BinaryNode			//二叉树节点，data存储数据
{
	char data;
	BinaryNode *left;
	BinaryNode *right;
}TreeNode;
TreeNode* CreateTreeNode(char ch)	//创建二叉树节点并初始化
{
	TreeNode *pNode = new TreeNode;
	pNode->data = ch;
	pNode->left = NULL;
	pNode->right = NULL;
	return pNode;
}
int get_op(char c);                          //判断运算符优先级
void PreOrder(stack<TreeNode *> subTree);     //前序遍历，三种遍历方式均使用递归
void InOrder(stack<TreeNode *> subTree);		//中序遍历
void PostOrder(stack<TreeNode *> subTree);		//后序遍历
void tree(const string& suffix_exp);				//由后缀表达式得到二叉树