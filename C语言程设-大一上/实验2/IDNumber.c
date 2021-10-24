/*
    ID Number Checker.
    ZWT. 18/10/20
*/

#include<stdio.h>

int main()
{
    int idSum=0,idCheckNum=0;
    int i;
    int idWeight[]={7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2}; // Store the weight of every digit.
    char idMod[]={'1','0','X','9','8','7','6','5','4','3','2'},idNumber[19];

    printf("Please input your ID number:");
    scanf("%s",&idNumber);
    for(i=0;i<17;i++)      // Calculate the sum.
        idSum+=(idNumber[i]-'0')*idWeight[i];
    if(idNumber[17]==idMod[idSum%11])       // Verify the last digit.
        printf("ID Number is legal.\n");
    else
        printf("ID Number is illegal.\n");
    return 0;
}
