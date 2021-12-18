#include <string>
using std::string;
struct Family {            //Family成员结构体
    string name;           //家庭成员名字
    int child_num;            //该家庭成员所有的孩子个数
    Family* father;        //二叉链表的父指针
    Family* brother_next;  //二叉链表的兄弟指针
    Family* brother_pre;
    Family* child;  //二叉链表的孩子指针
};

class Brother_list {
   public:
    Brother_list();                         //构造函数
    ~Brother_list() { destroy(ancestor); }  //析构函数

    void destroy(Family* ancestor);                 //递归删除
    void Establish_family();                        //操作A完善家谱
    void Family_tree();                             //建立祖先
    void Add_member();                              //操作B添加家庭成员
    void Divorce_member();                          //操作C解散局部家庭
    void Change_member();                           //操作D更改家庭成员姓名
    Family* Find_member(const string& name, Family* key);  //寻找家庭成员
    static Family* Member_create();                        //创建新的家庭成员
    static void Show_child(Family* parent);                //展示家庭成员第一代
   private:
    Family* ancestor;  //祖先
};
