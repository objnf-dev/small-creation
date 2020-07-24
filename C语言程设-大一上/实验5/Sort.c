/*
 * Sort the numbers.
 * ZWT. 18/11/09
 */
#include <stdio.h>

int main()
{
    int n,num[21],i;

    printf("Input n:");   // Input n.
    scanf("%d",&n);

    printf("Input all the numbers:\n");
    for(i=0;i<n;i++)
        scanf("%d",&num[i]);

    printf("The number you add:");
    scanf("%d",&num[n]);

    i=n;       // Start sorting.
    while(1)
    {
        int tmp;
        if(num[i] < num[i-1])
        {
            tmp=num[i-1];
            num[i-1]=num[i];
            num[i]=tmp;
        }
        else    // Check whether the sorting is completed.
            break;
        i--;  // Move forward.
    }

    for(i=0;i<=n;i++)  // Output.
        printf("%d ",num[i]);
    return 0;
}
