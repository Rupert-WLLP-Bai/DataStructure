# 基于C++实现的家谱管理系统

# 一、使用说明

## 1.1 项目简介

家谱是一种以表谱形式，记载一个以血缘关系为主体的家族世袭繁衍和重要任务事迹的特殊图书体裁。家谱是中国特有的文化遗产，是中华民族的三大文献（国史，地志，族谱）之一，属于珍贵的人文资料，对于历史学，民俗学，人口学，社会学和经济学的深入研究，均有其不可替代的独特功能。本项目对家谱管理进行简单的模拟，以实现查看祖先和子孙个人信息，插入家族成员，删除家族成员的功能。

## 1.2 项目功能要求

本项目的实质是完成对家谱成员信息的建立，查找，插入，修改，删除等功能，可以首先定义家族成员数据结构，然后将每个功能作为一个成员函数来完成对数据的操作，最后完成主函数以验证各个函数功能并得到运行结果。

## 1.3 操作手册

运行程序后，进入欢迎界面，首先要输入考生的数据。

第一步，输入祖先的姓名：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/edd7cd6fd344b7583f885ca1e65c980c.writebug)

首先输入要建立家庭的人的姓名：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/ffdb74f4cea9b3f77241332342c90755.writebug)

然后输入该成员的儿女数及儿女的名字：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/932e63ca4347a0f96bfac69d1aa125a0.writebug)

之后会显示第一代子孙：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/c32f20039de205ee6ab4bf66f10e1ff9.writebug)

首先要输入要添加家庭成员的人的姓名：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/37ced909bd2a6ab06c9ba88c1aa96650.writebug)

之后输入该家庭成员新添加的儿子或女儿的姓名：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/f7541e99e0b1402d739ec37390bd9d6e.writebug)

之后会显示第一代子孙：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/8b467822dbc62972b0a78e2617addecf.writebug)

首先要输入解散家庭的人的姓名：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/c347e6f1955eba0d43dbeb67f5d65edd.writebug)

之后将显示解散的家庭：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/1dc63a849e13310f8d90016228068720.writebug)

首先输入要更改姓名的人的目前的姓名：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/983a8cd3be189eaf912816e5ec27d47a.writebug)

之后输入更改后的姓名：

![](http://www.writebug.com/myres/static/uploads/2021/10/19/d0179a4df53f9136bf0cd05756441098.writebug)

## 1.4 注意事项

- 进行每步操作时，需要在已有的家庭成员信息上进行操作，不可输入不存在的家庭成员姓名。如操作D被更改姓名的家庭成员必须是已有成员

- 操作A输入的儿女数对应相应的名字数

- 操作B只能添加一名家庭成员

# 二、概述

## 2.1 基本思路

采用子女—兄弟链表表示法的二叉链表实现。Family成员结构体，对应有父指针和子指针以及前后兄弟指针，将整个家庭构造成树的结构。在添加新家庭成员时，只需在原链表尾处添加新节点并标记其父指针为原表尾。同样，解散家庭成员时，根据该成员所处位置，将其前后兄弟指针相连，并减少父节点的子孙数后删除该节点。完善家庭成员时，先输入子女个数，之后为每个子女建立新节点并与父节点相连，每个子女节点之间用兄弟指针相连，便于查找家庭成员。

## 2.2 文件目录

- test.cpp (主文件)

- FamilyTree.h (定义Brother_list类和Family结构体)

- FamilyTree.cpp (Brother_list类相关函数的具体实现方法)

- test.exe (程序可执行文件)

- 设计报告.doc (项目文档)

# 三、具体实现

## 3.1 Brother_list接口

| 成员函数名                                    | 功能                        | 参数                        |
| ---------------------------------------- | ------------------------- | ------------------------- |
| Brother_list ()                          | 构造函数,初始化家庭成员。             |                           |
| ~Brother_list ()                         | 析构函数，递归删除家庭成员，与寻找家庭成员方法类似 |                           |
| void destroy(Family\* ancestor)           | 删除家庭成员                    | 整个家庭树                     |
| void Establish_family()                  | 操作A完善家谱                   |                           |
| void Family_tree()                       | 建立祖先                      |                           |
| void Add_member()                        | 操作B添加家庭成员                 |                           |
| void Divorce_member()                    | 操作C解散局部家庭                 |                           |
| void Change_member()                     | 操作D更改家庭成员姓名               |                           |
| Family \*Find_member(string name, Family \*  key) | 寻找家庭成员                    | name为家庭成员姓名  key为家庭成员所处节点 |
| Family \*Member_create()                  | 创建新的家庭成员                  |                           |
| void Show_child(Family \*parent)          | 展示家庭成员第一代                 | parent为当前家庭成员节点           |

## 3.2 结构体Family

```c++
    string name;			// 家庭成员名字
	int ichild;			   // 该家庭成员所有的孩子个数
	Family *father;		   // 二叉链表的父指针
	Family *brother_next;  // 二叉链表的兄弟指针
	Family *brother_pre;
	Family *child;      	// 二叉链表的孩子指针
```

## 3.3 方法实现具体说明

- **操作A完善家谱**
  在得到家庭成员的姓名后，用查找函数在家庭树中查找该成员。在对其子指针进行判断，若不空则已建立家庭不进行操作。若为空则需要输入子女的个数和姓名，之后用循环添加新子女到家庭树中。

- **操作B添加家庭成员**
  同操作A，得到家庭成员姓名后先在家庭树中找到该人，之后输入该成员的姓名，在家庭树中建立新的节点，方法与操作A相同。

- **操作C解散局部家庭**
  首先找到要删除的家庭成员的人，之后进行分情况讨论，要判断该人是否有兄弟指针，如果有则需将前后兄弟指针相连或置空，并让其父节点的子孙数减一，之后删除该节点。

- **操作D更改家庭成员姓名**
  找到该家庭成员后更改其name即可。

- **查找函数**
  收先判断传入函数的key是否就是所找家庭成员，若不是，在对其兄弟节点和孩子节点进行递归查找。

- **展示家庭成员**
  得到parent节点后，将其子节点赋给temp，之后展示temp的所有兄弟指针所处节点。