/*
 * 编写strcat函数
 * ZWT. 18/11/23
*/
#include <stdio.h>

char* strcat(char *dst,char *src)  // 定义函数
{
    int i,j;
    for(i=0;*(dst+i)!='\0';i++)  // 达到dst末尾
        continue;
    for(j=0;*(src+j)!='\0';j++)  // 把dst后面的内存复写
        *(dst+i+j)=*(src+j);
    *(dst+i+j)='\0';  // 添加结束空字符
    return dst;
}

int main()
{
    char s1[100],s2[100];
    gets(s1);  // 输入两个字符串
    gets(s2);
    strcat(s1,s2);  // 进行拼接
    printf("%s",s1);
    return 0;
}
