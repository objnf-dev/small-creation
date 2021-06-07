#include "BiTree.h"

int main()
{
	BTNode *btree;
	TreeInit(btree);
	cout << "二叉树初始化成功" << endl;
	DataType treeData[15] = { 'A','B','#','C','D','#','#','E','#','#','F','#','G','#','#' };
	CreateBTree_Pre(btree, treeData);
	DataType TraverseData[16];
	cout << "前序遍历：" << endl;
	TraverseTree_Pre(btree, TraverseData);
	TraverseData[15] = '\0';
	cout << TraverseData << endl;
	cout << "中序遍历：" << endl;
	TraverseTree_Mid(btree, TraverseData);
	cout << TraverseData << endl;
	cout << "后序遍历：" << endl;
	TraverseTree_Post(btree, TraverseData);
	cout << TraverseData << endl;
	return 0;
}