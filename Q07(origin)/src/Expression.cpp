#include"Expression.h"
char ops[] = "+-*/";
/*
  +  -  *  /         使用二维数组判断符号优先级
+ 0  0 -1 -1
- 0  0 -1 -1
* 1  1  0  0
/ 1  1  0  0

*/
int priority[4][4] =
{
	{ 0, 0, -1, -1 },
	{ 0, 0, -1, -1 },
	{ 1, 1, 0, 0 },
	{ 1, 1, 0, 0 }
};
int get_op(char c)
{
	for (int i = 0; i < 4; i++)
	if (c == ops[i]) return i;
	return -1;
}

void suffix(string expression){
	stack<char>operate, number;   //operate为运算符栈 number为数字栈
	char c;                       //c为表达式中的单个字符
	string suffix_exp,temp;			//suffix_exp为后缀表达式
	int i = 0;
	while (i < expression.size()){
		c = expression[i];
		if (isdigit(c)) 
			number.push(c);  //数字直接压栈number  
		else{
			if ('(' == c) operate.push(c);   //左括号  
			else if (')' == c){    //右括号  

				while ('(' != operate.top()){
					number.push(operate.top());
					operate.pop();
					
				}
				operate.pop();
			}
			else{
				if (operate.empty() || '(' == operate.top()) operate.push(c);
				else{
					while (!operate.empty() && (priority[get_op(c)][get_op(operate.top())]) <= 0){
						number.push(operate.top());
						operate.pop();
					}
					operate.push(c);
				}
			}
		}
		i++;
	}
	while (!number.empty()){   //把operate中剩余字符压入number  
		operate.push(number.top());
		number.pop();
	}
	while (!operate.empty()){
		temp = operate.top();
		suffix_exp += temp;
		operate.pop();
	}
	tree(suffix_exp);
}
stack<TreeNode *> nodeStack;    //后缀表达式转成的二叉树
void tree(const string& suffix_exp){
	char ch;
	for(char iX : suffix_exp){
		ch = iX;		//遍历后缀表达式每个字符，数字直接入栈，运算符创建二叉树节点
		TreeNode *pNode = CreateTreeNode(ch);
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			TreeNode *pRight = nodeStack.top();    //若该字符为运算符，则其为二叉树的节点
			nodeStack.pop();					//为其创建左右子节点，将栈顶的两个数据弹出作为左右子节点
			TreeNode *pLeft = nodeStack.top();	//再将运算符入栈
			nodeStack.pop();

			pNode->right = pRight;
			pNode->left = pLeft;
			nodeStack.push(pNode);
		}
		else{
			nodeStack.push(pNode);
		}
	}
	cout << endl<<"前缀表达式为：";
	PreOrder(nodeStack);
	cout << endl<<"中缀表达式为：";
	InOrder(nodeStack);
	cout << endl << "后缀表达式为：";
	PostOrder(nodeStack);
}
void PreOrder(stack<TreeNode *> subTree){        //前序遍历
	cout << subTree.top()->data;				//前序遍历先将根节点找出
	TreeNode* tmp;								//再搜寻左子树
	if (subTree.top()->left!= NULL){			//最后将右子树的节点找出可得到前缀表达式
		tmp = subTree.top();					//tmp作为中间变量使用
		subTree.top() = subTree.top()->left;	
		PreOrder(subTree);
		subTree.top() = tmp;
		if (subTree.top()->right != NULL){
			subTree.top() = subTree.top()->right;
			PreOrder(subTree);
		}
	}
}
void InOrder(stack<TreeNode *> subTree){        //中序遍历
	TreeNode* tmp;								//中序遍历是先找出左子树的节点
	if (subTree.top()->left != NULL){			//再找出根节点
		tmp = subTree.top();					//最后找出右子树的所有节点
		subTree.top() = subTree.top()->left;	//从而达到中缀表达式
		InOrder(subTree);
		subTree.top() = tmp;
	}
	cout << subTree.top()->data;
	if (subTree.top()->right != NULL){
		subTree.top() = subTree.top()->right;
		InOrder(subTree);
	}
}
void PostOrder(stack<TreeNode *> subTree){               //后序遍历
	TreeNode* tmp_left;									//后序遍历是先找到所有左子树节点
	TreeNode* tmp_right;								//再将右子树节点找出
	if (subTree.top()->left != NULL){					//最后找出根节点
		tmp_left = subTree.top();
		subTree.top() = subTree.top()->left;
		PostOrder(subTree);
		subTree.top() = tmp_left;
		if (subTree.top()->right != NULL){
			tmp_right = subTree.top();
			subTree.top() = subTree.top()->right;
			PostOrder(subTree);
			subTree.top() = tmp_right;
		}
	}
	cout << subTree.top()->data;	
}