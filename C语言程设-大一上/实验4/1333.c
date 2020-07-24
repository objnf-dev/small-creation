/*
 * Find the value of a,b,c
 * ZWT. 18/11/2
*/
#include <stdio.h>

int main() {
    int a=0,b=0,c=0,sum=0;
    for(a=0;a<=9;a++)
        for(b=0;b<=9;b++)
            for(c=0;c<=9;c++)
            {
                sum=(a*100+b*10+c)+(c*100+b*10+a);
                if ( sum == 1333)   // Check if the number fits the condition.
                    printf("a=%d b=%d c=%d\n", a, b, c);  // Output
            }
    return 0;
}