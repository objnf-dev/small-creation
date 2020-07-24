#include "SqStack.h"

//初始化空顺序栈
int InitStack(SqStack &S)
{
	S.top=-1;
	return 1;
}

//判栈空
int StackEmpty(SqStack &S)
{
	if(S.top==-1)
		return 1;
	else
		return 0;
}

//入栈
int Push(SqStack &S, DataType item)
{
	if(S.top >= STACKSIZE-1)
	{
		cout<<"栈满"<<endl;
        return 0;
    }
    S.top++;
    S.items[S.top]=item;
	return 1;
}

//出栈
int Pop(SqStack &S, DataType &item)
{
    if(S.top <= -1){
            cout<<"栈空"<<endl;
            return 0;
    }
	item=S.items[S.top];
	S.top--;
	return 1;
}
                                                                                                                                                                                                      
//取栈顶
int GetTop(SqStack &S, DataType &item)
{
    if(S.top <= -1){
            cout<<"栈空"<<endl;
            return 0;
    }
	item=S.items[S.top];
	return 1;
}

int TraverseStack(SqStack &S)
{
	SqStack P;
	InitStack(P);
	cout<<"栈中剩余元素为：";
	while(!StackEmpty(S))
	{
		DataType tmp;
		Pop(S, tmp);
		cout<<tmp<<" ";
		Push(P, tmp);
	}
	cout<<endl;
	while(!StackEmpty(P))
	{
		DataType tmp;
		Pop(P, tmp);
		Push(S, tmp);
	}
	return 1;
}
