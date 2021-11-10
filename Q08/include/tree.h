#include <string>
#include <vector>
#include <queue>
using namespace std;
/*---最小生成树类---*/
class Tree {
   private:
    int** map;                        //地图
    int num;                          //节点数目
    vector<pair<string, int> > name;  //节点名和对应的序号
    vector<pair<int, int> > ans;      //最小生成树序列
   public:
    Tree()
        : map(NULL), num(0) {}  //默认构造函数
    ~Tree();                    //析构函数

    void A_InputName();  //输入节点名称
    void B_InputMap();   //输入地图
    void C_buildTree();  //生成最小生成树
    void D_print();      //打印最小生成树
};