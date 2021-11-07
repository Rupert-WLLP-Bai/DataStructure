/**
 * @file file_maker.h
 * @brief 实现文件操作
 * @author Laobai (CWLLP1230@gmail.com)
 * @version 1.0
 * @date 2021-11-05
 * 
 * @copyright Copyright (c) 2021  Laobai
 * 
 */

#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

using namespace std;

#ifdef _WIN32
//Windows下操作文件夹
#else
//LINUX下遍历目录 opendir -> readdir -> closedir
// 打开 ->  读取  -> 关闭
void Getfilepath(const char* path, const char* filename, char* filepath) {
    strcpy(filepath, path);
    if (filepath[strlen(path) - 1] != '/')
        strcat(filepath, "/");
    strcat(filepath, filename);
    printf("path is = %s\n", filepath);
}

bool DeleteFile(const char* path) {
    DIR* dir;
    struct dirent* dirinfo;
    struct stat statbuf;
    char filepath[256] = {0};
    lstat(path, &statbuf);

    if (S_ISREG(statbuf.st_mode))  //判断是否是常规文件
    {
        remove(path);
    } else if (S_ISDIR(statbuf.st_mode))  //判断是否是目录
    {
        if ((dir = opendir(path)) == NULL)
            return 1;
        while ((dirinfo = readdir(dir)) != NULL) {
            Getfilepath(path, dirinfo->d_name, filepath);
            if (strcmp(dirinfo->d_name, ".") == 0 || strcmp(dirinfo->d_name, "..") == 0)  //判断是否是特殊目录
                continue;
            DeleteFile(filepath);
            rmdir(filepath);
        }
        closedir(dir);
    }
    return 0;
}

#endif