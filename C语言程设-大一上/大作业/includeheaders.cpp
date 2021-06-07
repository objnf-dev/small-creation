#include "includeheaders.h"

// 计算包含了补贴的应发工资总额
void calcSalaryBeforeFee(teacher *tmp)
{
    tmp->salaryBeforeFee = tmp->basicSalary + tmp->adds + tmp->addsLife;
}

// 计算包含各项费用的扣除费用总额
void calcTotalFee(teacher *tmp)
{
    tmp->totalFee = tmp->gainTax + tmp->healthFee + tmp->houseFee + tmp->publicFee + tmp->telephoneFee + tmp->waterElectricityFee;
}

// 相减求得实发工资总额
void calcSalaryAfterFee(teacher *tmp)
{
    tmp->salaryAfterFee = tmp->salaryBeforeFee - tmp->totalFee;
}
