#include "LinkQueue.h"

int main()
{
	LinkQueue M, W;
	InitQueue(M);
	InitQueue(W);
	DataType MaleName[9] = { {"M1"}, {"M2"}, {"M3"}, {"M4"}, {"M5"}, {"M6"}, {"M7"}, {"M8"}, {"M9"} };
	DataType FemaleName[7] = { {"W1"}, {"W2"}, {"W3"}, {"W4"}, {"W5"}, {"W6"}, {"W7"} };
	for (int i = 0; i < 9; i++)
		EnQueue(M, MaleName[i]);
	for (int i = 0; i < 7; i++)
		EnQueue(W, FemaleName[i]);
	cout << "男士名单：";
	TraverseQueue(M);
	cout << endl << "女士名单：";
	TraverseQueue(W);
	cout << endl << "开始配对" << endl;
	Dancing(W, M);
	cout << "配对后男士名单：";
	TraverseQueue(M);
	cout << endl << "配对后女士名单：";
	TraverseQueue(W);
	cout << endl;
	return 0;
}