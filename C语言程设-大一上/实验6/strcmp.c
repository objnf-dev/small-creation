/*
 * 编写strcmp函数
 * ZWT. 18/11/23
*/
#include <stdio.h>

int strcmp(char *s1,char *s2)  // 定义函数
{
    int i=0;
    while(1)
    {
        char a=*(s1+i),b=*(s2+i); // 提取当前需要比较的字符
        i++;
        if(a=='\0' && b=='\0')  // 进行比较
            return 0;
        else if(a>b)
            return 1;
        else if(a<b)
            return -1;
        else if(a==b)
            continue;
    }
}

int main()
{
    char s1[100],s2[100];
    gets(s1);  // 输入两个字符串
    gets(s2);
    printf("strcmp returns %d",strcmp(s1,s2));  // 输出strcmp函数的返回值
    return 0;
}
