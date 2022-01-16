// 防止被重复包含的头
#ifndef INCLUDEHEADERS_H
#define INCLUDEHEADERS_H

// 主要放置基础头文件
#include <cstdio>       // C标准输入输出
#include <cstdlib>      // C标准库函数
#include <cstring>      // C字符串函数
#include <string>

// 使用C方式加载剩余头文件
extern "C"
{
#include <io.h>         // C扩展输入输出
#include <windows.h>    // C窗口
#include "sqlite3.h"    // SQLite3的库
}

// 使用标准命名空间
using namespace std;

// 定义 teacher 结构体
typedef struct Teacher {
    int teacherID;
    char name[10];
    int gender;
    char officeAddr[100];
    char homeAddr[100];
    char phoneNumber[20]; // 电话号码位数超过int表示范围，利用字符串表示
    double basicSalary;
    double adds;
    double addsLife;
    double telephoneFee;
    double waterElectricityFee;
    double houseFee;
    double gainTax;
    double healthFee;
    double publicFee;
    double salaryBeforeFee;
    double totalFee;
    double salaryAfterFee;
} teacher;

// 分别是计算实发工资、应发工资和合计扣款的函数定义
void calcSalaryAfterFee(teacher *tmp);

void calcSalaryBeforeFee(teacher *tmp);

void calcTotalFee(teacher *tmp);

#endif