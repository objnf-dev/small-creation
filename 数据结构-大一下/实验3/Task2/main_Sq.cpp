#include "SqStack.h"

int main(){
    SqStack data;
    InitStack(data);
    for(int i=1;i<=10;i++){
        Push(data, i);
    }
    for(int i=0;i<=2;i++){
        DataType tmp;
        Pop(data, tmp);
        cout<<"出栈元素为："<<tmp<<endl;
    }
    TraverseStack(data);
    while(!StackEmpty(data)){
        DataType tmp;
        Pop(data, tmp);
    }
    cout<<"栈释放成功"<<endl;
    return 0;
}