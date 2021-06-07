#include "LinkQueue.h"

int main()
{
	LinkQueue Q;
	InitQueue(Q);
	cout << "队列初始化成功" << endl;
	char inQueue = 'a';
	for (int i = 0; i < 5; i++)
		EnQueue(Q, (char)((int)inQueue + i));
	cout << "遍历队列：";
	TraverseQueue(Q);
	Reverse(Q);
	cout << endl << "再次遍历：";
	TraverseQueue(Q);
	Destroy(Q);
	cout << endl << "队列销毁成功。";
	return 0;
}