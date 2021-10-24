#include <iostream>
using namespace std;

typedef char DataType;

struct QNode
{ //结点结构
	DataType	data; 
	QNode	*next; 
}; 

typedef struct 
{ //队列结构
	QNode	*front;
	QNode	*rear; 
}LinkQueue; 

//初始化带头结点的链队列
int InitQueue( LinkQueue &Q );

//判链队列空
int QueueEmpty(LinkQueue &Q);

//入队
int EnQueue( LinkQueue &Q, DataType item );

//出队
int DeQueue( LinkQueue &Q,DataType &item );

//取队头元素
int GetFront( LinkQueue &Q,DataType &item );

//遍历队列
int TraverseQueue(LinkQueue &Q);

//释放链队列
void Destroy(LinkQueue &Q);