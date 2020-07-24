#include "LinkQueue.h"

//初始化带头结点的链队列
int InitQueue( LinkQueue &Q )
{   //构造只有一个空头结点的链式队列
    //头、尾指针均指向头结点
	Q.front=Q.rear=new QNode;
	if(Q.front==NULL) {cout<<"出错";return 0;}
	Q.front->next=NULL;
	return 1;
} 

//判链队列空
int QueueEmpty(LinkQueue &Q)
{
	if(Q.front->next==NULL)
		return 1;
	else
		return 0;
}

//入队
int EnQueue( LinkQueue &Q, DataType item )
{	//单链表的尾插法

	QNode *t=new QNode; //①生成新结点
	if(t==NULL) {cout<<"出错";return 0;}
	t->data=item; t->next=NULL;	

	Q.rear->next=t; //②在尾结点后插入新结点

	Q.rear=t; //③更新尾指针
	return 1;
} 

//出队
int DeQueue( LinkQueue &Q,DataType &item )
{	//删除单链表的表头元素

	//①判空
	if(Q.front==Q.rear) {cout<<"队空";return 0;}

	QNode *t=Q.front->next;
	item=t->data;
	Q.front->next=t->next; //②删除队头结点 

	if(Q.rear==t)  //③若删除尾结点须更新尾指针
		Q.rear=Q.front;
	delete t; 
	return 1;
}

//取队头元素
int GetFront( LinkQueue &Q, DataType &item )
{	
	if(Q.front==Q.rear) {cout<<"队空";return 0;}
	item=Q.front->next->data;
	return 1;
}

//遍历队列
int TraverseQueue(LinkQueue &Q)
{
	if(Q.front==Q.rear) {cout<<"队空";return 0;}
	QNode *p=Q.front->next;
	while(p!=NULL)
	{
		cout<<p->data.name<<" ";
		p=p->next;
	}
	cout<<endl;
	return 1;
}

//释放链队列
void Destroy(LinkQueue &Q)
{
	while(Q.front!=NULL)
	{
		Q.rear=Q.front;
		Q.front=Q.front->next;
		delete Q.rear;
	}
}

void Dancing(LinkQueue &QLady, LinkQueue &QGentlemen)
{
	cout << "配对结果：" << endl;
	for (int i = 0; i < 5; i++)
	{
		DataType tmp[2];
		DeQueue(QLady, tmp[0]);
		DeQueue(QGentlemen, tmp[1]);
		cout << tmp[0].name << " " << tmp[1].name << endl;
	}
}