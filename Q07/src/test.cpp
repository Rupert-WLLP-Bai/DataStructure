#include <iostream>
#include <string>
using namespace std;
void suffix(string expression);  //由输入的表达式得到后缀表达式
int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    string order = "1";
    string expression;
    cout << "**              表达式计算              **" << endl;
    cout << "==========================================" << endl;
    cout << "**          请选择要执行的操作          **" << endl;
    cout << "**         1 --- 前缀、中缀及后缀       **" << endl;
    cout << "**            0 --- 退出系统            **" << endl;
    cout << "==========================================" << endl;
    while (order != "0") {
        cout << endl
             << "请输入中缀表达式：";
        cin >> expression;
        suffix(expression);
        cout << endl
             << endl
             << "请输入指令：";
        cin >> order;
    }
}