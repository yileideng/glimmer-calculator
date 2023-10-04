#ifndef HEADER_FILE_H
#define HEADER_FILE_H

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<getopt.h>
#include<stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#define Stack_Size 10
#define Add_Size 5
#define ERROR 0
#define OK 1
typedef int Status;
typedef int Bool;
typedef char StackElem; /*定义字符数据类型*/
typedef double StackElem2;/*定义运算数数据类型*/
//字符栈：
typedef struct {
    StackElem* pbase;
    StackElem* ptop;
    int size;
} SQstack;
//数字栈：
typedef struct {
    StackElem2* pbase;
    StackElem2* ptop;
    int size;
} NSstack;
#endif
