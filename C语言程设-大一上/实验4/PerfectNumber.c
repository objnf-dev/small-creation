/*
 * Find the perfect number under 2000.
 * ZWT. 18/11/2
 */
#include <stdio.h>

int main() {
    int sum=0,i,j;
    for(i=1;i<=2000;i++)  // Loop the number.
    {
        for(j=1;j<i;j++)  // Find the factor.
        {
            if(i%j==0)
                sum+=j;
        }
        if(sum == i)
            printf("%d\n",i);  // Output.
        sum=0;  // Set sum value to 0 for the next loop.
    }
    return 0;
}