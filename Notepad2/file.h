#ifndef FILE_H
#define FILE_H

#pragma once

#include <iostream>
#include <cstdio>
#include <string.h>
        ///300行会清屏
#define MAXKEYWORDS 295
#define MAXKEYLENGTH 100

using namespace std;

//读入数据文件输入关键字
bool ReadFileToArray(char *fileName, char keyWords[MAXKEYWORDS][MAXKEYLENGTH]){
    FILE *fp;
    char str[65535];
    fp=fopen(fileName, "r");
    if(fp==nullptr){
        cout << "File cannot be opened!" << endl;
        return false;
    }
    //Read the identification and judge
    if(fgets(str, 1000, fp)!=nullptr){
        if(strcmp(str, "Key Words\n")!=0){
            cout << "Format Error!" << endl;
            return false;
            fclose(fp);
        }
    }
    //Empty file protection
    else{
        cout << "Empty File!" << endl;
        return false;
        fclose(fp);
    }
    int Line=0;
    while(fscanf(fp, "%s\n", &keyWords[Line]) != EOF){
        Line++;
    }
    fclose(fp);
    return true;
}

#endif // FILE_H
