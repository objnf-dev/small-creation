/*
 * Output the order of the chosen kids.
 * ZWT. 18/11/09
 */
#include <stdio.h>
#define M 10  // 定义M值

int main()
{
    int n,nowAt=0,totalOut=0,a[M]={0};   // 初始化

    printf("Input n:");    // 输入n
    scanf("%d",&n);

    while(totalOut != M)  // 判断是否输出过所有数字
    {
        int nowPassed=0;
        while(1)
        {
            if(a[nowAt]==0)   // 如果现在下标指示的数组元素为0，则“通过”+1
                nowPassed++;
            if(nowPassed==n)  // 如果这是报数的第n个同学，则跳出循环
                break;
            nowAt++;
            if(nowAt == M)   // 如果当前下标越界则回到第一个元素
                nowAt=0;
        }
        a[nowAt]=1;     // 设置该学生已经出圈
        printf("%d ",nowAt+1);   // 输出该学生编号
        totalOut++;    // 已经输出的数字个数+1
    }
    return 0;
}
