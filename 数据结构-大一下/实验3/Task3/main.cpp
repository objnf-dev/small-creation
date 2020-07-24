#include "LinkStack.h"

void Conversion(int N, int m)
{
    SNode *number_stack;
    InitStack(number_stack);
    int back_num = N;
    do
    {
        DataType res=N%m;
        Push(number_stack, res);
        N=N/m;
    }
    while(N != 0);
    cout<<back_num<<"的"<<m<<"进制转换结果为：";
    while(!StackEmpty(number_stack))
    {
        DataType tmp;
        Pop(number_stack, tmp);
        cout<<tmp;
    }
    cout<<endl;
    return;
}

int main()
{
    
    int N,m;
    cout<<"请输入N:";
    cin>>N;
    cout<<"请输入m:";
    cin>>m;
    Conversion(N,m);
    return 0;
}