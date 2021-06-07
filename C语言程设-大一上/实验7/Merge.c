/*
* 合并两个升序序列。
* ZWT. 18/12/3
*/

#include <stdio.h>
#include <stdlib.h>

int mrge(const int *str1,const int *str2,int *dst,int lenstr1,int lenstr2) // 定义函数
{
    int i=0,j=0,k=0; // 定义三个下标位置
    int brk=0; // 判断哪一个序列先达到末尾
    while(1) // 开始循环
    {
        if(str1[i]==str2[j])  // 如果两个数字相等，将其直接加入新序列
        {
            dst[k]=str1[i];
            i++;
            j++;
            k++;
        }
        else if(str1[i]>str2[j]) // 若1中的大于2，取2中的加入新序列
        {
            dst[k]=str2[j];
            j++;
            k++;
        }
        else if(str1[i]<str2[j]) // 若2中的大于1，取1中的加入序列
        {
            dst[k]=str1[i];
            i++;
            k++;
        }
        if(i==lenstr1-1) // 若str1先达到末尾，brk=1
        {
            brk=1;
            break;
        }
        else if(j==lenstr2-1) // 若str2先达到末尾，brk=2
        {
            brk=2;
            break;
        }
    }
    if(brk==1)
        for(;j<lenstr2;j++,k++)
                dst[k]=str2[j];
    else if(brk==2)
        for(;i<lenstr1;i++,k++)
            dst[k]=str1[i];
    return k-1;

}

int main()
{
    int s1[]={3,4,5,6,8,10,24,35,45,46,57},s2[]={1,3,5,7,8,9,12,13,16,20,34,48}; // 定义两个已知的升序序列
    int len1=sizeof(s1)/4,len2=sizeof(s2)/4,ans[50]={0},len=mrge(s1,s2,ans,len1,len2),i; // 求两个序列长度，定义目标序列ans，调用mrge函数并接收其返回值，同时定义循环变量。
    for(i=0;i<len;i++) // 循环输出新的升序序列
        printf("%d ",ans[i]);
    return 0;
}
