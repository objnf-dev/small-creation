// 包含必要的头文件
#include "includeheaders.h"
#include "softio.h"

// 各函数的声明
void checkFileStatement();
sqlite3 *connectDB();
int isTableExistCallback(void *, int nCount, char **cValue, char **cName);
void addTeacherToDB(sqlite3 *teacherdb, const teacher *t);
void findTeacherinDB(sqlite3 *teacherdb,void *data,int choice);
int findTeacherCallback(void *ret, int nCount, char **cValue, char **cName);

void checkFileStatement() // 用于检查数据库文件状态
{
    if (!access("data.db", 0)) // 是否存在
    {
        if (access("data.db", 6)) // 是否可读写,不可读写直接退出。
        {
            printf("数据库文件无法读写，请检查是否有程序占用数据文件，并在占用解除后重启本程序。\n"); // 输出无法读写信息
            system("pause"); // 暂停
            exit(0); // 强制退出
        }
    }
    else // 不存在则开始新建
    {
        printf("数据库文件丢失，3秒后新建。\n");
        Sleep(3000); // 等待三秒
        sqlite3 *teacherdb; // 定义数据库访问指针
        sqlite3_open("data.db", &teacherdb); // 打开数据库文件，不存在的话就会自动新建
        sqlite3_close(teacherdb); // 关闭数据库文件，新建完成
    }
}

sqlite3* connectDB() // 用于连接数据库
{
    sqlite3 *teacherdb; // 定义数据库访问指针
    sqlite3_open("data.db", &teacherdb); // 打开数据库文件
    string sql = "SELECT COUNT(*) FROM sqlite_master WHERE TYPE='table' AND NAME='teacherdata';";
    char *err; // 定义sql语句和错误消息变量
    int isTableExist = 0; // 定义变量，是否存在表
    int retc = sqlite3_exec(teacherdb, sql.data(), isTableExistCallback, &isTableExist, &err); // 查询数据库
    if (retc != SQLITE_OK) // 如果查询语句执行失败
    {
        printf("连接数据库失败。错误码：%d，错误信息：%s\n", retc, err); // 抛出错误
        exit(0); //强制退出
    }
    if (isTableExist == 0) // 如果不存在数据表
    {
        printf("未找到数据表，新建中...\n"); // 提醒用户
        // 使用sql语句在当前文件中新建
        string sqlct = "CREATE TABLE teacherdata(" \
                    "teacherID      INT PRIMARY KEY NOT NULL," \
                    "name           TEXT            NOT NULL," \
                    "gender         INT             NOT NULL," \
                    "officeAddr     TEXT            NOT NULL," \
                    "homeAddr       TEXT            NOT NULL," \
                    "phoneNumber    TEXT            NOT NULL," \
                    "basicSalary    REAL            NOT NULL," \
                    "adds           REAL            NOT NULL," \
                    "addsLife       REAL            NOT NULL," \
                    "telephoneFee   REAL            NOT NULL," \
                    "waterElectricityFee REAL       NOT NULL," \
                    "houseFee       REAL            NOT NULL," \
                    "gainTax        REAL            NOT NULL," \
                    "healthFee      REAL            NOT NULL," \
                    "publicFee      REAL            NOT NULL," \
                    "salaryBeforeFee REAL           NOT NULL," \
                    "totalFee       REAL            NOT NULL," \
                    "salaryAfterFee REAL            NOT NULL);";
        int retc2 = sqlite3_exec(teacherdb, sqlct.data(), NULL, NULL, &err); // 调用数据表创建语句
        if (retc2 != SQLITE_OK) // 如果sql语句执行失败
        {
            printf("创建表失败。错误码：%d，错误信息：%s\n", retc2, err); // 提示用户
            exit(0); // 数据表不存在，无法执行后续操作，强制退出
        }
    }
    return teacherdb; // 返回sql连接指针，在后续操作中使用
}

int isTableExistCallback(void *ret, int nCount, char **cValue, char **cName) // 判断数据表是否存在时的回调函数
{
    int *retint = (int *) ret; // 指针强制类型转换
    if (atoi(cValue[0]) == 0) // 读取sql语句的返回值，执行操作
        *retint = 0;
    else
        *retint = 1;
    return SQLITE_OK; // 回调执行成功，返回0
}

void addTeacherToDB(sqlite3 *teacherdb, const teacher *t) // 将教师数据写入数据库
{
    char sql[500] = "", *err; // 定义sql语句和错误指针
    sprintf(sql,
            "INSERT INTO teacherdata VALUES (%d,'%s',%d,'%s','%s','%s',%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf);",
            t->teacherID, t->name, t->gender, t->officeAddr, t->homeAddr, t->phoneNumber, t->basicSalary, t->adds,
            t->addsLife, t->telephoneFee, t->waterElectricityFee, t->houseFee, t->gainTax, t->healthFee, t->publicFee,
            t->salaryBeforeFee, t->totalFee, t->salaryAfterFee); // 此处构造sql语句并printf到字符串中
    int retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err); // 执行sql语句
    if (retc != SQLITE_OK) // 若sql执行失败
        printf("添加教师数据失败。错误码：%d，错误信息：%s\n", retc, err); // 提醒用户
    else // 否则
        printf("添加教师数据成功。\n"); // 告知用户成功
}

int check;

void findTeacherinDB(sqlite3 *teacherdb,void *data,int choice)
{
    char sql[300] = "",*err;
    teacher t;
    check = 0;
    const char col[][15]={"teacherID","name","phoneNumber"};
    if(choice == 1)//若选择ID查询教师信息
        sprintf(sql, "SELECT * FROM teacherdata WHERE %s=%d", col[choice-1],*(int*)data);
    else
    {
        const char *str=(const char*)data;//若选择联系电话或姓名查询教师信息
        sprintf(sql, "SELECT * FROM teacherdata WHERE %s=\'%s\'", col[choice-1],str);//列名和其中内容
    }
    int retc = sqlite3_exec(teacherdb, sql, findTeacherCallback, &t, &err);//若调用callback函数，返回check==1的信息与结构体t的内容
    if (retc != SQLITE_OK)
        printf("查询教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
    else
    {
        if(check==1)//callback改变check的值
            outputTeacher(&t);
        else
            printf("未查询到该条记录。");//查询数据不存在
    }
}

int findTeacherCallback(void *ret, int nCount, char **cValue, char **cName) // 查询教师时的回调函数
{

    teacher *retdata = (teacher *) ret; // 指针类型转换
    // 结构体赋值
    retdata->teacherID = atoi(cValue[0]);
    strcpy(retdata->name, cValue[1]);
    retdata->gender = atoi(cValue[2]);
    strcpy(retdata->officeAddr, cValue[3]);
    strcpy(retdata->homeAddr, cValue[4]);
    strcpy(retdata->phoneNumber, cValue[5]);
    retdata->basicSalary = atof(cValue[6]);
    retdata->adds = atof(cValue[7]);
    retdata->addsLife = atof(cValue[8]);
    retdata->telephoneFee = atof(cValue[9]);
    retdata->waterElectricityFee = atof(cValue[10]);
    retdata->houseFee = atof(cValue[11]);
    retdata->gainTax = atof(cValue[12]);
    retdata->healthFee = atof(cValue[13]);
    retdata->publicFee = atof(cValue[14]);
    retdata->salaryBeforeFee = atof(cValue[15]);
    retdata->totalFee = atof(cValue[16]);
    retdata->salaryAfterFee = atof(cValue[17]);
    // check设置为1，证明已经调用callback
    check=1;
    // 正常返回
    return SQLITE_OK;
}

void updateTeacherinDB(sqlite3 *teacherdb, int id)
{
    char sql[300] = "", *err , nameAndAddr[300];
    int choice = -1, gen = 0, newID = id;
    double fee;
    teacher t;
    check=0;
    sprintf(sql, "SELECT * FROM teacherdata WHERE teacherID=%d", id); // 构造select语句
    int retc = sqlite3_exec(teacherdb, sql, findTeacherCallback, &t, &err);//调用callback函数返回结构体t的内容
    if (retc != SQLITE_OK)
        printf("查询教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
    else
    {
        if(check==0){
            printf("\n修改项目不存在\n\n");
            return;
        }
        outputTeacher(&t);//输出个人信息
        while (true)
        {
            printvariables();//每次输出修改列表信息
            printf("\n请选择需要修改的项目：");
            scanf("%d", &choice);
            switch (choice)
            {
                default:
                    printf("\n操作代码无效。2秒后自动返回上级菜单。\n");
                    Sleep(2000);
                    break;//回到修改列表
                case (0):
                    printf("2秒后退出。\n");
                    Sleep(2000);
                    choice = 0;//给choice赋值
                    break;
                case (1):
                    printf("请输入新的数据：");
                    scanf("%d", &newID);
                    t.teacherID=newID;//在结构体中更改id
                    sprintf(sql, "UPDATE teacherdata SET teacherID=%d WHERE teacherID=%d", newID, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改id
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (2):
                    printf("请输入新的数据：");
                    scanf("%s", nameAndAddr);
                    sprintf(sql, "UPDATE teacherdata SET name=\'%s\' WHERE teacherID=%d", nameAndAddr, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改姓名
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (3):
                    printf("请输入新的数据：（【0】：女；【1】：男）");
                    scanf("%d", &gen);
                    sprintf(sql, "UPDATE teacherdata SET gender=%d WHERE teacherID=%d", gen, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改性别
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (4):
                    printf("请输入新的数据：");
                    scanf("%s", nameAndAddr);
                    sprintf(sql, "UPDATE teacherdata SET officeAddr=\'%s\' WHERE teacherID=%d", nameAndAddr, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改地址
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (5):
                    printf("请输入新的数据：");
                    scanf("%s", nameAndAddr);
                    sprintf(sql, "UPDATE teacherdata SET homeAddr=\'%s\' WHERE teacherID=%d", nameAndAddr, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改家庭住址
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (6):
                    printf("请输入新的数据：");
                    scanf("%s", nameAndAddr);
                    sprintf(sql, "UPDATE teacherdata SET phoneNumber=\'%s\' WHERE teacherID=%d", nameAndAddr, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改电话
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (7):
                    printf("请输入新的数据：");
                    scanf("%lf", &fee);
                    t.basicSalary=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET basicSalary=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (8):
                    printf("请输入：");
                    scanf("%lf", &fee);
                    t.adds=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET adds=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (9):
                    printf("请输入：");
                    scanf("%lf", &fee);
                    t.addsLife=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET addsLife=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (10):
                    printf("请输入：");
                    scanf("%lf", &fee);
                    t.telephoneFee=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET telephoneFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (11):
                    printf("请输入：");
                    scanf("%lf", &fee);
                    t.waterElectricityFee=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET waterElectricityFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (12):
                    printf("请输入：");
                    scanf("%lf", &fee);
                    t.houseFee=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET houseFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (13):
                    printf("请输入：");
                    scanf("%lf", &fee);
                    t.gainTax=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET gainTax=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (14):
                    printf("请输入：");
                    scanf("%lf", &fee);
                    t.healthFee=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET healthFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
                case (15):
                    printf("请输入：");
                    scanf("%lf", &fee);
                    t.publicFee=fee;//结构体记录该费用
                    sprintf(sql, "UPDATE teacherdata SET publicFee=%lf WHERE teacherID=%d", fee, id);
                    retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
                    if (retc != SQLITE_OK) {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
                    }
                    break;
            }
            if (choice == 0)//跳出修改
                break;
            if (choice == 1)//若更改id，更改新id继续修改
                id=newID;
        }
        calcSalaryBeforeFee(&t);
        calcTotalFee(&t);
        calcSalaryAfterFee(&t);//在结构体中改变后三者费用计算
        sprintf(sql, "UPDATE teacherdata SET salaryBeforeFee = %lf WHERE teacherID = %d", t.salaryBeforeFee, id);
        retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
        if (retc != SQLITE_OK) {
            printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
        }
        sprintf(sql, "UPDATE teacherdata SET totalFee = %lf WHERE teacherID = %d", t.totalFee, id);
        retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
        if (retc != SQLITE_OK) {
            printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
        }
        sprintf(sql, "UPDATE teacherdata SET salaryAfterFee = %lf WHERE teacherID = %d", t.salaryAfterFee, id);
        retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//修改该费用
        if (retc != SQLITE_OK) {
            printf("修改教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
        }
    }
    sprintf(sql, "SELECT * FROM teacherdata WHERE teacherID=%d", id); // 构造select语句
    retc = sqlite3_exec(teacherdb, sql, findTeacherCallback, &t, &err);
    if (retc != SQLITE_OK) {
        printf("查询教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
    }
    else
        outputTeacher(&t);//返回修改后的信息
}


void deleteTeacherinDB(sqlite3 *teacherdb, int id) {
    char sql[300] = "", *err;
    sprintf(sql, "DELETE FROM teacherdata WHERE teacherID=%d", id);
    int retc = sqlite3_exec(teacherdb, sql, NULL, NULL, &err);//删除该条信息
    if (retc != SQLITE_OK) {
        printf("删除教师数据失败。错误码：%d，错误信息：%s\n", retc, err);
        printf("请先确认教师信息是否存在。\n");
    } else
        printf("删除教师数据成功。\n");
}
