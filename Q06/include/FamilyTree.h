#include <string>
using std::string;

/**
 * Family 成员结构体
 */
struct Family {
    string name;           //家庭成员名字
    int child_num;            //该家庭成员所有的孩子个数
    Family* father;        //二叉链表的父指针
    Family* brother_next;  //二叉链表的兄弟指针
    Family* brother_pre;
    Family* child;  //二叉链表的孩子指针
};

class FamilyMap {
   public:
    FamilyMap();                         //构造函数
    ~FamilyMap() { destroyFamily(ancestor); }  //析构函数
    void destroyFamily(Family* family_ancestor);                 //递归删除
    void establishFamily();                        //操作A完善家谱
    void familyTree();                             //建立祖先
    void addMember();                              //操作B添加家庭成员
    void divorceMember();                          //操作C解散局部家庭
    void changeMember();                           //操作D更改家庭成员姓名
    Family* findMember(const string& name, Family* key);  //寻找家庭成员
    static Family* memberCreate();                        //创建新的家庭成员
    static void showChild(Family* parent);                //展示家庭成员第一代
   private:
    Family* ancestor;  //祖先
};
