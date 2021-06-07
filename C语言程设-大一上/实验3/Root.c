/*
   Calculate the real root of the equation.
   ZWT. 18/10/26.
*/

#include <stdio.h>
#include <math.h>

#define EPSILON 1e-5       // The Accuracy
double xEquation(double x)
{
    return x*x+x*sin(x)-5;      // The equation about x
}

int main()
{
    double a=0,b=5,c=0;
    while(fabs(xEquation(c))>=EPSILON || fabs(b-a)>=EPSILON)    // Judge whether the loop continues or not.
    {
        c=(a+b)/2;
        if(xEquation(a)*xEquation(c)<0)
            b=c;
        else
            a=c;
    }
    printf("The root is:%lf\n",c);
    return 0;
}