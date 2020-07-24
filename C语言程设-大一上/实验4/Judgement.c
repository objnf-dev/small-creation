/*
 * Find who entered the competition.
 * ZWT. 18.11.2
 */
#include <stdio.h>

int A,B,C,D,E;
void print()       // A function to print the result.
{
    if(A==1)  printf("A");
    if(B==1)  printf("B");
    if(C==1)  printf("C");
    if(D==1)  printf("D");
    if(E==1)  printf("E");
    printf("\n");
    return;
}

int main() {
    for(A=0;A<=1;A++)
        for(B=0;B<=1;B++)
            for(C=0;C<=1;C++)
                for(D=0;D<=1;D++)
                    for(E=0;E<=1;E++)
                    {
                        if((B+C==1) && (C+D==0 || C+D==2) && (D+E>=1))  // Check the statement.
                        {
                            if(E==1 && A+D!=2)
                                continue;
                            else if(A==1 && B==0)
                                continue;
                            else
                                print();   // Output.
                        }
                    }
    return 0;
}