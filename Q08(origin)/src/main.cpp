#include <iostream>
#include "tree.h"

using namespace std;
/*---析构函数---*/

int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    cout << "**                     电网造价模拟系统                     **" << endl;
    cout << "==============================================================" << endl;
    cout << "**                     A---创建电网定点                     **" << endl;
    cout << "**                     B---添加电网的边                     **" << endl;
    cout << "**                     C---构造最小生成树                   **" << endl;
    cout << "**                     D---显示最小生成树                   **" << endl;
    cout << "**                     E---退出    程序                     **" << endl;
    cout << "==============================================================" << endl;

    char order;
    Tree tree;

    //Node * p = tree.create();

    cout << "请选择操作:";
    cin >> order;

    while (order != 'E') {
        switch (order) {
            case 'A':
                tree.A_InputName();
                break;
            case 'B':
                tree.B_InputMap();
                break;
            case 'C':
                tree.C_buildTree();
                break;
            case 'D':
                tree.D_print();
                break;
            default:
                break;
        }
        cout << "请选择操作:";
        cin >> order;
    }
    return 0;
}
