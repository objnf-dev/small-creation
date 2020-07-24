/*
 * 编写strlen函数
 * ZWT. 18/11/23
*/

#include <stdio.h>

int strlen(char *s) // 定义函数
{
    int stringLen=0,i;
    for(i=0;*(s+i)!='\0';i++) // 开始逐个地址检查，遇到空字符结束
        stringLen++;
    return stringLen;  // 返回长度值
}

int main()
{
    char s[100],len=0;
    gets(s);
    len=strlen(s);
    printf("len=%d",len);
    return 0;
}
