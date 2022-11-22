/*
@file:        solution.cpp
@description: 求解问题
@version:     v1.0.2
@author:      Laobai
@time:        2021年11月7日14:42:29
*/

#include "solution.h"
#include <string>  //字符串
#include "trie.h"  //Trie树

/*
#ifdef _WIN32
#include <Windows.h>  //Windows API用于创建和删除目录
#else
#include "file_maker.h"  //Linux only
#endif
*/

/**
 * @brief 输入内容
 * @param  filename         
 * @param  route            
 */
void input(string& filename, string& route) {
    cout << "输入文件名" << endl;
    cin >> filename;
    route += filename;//路径
    ofstream out;//输入到文件中
    out.open(route);
    if (out.fail()) {
        cerr << "Error" << endl;
        exit(1);
    }
    cin.get();
    string text;//输入的文本内容
    cout << "请输入一段文字" << endl;
    getline(cin, text);
    out << text;//输入到文件中
    out.close();
}

/**
 * @brief 输入关键词
 * @param  key              
 */
void input_key(string& key) {
    cout << "输入关键词" << endl;
    cin >> key;
}

/**
 * @brief 显示源文件
 * @param  route            
 */
void display_src(const string& route) {
    int src;
    fstream out;
    out.open(route);
    if (out.fail()) {
        cerr << "Error" << endl;
        exit(1);
    }
    while ((src = out.get()) != EOF) {
        cout << char(src);
    }
    cout << endl;
    out.close();
}

/**
 * @brief 读取到trie树中
 * @param  t                
 * @param  route            
 */
void read_file(trie<26, IndexClass>& t, const string& route) {
    ifstream in(route);
    string str;
    int c;
    while (!in.eof()) {
        c = in.get();
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))  //判断有效
            str += std::to_string(c);
        else {
            //  这一段的逻辑可能有待商榷，大概应该先过滤掉无效字符之后再进行插入
            if (str.empty())
                continue;
            //cout << "插入：" << str << endl;
            t.insert(str.begin(), str.end());
            str.clear();
        }
    }
}


/**
 * @brief 遍历方式
 */
class StringExe {
   public:
    void operator()(std::string& str, int freq) {
        std::cout << str << ":" << freq << std::endl;
    }
};

//主程序
void solution() {
    string filename;         //文件名
    string route;       //文件路径文件夹
    string key;              //关键词
    trie<26, IndexClass> t;  //Trie树
    input(filename, route);  //输入文件名以及文件内容
    input_key(key);          //输入关键字
    read_file(t, route);     //将文本储存在Trie树中(去掉字母以外的内容)
    cout << "---------- 遍 历 结 果 ----------" << endl;
    t.traverse<StringExe>();  //遍历
    cout << "-------- 输 出 源 文 件 --------" << endl;
    display_src(route);  //输出源文件
    /*查找结果*/
    cout << "---------- 查 找 结 果 ----------" << endl;
    cout << key << ": " << t.getFrequency(key.c_str()) << endl;
}
