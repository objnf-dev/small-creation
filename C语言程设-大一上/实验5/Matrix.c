/*
 * Calculate the multiplication of the two matrix.
 * ZWT. 18/11/09
 */
#include <stdio.h>

int main()
{
    int a[3][4],b[4][3];
    int i,j;

    printf("Input Matrix A:\n");  // Input.
    for(i=0;i<3;i++)
        for(j=0;j<4;j++)
            scanf("%d",&a[i][j]);

    printf("Input Matrix B:\n");
    for(i=0;i<4;i++)
        for(j=0;j<3;j++)
            scanf("%d",&b[i][j]);

    printf("The answer is:\n");    // Calculate and output.
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            int sum=0,s;
            for(s=0;s<4;s++)
                sum += a[i][s]*b[s][j];
            printf("%d ",sum);
        }
        printf("\n");   // Change the line.
    }

    return 0;
}
