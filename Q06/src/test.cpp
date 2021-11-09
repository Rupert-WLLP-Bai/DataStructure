#include <iostream>
#include "FamilyTree.h"
using namespace std;
int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    Brother_list Family_Tree;
    cout << "**              家谱管理系统              **" << endl;
    cout << "============================================" << endl;
    cout << "**           请选择要执行的操作：         **" << endl;
    cout << "**             A --- 完善家谱             **" << endl;
    cout << "**             B --- 添加家庭成员         **" << endl;
    cout << "**             C --- 解散局部家庭         **" << endl;
    cout << "**             D --- 更改家庭成员姓名     **" << endl;
    cout << "**             E --- 退出程序             **" << endl;
    cout << "============================================" << endl;
    char order;
    Family_Tree.Family_tree();  //先建立祖先
    cin >> order;
    try {
        while (order != 'E') {
            switch (order) {
                case 'A':
                    Family_Tree.Establish_family();
                    break;
                case 'B':
                    Family_Tree.Add_member();
                    break;
                case 'C':
                    Family_Tree.Divorce_member();
                    break;
                case 'D':
                    Family_Tree.Change_member();
                    break;
                default:
                    cout << "请输入正确的命令";
                    break;
            }
            cout << endl
                 << endl
                 << "请选择要执行的操作：";
            cin >> order;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}