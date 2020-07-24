/*
 *  Claculate the number of the words in the string.
 *  ZWT. 18/12/3
*/

#include <stdio.h>

int strcnt(char *str)  // 定义函数
{
    int ans=0;  // 初始化单词个数为0
    for(;*str!='\0';str++)  // 循环str内的每一个字符
        if(*str!=' ') // 如果字符不是空格
            if(*(str+1)==' ') // 如果下一个字符是空格，则单词数量加一
                ans++;
    return ans; // 返回单词的个数
}

int main()
{
    char s1[100]; // 定义字符串
    gets(s1); // 输入
    printf("%d",strcnt(s1)); // 调用strcnt函数并输出
    return 0;
}
