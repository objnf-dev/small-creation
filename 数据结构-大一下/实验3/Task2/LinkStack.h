#include <iostream>
using namespace std;

typedef int DataType;
struct SNode
{ //链栈结点数据类型
	DataType	data; //数据域
	struct SNode	*next; //后继结点指针
}; 


//初始化空链栈
int InitStack(SNode *&top);

//判链栈空
int StackEmpty(SNode *top);

//入栈
int Push(SNode *top, DataType item);

//出栈
int Pop(SNode *top, DataType &item);

//取栈顶
int GetTop(SNode *top, DataType &item);

//释放链栈
void Destroy(SNode *&top);

int TraverseStack(SNode *top);
