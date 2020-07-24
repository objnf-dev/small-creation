#include "SqQueue.h"

int main() 
{
	SqQueue Q;
	InitQueue(Q);
	cout << "初始化队列成功。" << endl;
	char inQueue = 'a';
	for (int i = 0; i < 4; i++)
		EnQueue(Q, (char)((int)inQueue + i));
	cout << "Q.front=" << Q.front << " Q.rear=" << Q.rear << endl;
	cout << "插入e：";
	EnQueue(Q, 'e');
	cout << endl << "出队的元素为：";
	for (int i = 0; i < 3; i++)
	{
		DataType tmp;
		DeQueue(Q, tmp);
		cout << tmp << " ";
	}
	cout << "Q.front=" << Q.front << " Q.rear=" << Q.rear << endl;
	cout << endl << "遍历队列：";
	TraverseQueue(Q);
	inQueue = 'e';
	for (int i = 0; i < 3; i++)
		EnQueue(Q, (char)((int)inQueue + i));
	cout << endl << "Q.front=" << Q.front << " Q.rear=" << Q.rear << endl;
	while (!QueueEmpty(Q))
	{
		DataType tmp;
		DeQueue(Q, tmp);
	}
	cout << "队列销毁成功";
	return 0;
}