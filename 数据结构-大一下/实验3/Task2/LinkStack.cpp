#include "LinkStack.h"

//初始化空链栈
int InitStack(SNode *&top)
{
	top=new SNode; //申请头结点空间
	if(top==NULL) //申请空间是否失败判断	
	{
		cout<<"初始化错误";
		return 0; //初始化空栈失败
	}
	top->next=NULL; //链栈头结点没有下一个结点为空栈
	return 1; //初始化空栈成功
}

//判栈空
int StackEmpty(SNode *top)
{
	if(top->next==NULL)//判链栈头结点是否没有下一个结点为空
		return 1; //为空栈返回1
	else
		return 0; //不为空栈返回0
}

//入栈：入栈前必判栈是否为满，但链栈理论上没有满的概念，所以不用考虑栈情况
int Push(SNode *top, DataType item)
{ //带头结点单链表的表头插入法

	SNode *t=new SNode; //①生成新结点
    if(t==NULL) {cout<<"出错";return 0;} //处理申请空间失败情况
	t->data=item; //数据放入刚刚申请的结点空间的data数据项

	//②在栈顶插入新结点
	t->next=top->next; //把刚申请的结点加入到栈顶
	top->next=t; //刚加入的结点为第一个结点（非头结点），从而实现先进后出（栈的操作特点）
	return 1; //入栈成功返回1
}


//出栈：出栈前必判断是否空栈，如果空栈是没有数据可出栈
int Pop(SNode *top, DataType &item)
{  //删除单链表的第一个结点

	//①判断栈是否为空
    if(top->next==NULL) {cout<<"栈空";return 0;} //空栈时，不能出栈，返回0

	//②删除栈顶元素
    SNode *t=top->next; //用t临时指向栈顶结点，即第一个结点
    top->next=t->next; //栈顶结点把第2个结点改为第1给结点的位置（即把第2个结点设为栈顶）
    item=t->data; //删除之前把被删的元素值有参数item带到调用点，以备需用到
	delete t; //释放原来的栈顶元素空间
    return 1; //出栈成功返回1
}

                                                                                                                                                                                                      
//取栈顶：必判是否为空栈，纯读取栈顶元素值，不移动栈顶的位置
int GetTop(SNode *top, DataType &item)
{  
	//①判断栈是否为空
    if(top->next==NULL){cout<<"栈空";return 0;}

	//②取栈顶元素
    item=top->next->data; //栈顶元素值有参数item带回到调用点
    return 1; //读取成功返回1
}


//释放链栈：一个一个结点删除
void Destroy(SNode *&top)
{
	SNode *p; //p为辅助操作的临时指针，要移动链栈时必须用到另为一个临时指针
	while(top!=NULL)
	{
		p=top; //从头结点开始删除
		top=top->next; //栈顶指向下一个结点
		delete p; //删除的是已经单独脱离的结点，这样的目的是不会丢失结点
	}
}

int TraverseStack(SNode *top)
{
	SNode *tmpstack;
	InitStack(tmpstack);
	cout<<"栈中剩余元素为：";
	while(!StackEmpty(top)){
		DataType tmp;
		Pop(top, tmp);
		cout<<tmp<<" ";
		Push(tmpstack, tmp);
	}
	cout<<endl;
	while(!StackEmpty(tmpstack))
	{
		DataType tmp;
		Pop(tmpstack, tmp);
		Push(top, tmp);
	}
	Destroy(tmpstack);
	return 1;
}
