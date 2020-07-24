// 包含必要头文件
#include "includeheaders.h"

void outputTeacher(const teacher *t) // 输出教师信息
{
    printf("教师详情\n\n");
    printf("-----基本信息-----\n"); // 分为四个部分：基本信息，基本工资和补贴，扣款信息和合计
    printf("教师编号：%d\n教师姓名：%s\n", t->teacherID, t->name);
    if (t->gender == 0) // 通过int值判断性别
        printf("教师性别：女\n");
    else
        printf("教师性别：男\n");
    printf("单位名称：%s\n家庭住址：%s\n联系电话：%s\n\n", t->officeAddr, t->homeAddr, t->phoneNumber);
    printf("-----基本工资与补贴-----\n");
    printf("基本工资：%.5lf\n津贴：%.5lf\n生活补贴：%.5lf\n\n", t->basicSalary, t->adds, t->addsLife);
    printf("-----扣款信息-----\n");
    printf("电话费：%.5lf\n水电费：%.5lf\n房租：%.5lf\n所得税：%.5lf\n卫生费：%.5lf\n公积金：%.5lf\n\n", t->telephoneFee,
           t->waterElectricityFee, t->houseFee, t->gainTax, t->healthFee, t->publicFee);
    printf("-----合计-----\n");
    printf("应发工资：%.5lf\n合计扣款：%.5lf\n实发工资：%.5lf\n", t->salaryBeforeFee, t->totalFee, t->salaryAfterFee);
}

void inputTeacher(teacher *t) // 输入教师信息，并通过指针修改传入的t指向的结构体变量
{
    printf("教师详情输入页\n\n");
    printf("-----基本信息-----\n");
    printf("教师编号：");
    scanf("%d", &t->teacherID);
    printf("教师姓名：");
    scanf("%s", t->name);
    printf("教师性别（【0】：女；【1】：男）：");
    scanf("%d", &t->gender);
    printf("单位名称：");
    scanf("%s", t->officeAddr);
    printf("家庭住址：");
    scanf("%s", t->homeAddr);
    printf("联系电话：");
    scanf("%s", t->phoneNumber);
    printf("\n\n-----基本工资与补贴-----\n");
    printf("基本工资：");
    scanf("%lf", &t->basicSalary);
    printf("津贴：");
    scanf("%lf", &t->adds);
    printf("生活补贴：");
    scanf("%lf", &t->addsLife);
    printf("\n\n-----扣款信息-----\n");
    printf("电话费：");
    scanf("%lf", &t->telephoneFee);
    printf("水电费：");
    scanf("%lf", &t->waterElectricityFee);
    printf("房租：");
    scanf("%lf", &t->houseFee);
    printf("所得税：");
    scanf("%lf", &t->gainTax);
    printf("卫生费：");
    scanf("%lf", &t->healthFee);
    printf("公积金：");
    scanf("%lf", &t->publicFee);
    printf("-----输入完毕-----\n\n");

    calcSalaryBeforeFee(t); // 输入完毕后立即计算并传递
    calcTotalFee(t);
    calcSalaryAfterFee(t);
    printf("-----合计-----\n"); // 计算完成后输出合计
    printf("应发工资：%.5lf\n合计扣款：%.5lf\n实发工资：%.5lf\n\n\n", t->salaryBeforeFee, t->totalFee, t->salaryAfterFee);
}


void printvariables() // 输出修改参数
{
    printf("【1】.教师编号\n");
    printf("【2】.教师姓名\n");
    printf("【3】.教师性别\n");
    printf("【4】.单位名称\n");
    printf("【5】.家庭住址\n");
    printf("【6】.联系电话\n");
    printf("【7】.基本工资\n");
    printf("【8】.津贴\n");
    printf("【9】.生活补贴\n");
    printf("【10】.电话费\n");
    printf("【11】.水电费\n");
    printf("【12】.房租\n");
    printf("【13】.所得税\n");
    printf("【14】.卫生费\n");
    printf("【15】.公积金\n\n");
    printf("【0】.退出修改\n");
}
