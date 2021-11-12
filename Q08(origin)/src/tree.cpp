#include "tree.h"
#include <iostream>
using namespace std;
#define Max 10000

Tree::~Tree() {
    if (map != NULL)
        delete[] map;
}
/*---输入节点名称---*/
void Tree::A_InputName() {
    if (!ans.empty()) {
        cout << "已生成最小生成树，非法操作！" << endl
             << endl;
        return;
    }
    if (map != NULL) {
        cout << "已生成地图， 非法操作！" << endl
             << endl;
        return;
    }
    string temp;
    cout << "请输入顶点的个数:";
    cin >> num;
    cout << "请依次输入顶点的名称:" << endl;

    for (size_t i = 0; i < num; i++) {
        cin >> temp;
        name.push_back(make_pair(temp, i));
    }
    cout << endl;
}
/*---输入地图---*/
void Tree::B_InputMap() {
    if (!ans.empty()) {
        cout << "已生成最小生成树，非法操作！" << endl
             << endl;
        return;
    }
    if (num == 1) {
        cout << "非法城市个数！" << endl
             << endl;
        return;
    }

    map = new int*[num];
    for (size_t i = 0; i < num; i++)
        map[i] = new int[num];

    for (size_t i = 0; i < num - 1; i++) {
        cout << "请输入给出的两个顶点间的距离，不存在距离则输入-1: ";
        map[i][i] = 0;
        for (size_t k = i + 1; k < num; k++) {
            cout << name[i].first << " ";
            cout << name[k].first << " ";
            cin >> map[i][k];
            if (map[i][k] == -1)
                map[i][k] = Max;
            if (k != num - 1)
                cout << "请输入给出的两个顶点间的距离，不存在距离则输入-1: ";
        }
    }

    for (size_t i = 0; i < num; i++) {
        for (size_t k = 0; k < i; k++) {
            map[i][k] = map[k][i];
        }
    }
    cout << endl;
}
/*---生成最小生成树---*/
void Tree::C_buildTree() {
    ans.clear();
    vector<pair<string, int> > store;
    pair<int, int> Min;
    string tempname;
    priority_queue<int, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > que;
    int min;
    int flag = 0;
    cout << "请输入起始顶点：";
    cin >> tempname;
    for (size_t i = 0; i < name.size(); i++) {
        if (tempname == name[i].first) {
            store.push_back(name[i]);
            break;
        }
    }
    while (store.size() < num) {
        min = 100000;
        //遍历
        for (size_t i = 0; i < store.size(); i++) {
            for (size_t k = 0; k < num; k++) {
                if (k == store[i].second)
                    continue;
                que.push(make_pair(map[store[i].second][k], make_pair(store[i].second, k)));
            }
        }
        //加入
        for (size_t i = 0; i < name.size(); i++) {
            if (que.top().second.second == name[i].second) {
                store.push_back(name[i]);
                ans.push_back(make_pair(que.top().second.first, que.top().second.second));
            }
        }
        while (!que.empty())
            que.pop();
    }
    cout << "生成Prim最小生成树！" << endl
         << endl;
}
/*---打印最小生成树---*/
void Tree::D_print() {
    string name1, name2;
    cout << "最小生成树的顶点以及边为：" << endl;
    for (size_t i = 0; i < ans.size(); i++) {
        for (size_t k = 0; k < name.size(); k++) {
            if (ans[i].first == name[k].second)
                name1 = name[k].first;
            if (ans[i].second == name[k].second)
                name2 = name[k].first;
        }

        cout << name1 << "-(" << map[ans[i].first][ans[i].second]
             << ")-" << name2 << "        ";
    }
    cout << endl
         << endl;
}