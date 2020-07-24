/*
 * P165 Q2.
 * Find and swap the biggest number.
 * ZWT. 18/11/2
*/
#include <stdio.h>

int main()
{
    int n,a[20],biggestNum=0,biggestNumKey=0;
    int i,tmp;
    printf("Please input n:");
    scanf("%d",&n);     // Input the amount of the number.
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        if(i==0)      // Init the biggest number.
            biggestNum=a[i];
        else if(a[i] > biggestNum)   // Find the biggest number.
        {
            biggestNum=a[i];
            biggestNumKey=i;
        }
    }
    tmp=a[0];    // Swap the value
    a[0]=biggestNum;
    a[biggestNumKey]=tmp;
    for(i=0;i<n;i++)  // Output
    {
        printf("%d ",a[i]);
    }
    return 0;
}