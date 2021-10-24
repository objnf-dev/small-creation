#include "Sort_Alg.h"

void QuickSort(int array[], int start, int last, int len)
{
	int low = start;
	int high = last;
	int tmp = array[low];
	if (low < high)
	{
		while (low < high)
		{
			while (low < high && array[high] >= tmp)
				high--;
			if (low < high)
			{
				array[low] = array[high];
				low++;
			}
			while (low < high && tmp > array[low])
				low++;
			if (low < high)
			{
				array[high] = array[low];
				high--;
			}
		}
		array[low] = tmp;
		for (int i = 0; i < len; i++)
			cout << array[i] << " ";
		cout << endl;
		QuickSort(array, start, low - 1, len);
		QuickSort(array, low + 1, last, len);
	}
}

void HeapSort(int data[], int start, int end, int len)
{
	if (start == end)
		return;
	if (end % 2 == 0)
	{
		int* comp = NULL;
		if (data[end - 1] > data[end])
			comp = &data[end - 1];
		else
			comp = &data[end];
		if (*comp > data[end / 2 - 1])
		{
			int tmp = data[end / 2 - 1];
			data[end / 2 - 1] = *comp;
			*comp = tmp;
		}
	}
	else
	{
		if (data[end] > data[end / 2])
		{
			int tmp = data[end / 2];
			data[end / 2] = data[end];
			data[end] = tmp;
		}
	}
	for (int i = 0; i < len; i++)
		cout << data[i] << " ";
	cout << endl;
	if (end % 2 == 0 && (end / 2 - 1) % 2 == 0)
		HeapSort(data, start, end / 2 - 1, len);
	else if (end % 2 == 0 && (end / 2 - 1) % 2 == 1)
		HeapSort(data, start, end / 2, len);
	else if (end % 2 == 1 && (end / 2) % 2 == 0)
		HeapSort(data, start, end / 2, len);
	else if (end % 2 == 1 && (end / 2) % 2 == 1)
		HeapSort(data, start, end / 2 + 1, len);
}

void HeapSort_Proc(int data[], int start, int end, int len)
{
	while (start != end)
	{
		HeapSort(data, start, end, len);
		int tmp = data[start];
		data[start] = data[end];
		data[end] = tmp;
		end--;
	}
}
