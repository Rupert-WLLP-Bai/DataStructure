/*
输入文件名
输入文本到文件
从文本中读取文件到string 去掉空格 存在trie树中
输入关键字 查找 输出结果 （不区分大小写）
*/

#pragma once
#include <fstream>
#include <iostream>
#include "trie.h"
using namespace std;

//DEFINITION OF EXCEPTION
#define OPEN_FAILED 1


void input(string& filename, string& route);
void input_key(string& key);
void display_src(string route);
void read_file(trie<26, IndexClass>& t, string route);
void solution();
string random_gen(int64_t n);