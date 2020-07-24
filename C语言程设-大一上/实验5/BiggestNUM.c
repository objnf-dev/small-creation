/*
 * Find the biggest number in the 5x6 matrix.
 * ZWT. 18/11/09
 */
#include <stdio.h>

int main()
{
    int a[5][6]={{0}},maxVAL=0,maxX=0,maxY=0,i,j;  // Init.
    for(i=0;i<5;i++)
        for(j=0;j<6;j++)  // Input the number and compare.
        {
            scanf("%d",&a[i][j]);
            if(i==0 && j==0)
                maxVAL=a[i][j];
            else if(a[i][j] > maxVAL)
            {
                maxVAL=a[i][j];
                maxX=i;
                maxY=j;
            }
        }
    printf("Max value=%d\nRow=%d Column=%d",maxVAL,maxX,maxY);  // Output.
    return 0;
}