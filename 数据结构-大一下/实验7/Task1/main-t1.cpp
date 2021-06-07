#include "graph.h"

int main()
{
	MGraph Map;
	int n = 5;
	DataType node[5] = { 'a', 'b', 'c', 'd', 'e' };
	int weightMatrix[5][50] = { {0, 1, 0, 1, 1}, {1, 0, 1, 1, 0}, {0, 1, 0, 0, 0}, {1, 1, 0, 0, 1}, {1, 0, 0, 1, 0} };
	CreateGraph(&Map, weightMatrix, node, n);
	int visited[5] = { 0 };
	DFS(&Map, 0, visited);
	return 0;
}
