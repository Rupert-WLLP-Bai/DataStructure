#include "FamilyTree.h"
#include <iostream>
#include <string>
#include "tool.h"
using namespace std;
Family* Brother_list::Find_member(const string& name, Family* key) {
    Family *p = key, *ans = nullptr, *temp = p;
    if (p->name == name)  //恰好传入函数的家庭成员key即是所找的成员名字
        return p;
    while (temp->brother_next) {  //在兄弟指针中不断递归寻找
        ans = Find_member(name, temp->brother_next);
        if (ans)  //找到该成员
            return ans;
        temp = temp->brother_next;  //未找到则继续搜寻其兄弟指针直至都搜寻完后搜寻孩子
    }
    temp = p;
    if (temp->child)
        ans = Find_member(name, temp->child);
    return ans;
}
Brother_list::Brother_list() {  //构造函数
    ancestor = new Family;
    ancestor->name = "";
    ancestor->child_num = 0;
    ancestor->father = nullptr;
    ancestor->child = nullptr;
    ancestor->brother_pre = nullptr;
    ancestor->brother_next = nullptr;
}
Family* Brother_list::Member_create() {  //创建新的家庭成员并初始化
    auto* p = new Family;
    p->name = "";
    p->child_num = 0;
    p->father = nullptr;
    p->child = nullptr;
    p->brother_pre = nullptr;
    p->brother_next = nullptr;

    return p;
}
void Brother_list::destroy(Family* p) {  //递归删除家庭成员，与寻找家庭成员方法类似
    Family* temp = p;
    while (temp->brother_next) {
        temp = temp->brother_next;
    }
    while (temp->brother_pre) {
        temp = temp->brother_pre;
        temp->brother_next->brother_pre = nullptr;
        temp->brother_next->brother_next = nullptr;
        destroy(temp->brother_next);
    }
    if (temp->child)
        destroy(temp->child);
    delete p;
}
void Brother_list::Show_child(Family* parent) {
    if (parent->child_num == 0) {  //该家庭成员没有孩子
        cout << parent->name << "没有后代" << endl;
        return;
    }
    Family* temp = parent->child;
    cout << parent->name << "的第一代子孙是:";  //展示子孙
    for (int i = 0; i < parent->child_num; i++) {
        cout << temp->name << "   ";
        if (temp->brother_next)
            temp = temp->brother_next;
    }
}
/*操作A完善家谱*/
void Brother_list::Establish_family() {
    string name;
    cout << "请输入要建立家庭的人的姓名：";
    cin >> name;
    Family* p = Find_member(name, ancestor);
    if (p == nullptr) {
        cout << "查无此人" << endl;
        return;
    }
    if (p->child != nullptr) {
        cout << p->name << "已经建立过家庭" << endl;
        return;
    }
    cout << "请输入" << p->name << "的儿女人数：";
    get_input(p->child_num, 0, INT32_MAX);
    if (p->child_num == 0)
        return;
    cout << "请依次输入" << p->name << "的儿女的姓名：";
    p->child = Member_create();
    Family* temp = p->child;
    cin >> temp->name;
    temp->father = p;
    for (int i = 1; i < p->child_num; i++) {
        Family* brother = Member_create();
        cin >> brother->name;
        brother->father = p;
        brother->brother_pre = temp;
        temp->brother_next = brother;
        temp = temp->brother_next;
    }
    Show_child(p);
}
/*建立祖先*/
void Brother_list::Family_tree() {
    cout << "首先建立一个家谱" << endl
         << "请输入祖先的姓名：";
    cin >> ancestor->name;
    cout << "此家谱的祖先是：" << ancestor->name << endl
         << endl;
    cout << "请选择要执行的操作：";
}
/*操作B添加家庭成员*/
void Brother_list::Add_member() {
    cout << "请输入要添加儿子（女儿）的人的姓名：";
    string name;
    cin >> name;
    Family* p = Find_member(name, ancestor);
    if (p == nullptr) {
        cout << "查无此人" << endl;
        return;
    }
    cout << "请输入" << name << "新添加的儿子（或女儿）的姓名：";
    Family* child = Member_create();
    child->father = p;
    p->child_num++;
    cin >> child->name;
    Family* temp = p;
    temp = temp->child;
    if (!p->child) {
        p->child = child;
        Show_child(p);
        return;
    }
    while (temp->brother_next) {
        temp = temp->brother_next;
    }
    temp->brother_next = child;
    Show_child(p);
}
/*操作C解散局部家庭*/
void Brother_list::Divorce_member() {
    cout << "请输入要解散的家庭的人的姓名：";
    string name;
    cin >> name;
    Family* p = Find_member(name, ancestor);
    if (p == nullptr) {
        cout << "查无此人" << endl;
        return;
    }
    cout << "要解散家庭的人是：" << p->name << endl;
    Show_child(p);  //分情况讨论解散家庭成员，主要分为是否有前兄弟和后兄弟
    try {
        /*为根节点*/
        if (p->father == nullptr) {
            cout << "不能删除根节点，请使用更名操作" << endl;
            return;
        }
        if (p->brother_pre && p->brother_next) {
            p->brother_pre->brother_next = p->brother_next;
            p->brother_next->brother_pre = p->brother_pre;
            p->father->child_num--;
        }
        if (p->brother_pre && !p->brother_next) {
            p->brother_pre->brother_next = nullptr;
            p->father->child_num--;
        }
        if (!p->brother_pre && p->brother_next) {
            p->father->child = p->brother_next;
            p->brother_next->brother_pre = nullptr;
            p->father->child_num--;
        }
        if (!p->brother_pre && !p->brother_next) {
            p->father->child = nullptr;
            p->father->child_num--;
        }
        if (p->child)
            destroy(p->child);
        delete (p);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
/*操作D更改家庭成员姓名*/
void Brother_list::Change_member() {
    cout << "请输入要更改姓名的人的目前的姓名：";
    string name;
    cin >> name;
    Family* p = Find_member(name, ancestor);
    if (p == nullptr) {
        cout << "查无此人" << endl;
        return;
    }
    cout << "请输入更改后的姓名：";
    cin >> p->name;
    cout << name << "已更名为：" << p->name;
}