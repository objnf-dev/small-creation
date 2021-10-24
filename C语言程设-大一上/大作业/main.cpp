// 开始包含基本头文件
#include "includeheaders.h"
#include "dboperation.h"
#include "softio.h"

// 函数声明
int distribute(int opt);
void showWelcome();
void show();
int searchMenu();
int addMenu();
int updateMenu();
int deleteMenu();

// 数据库连接指针定义
sqlite3 *dbaccess = NULL;

void showWelcome() // 运行前先显示欢迎信息
{
    printf("\n                         欢迎使用教师工资管理系统\n\n");  // 欢迎语，3秒后消失。
    printf("         该系统由 ObjNF 同学制作。\n\n");
    printf("                                                    最后更新：2018/01/04");
    Sleep(3000);
}

void show() // 主菜单函数
{
    system("cls"); // 清屏
    printf("\n                         教师工资管理系统 - 主菜单\n\n"); // 输出主菜单
    printf("  请输入您需要进行的操作前的序号，并回车。\n\n\n\n");
    printf("  1. 【新增】教师信息\n\n");
    printf("  2. 【修改】教师信息\n\n");
    printf("  3. 【删除】教师信息\n\n");
    printf("  4. 【查询】教师信息\n\n");
    printf("  0. 【退出】\n\n\n\n");

    printf("  请输入操作代码："); // 提示用户输入操作代码
}

// 程序入口点
int main()
{
    int opt = -1;
    checkFileStatement(); // 先检查数据文件状态
    dbaccess = connectDB(); // 连接数据库，并传递数据库连接指针
    showWelcome(); // 显示欢迎消息
    while (opt <= 4 && opt >= -1)
    {
        if(opt == -1)
        {
            show();
            scanf("%d", &opt);//若要求输出主菜单，要求输入
        }
        opt = distribute(opt);//循环
    }
    return 0;
}

int distribute(int opt) // 依据操作码重定向函数
{
    int ret = 0; // 初始化操作为0
    switch(opt) // switch-case分支以进行条件判断
    {
        case (0): // 用户选择退出
            printf("\n程序将于5秒钟后退出。");
            Sleep(5000); // 等待5秒
            exit(0); // 强制退出程序
        case (1):
            ret = addMenu(); // 添加教师信息
            break;
        case (2):
            ret = updateMenu();//修改
            break;
        case (3):
            ret = deleteMenu();//删除
            break;
        case (4):
            ret = searchMenu();//查找
            break;
        default: // 输入不同于以上所有情况的操作符
            printf("\n无法识别的操作符，自动返回主菜单。");
            ret = -1;
            Sleep(2000);
            break;
    }
    return ret;//返回值用于循环，下一步操作
}

int addMenu() {
    teacher tmp;
    int ret=0, choiceAfterAdd = 0;
    inputTeacher(&tmp);//输入教师信息
    addTeacherToDB(dbaccess, &tmp);//把结构体输入函数，加入数据库
    printf("\n请选择在下一项的操作：\n【1】.新增\n【2】.修改\n【3】.查询\n【0】.返回主菜单\n\n输入您的选择：");//要求后续操作
    scanf("%d", &choiceAfterAdd);
    switch (choiceAfterAdd) {
        case (1):
            printf("\n开始新增教师信息");
            ret = 1;
            break;
        case (2):
            printf("\n开始修改教师信息");
            ret = 2;
            break;
        case (3):
            printf("\n开始查询下一个教师信息");
            ret = 4;
            break;
        case (0):
            printf("\n正在返回主菜单");
            ret = -1;
            Sleep(3000);
            break;
        default:
            printf("\n无法识别的操作符，自动返回主菜单。");
            ret = -1;
            Sleep(2000);
            break;
    }
    return ret;//返回操作要求
}

int searchMenu() //查找教师信息
{
    int searchChoice = 0, ret = 0, teacherID = 0;
    char name[10] = "", userPhoneNumber[20] = "";
    system("cls");
    printf("\n请选择输入教师的信息类型：\n\n【1】.教师编号\n【2】.教师姓名\n【3】.联系电话\n【4】返回\n\n\n输入您的选择：");//要求后续操作
    scanf("%d", &searchChoice);
    switch (searchChoice)
    {
        case (1): //输入教师编号以查询
            printf("\n教师编号：");
            scanf("%d", &teacherID);
            findTeacherinDB(dbaccess,(void*)&teacherID,1);
            break;
        case (2): //输入教师姓名以查询
            printf("\n教师姓名：");
            scanf("%s", name);
            findTeacherinDB(dbaccess,(void*)name,2);
            break;
        case (3): //输入教师联系电话以查询
            printf("\n联系电话：");
            scanf("%s", userPhoneNumber);
            findTeacherinDB(dbaccess,(void*)userPhoneNumber,3);
            break;
        case (4):
            printf("\n2秒后返回主菜单。");
            Sleep(2000);
            ret = -1;
            break;
        default:
            printf("\n无法识别的操作符，自动返回主菜单。");
            ret = -1;
            Sleep(2000);
            break;
    }
    if(ret==0)//未进行返回主菜单操作
    {
        printf("\n请选择在下一项的操作：\n\n【1】.修改\n【2】.删除\n【3】.查询下一个\n【0】.返回主菜单\n\n输入您的选择：");//要求后续操作
        scanf("%d", &ret);
        switch (ret)
        {
            case (1):
                printf("\n开始修改教师信息");
                ret = 2;
                break;
            case (2):
                printf("\n开始删除教师信息");
                ret = 3;
                break;
            case (3):
                printf("\n开始查询下一个教师信息");
                ret = 4;
                break;
            case (0):
                printf("\n正在返回主菜单");
                ret = -1;
                Sleep(3000);
                break;
            default:
                printf("\n无法识别的操作符，自动返回主菜单。");
                ret = -1;
                Sleep(2000);
                break;
        }
    }
    return ret;//返回操作要求
}

int updateMenu()
{
    int teacherID;
    int ret=0;
    int choiceAfterUpdate = 0;
    printf("\n请输入教师编号：");//输入更新特征
    scanf("%d", &teacherID);
    updateTeacherinDB(dbaccess, teacherID);//更新操作
    printf("\n请选择在下一项的操作：\n【1】.新增\n【2】.查询\n【3】.修改\n【0】.返回主菜单\n\n输入您的选择：");//要求后续操作
    scanf("%d", &choiceAfterUpdate);
    switch (choiceAfterUpdate)
    {
        case (1):
            printf("\n开始新增教师信息");
            ret = 1;
            break;
        case (2):
            printf("\n开始查询教师信息");
            ret = 4;
            break;
        case (3):
            printf("\n开始修改教师信息");
            ret = 2;
            break;
        case (0):
            printf("\n正在返回主菜单");
            ret = -1;
            Sleep(2000);
            break;
        default:
            printf("\n无法识别的操作符，自动返回主菜单。");
            ret = -1;
            Sleep(2000);
            break;
    }
    return ret;//返回操作要求
}

int deleteMenu()
{
    int ret=0;
    int teacherID;
    int choiceAfterDelete = 0;
    printf("\n请输入教师编号：");
    scanf("%d", &teacherID);//要求输入删除教师特征
    deleteTeacherinDB(dbaccess, teacherID);//删除操作
    printf("\n请选择在下一项的操作：\n【1】.新增\n【2】.查询\n【0】.返回主菜单\n\n输入您的选择：");//要求后续操作
    scanf("%d", &choiceAfterDelete);
    switch (choiceAfterDelete)
    {
        case (1):
            printf("\n开始新增教师信息");
            ret = 1;
            break;
        case (2):
            printf("\n开始查询教师信息");
            ret = 4;
            break;
        case (0):
            printf("\n正在返回主菜单");
            ret = -1;
            Sleep(3000);
            break;
        default:
            printf("\n无法识别的操作符，自动返回主菜单。");
            ret = -1;
            Sleep(2000);
            break;
    }
    return ret;//返回操作要求
}
