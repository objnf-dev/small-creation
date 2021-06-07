#include <iostream>
using namespace std;

#define STACKSIZE 10
typedef int DataType;
typedef struct 
{
	DataType	items[STACKSIZE]; 
	int		top; 	
}SqStack;

//初始化空顺序栈
int InitStack(SqStack &S);

//判顺序栈空
int StackEmpty(SqStack &S);

//入栈
int Push(SqStack &S, DataType item);

//出栈
int Pop(SqStack &S, DataType &item);

//取栈顶
int GetTop(SqStack &S, DataType &item);

