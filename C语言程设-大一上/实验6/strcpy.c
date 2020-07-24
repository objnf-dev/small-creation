/*
 * 编写strcpy函数
 * ZWT. 18/11/23
*/

#include <stdio.h>

char* strcpy(char *dst,char *src)  // 定义函数
{
    int i;
    for(i=0;*(src+i)!='\0';i++)  // 通过循环覆盖dst内存中的值
        *(dst+i)=*(src+i);
    *(dst+i)='\0';  // 复制结束后加入结束符
    return dst;  // 返回地址
}
int main()
{
    char s1[100],s2[100];
    gets(s1);  // 输入两个字符串
    gets(s2);
    strcpy(s1,s2);   // 调用函数
    printf("%s",s1); // 输出结果
    return 0;
}
