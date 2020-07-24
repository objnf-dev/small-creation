#include "Sort_Alg.h"

int main()
{
	int inputNumber[100] = { 0 }, n = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> inputNumber[i];
	cout << "快速排序过程：(最后一行为最终结果）" << endl;
	QuickSort(inputNumber, 0, n-1, n);
	cout << endl << "堆排序过程：（最后一行为最终结果）" << endl;
	HeapSort_Proc(inputNumber, 0, n - 1, n);
	for (int i = 0; i < n; i++)
		cout << inputNumber[i] << " ";
	cout << endl;
	return 0;
}
