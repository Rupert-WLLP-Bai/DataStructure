/*
@file:        student.h
@description: 学生类
@version:     v1.0.0
@author:      Laobai
@time:        2021年9月19日17:55:52
*/

/*
update notes:

v1.0.0 2021年9月19日17:55:52
     in v1.0.1:
        1. 根据最长的名字调整输出的长度以及表头标题之间的距离，名字超过10个汉字的长度只显示前五个和后五个字符中间用..连接
        2. 注释的位置放在某一行的上一行(***改掉行尾注释)
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include "list_linked.h"
using namespace std;

class Student {
   private:
    string id;        //序号
    string name;      //名字
    string gender;    //性别
    int age;          //年龄
    string category;  //类别
   public:
    Student() { age = -1; };
    Student(string ID, string NAME, string GENDER, int AGE, string CATEGORY) {
        id = std::move(ID);
        name = std::move(NAME);
        gender = std::move(GENDER);
        category = std::move(CATEGORY);
        age = AGE;
    }
    Student(Student& s1) {
        id = s1.id;
        name = s1.name;
        gender = s1.gender;
        category = s1.category;
        age = s1.age;
    }
    ~Student()= default;
    friend ostream& operator<<(ostream& out, Student& Stu);  //重载输出
    friend istream& operator>>(istream& in, Student& Stu);   //重载输入
    bool operator==(Student& s1);                            //重载==
    bool operator!=(Student& s1);                            //重载!=
};

//重载输出
inline ostream& operator<<(ostream& out, Student& Stu) {
    out << setiosflags(ios::left);
    out << setw(12) << Stu.id << setw(16) << Stu.name << setw(8) << Stu.gender
        << setw(8) << Stu.age << setw(10) << Stu.category;
    return out;
}

//重载输入
inline istream& operator>>(istream& in, Student& Stu) {
    cin >> Stu.id >> Stu.name >> Stu.gender >> Stu.age >> Stu.category;
    return in;
}

//重载!=
bool Student::operator!=(Student& s1) {
    if (s1.id != id)
        return true;
    if (s1.category != category)
        return true;
    if (s1.gender != gender)
        return true;
    if (s1.age != age)
        return true;
    if (s1.name != name)
        return true;
    return false;
}

//重载==
bool Student::operator==(Student& s1) {
    if (s1.id != id)
        return false;
    if (s1.category != category)
        return false;
    if (s1.gender != gender)
        return false;
    if (s1.age != age)
        return false;
    if (s1.name != name)
        return false;
    return true;
}
