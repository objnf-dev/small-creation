#include "LinkStack.h"

int main(){
    SNode *stack;
    InitStack(stack);
    for(int i=1;i<=10;i++)
        Push(stack, i);
    for(int i=0;i<=2;i++){
        DataType tmp;
        Pop(stack, tmp);
        cout<<"出栈元素为："<<tmp<<endl;
    }
    TraverseStack(stack);
    Destroy(stack);
    cout<<"栈释放成功";
    return 0;
}