/*
 * Delete the duplicated items in the string.
 * ZWT. 18/12/3
*/

#include <stdio.h>

char* del(char *src,char *dst)   // 定义函数
{
    char *start=dst;  // 保存开头处地址
    for(;*src!='\0';src++)  // 循环src中每一个元素
    {
        if(*src == *(src+1))  // 如果前后两个元素相同，则跳过
            continue;
        else  // 否则将此元素加入dst中
        {
            *dst=*src;
            dst++;
        }
    }
    *dst='\0';  // 给dst添加结束符
    return start;  // 返回dst开头处地址
}

int main()
{
    char s1[100],s2[100];  // 定义两个等大字符数组
    gets(s1);  // 输入
    printf("%s",del(s1,s2));  // 调用函数并输出dst字符串
    return 0;
}
