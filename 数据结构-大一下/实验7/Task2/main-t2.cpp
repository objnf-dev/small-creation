#include "graph.h"
#include <algorithm>

typedef struct node
{
	int dis;
	bool hasChecked;
}Node;

typedef struct
{
	int id;
	int weight;
}Line;

bool comp(const Line a, const Line b)
{
	return a.weight < b.weight;
}

void FindPath(AdjMetrix g, int n, int sp, int ep, Node data[], int* final_dis)
{
	if (sp == ep)
	{
		if (*final_dis == -1 || *final_dis > data[sp].dis)
		{
			*final_dis = data[sp].dis;
			return;
		}
	}
	else if (data[sp].hasChecked == true)
		return;
	Line tmp[50];
	for (int i = 0; i < n; i++)
	{
		tmp[i].id = i;
		tmp[i].weight = MAX;
	}
	for (int i = 0; i < n; i++)
	{
		if (g->arcs[sp][i] != MAX)
		{
			if ((data[i].dis == MAX) || ((g->arcs[sp][i] + data[sp].dis) < data[i].dis))
				data[i].dis = g->arcs[sp][i] + data[sp].dis;
			tmp[i].id = i;
			tmp[i].weight = data[i].dis;
		}
	}
	data[sp].hasChecked = true;
	sort(tmp, tmp + n, comp);
	for (int i = 0; i < n; i++)
	{
		if (tmp[i].weight == MAX)
			break;
		FindPath(g, n, tmp[i].id, ep, data, final_dis);
	}
}

int main()
{
	MGraph Map;

	int n = 5;
	DataType point[5] = { 'a','b','c','d','e' };
	int weightMatrix[5][50] = { {MAX, 7, 10, 12, MAX}, {7, MAX, 14, MAX, MAX}, {10, 14, MAX, 6, 18}, {12, MAX, 6, MAX, 8}, {MAX, MAX, 18, 8, MAX} };

	CreateGraph(&Map, weightMatrix, point, n);

	int startP = 1, endP = 5;
	startP--; endP--;

	Node data[50];
	for (int i = 0; i < n; i++)
	{
		data[i].dis = MAX;
		data[i].hasChecked = false;
	}
	data[startP].dis = 0;

	int final_dis = -1;
	FindPath(&Map, n, startP, endP, data, &final_dis);

	if (final_dis == -1)
		cout << "两点之间无法到达";
	else
		cout << "最短路径为：" << final_dis;

	return 0;
}
