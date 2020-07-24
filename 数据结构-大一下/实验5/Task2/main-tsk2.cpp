#include "BiTree.h"

int nodecount = 0;

int Depth(BTNode* root)
{
	if (root == NULL)
		return 0;
	int dep1 = Depth(root->lchild)+1;
	int dep2 = Depth(root->rchild)+1;
	return dep1 > dep2 ? dep1 : dep2;
}

void LeafNodeCount(BTNode* root)
{
	if (root != NULL)
	{
		LeafNodeCount(root->lchild);
		LeafNodeCount(root->rchild);
		if (root->lchild == NULL && root->rchild == NULL)
			nodecount++;
	}
}

int main()
{
	BTNode* btree;
	TreeInit(btree);
	cout << "二叉树初始化成功" << endl;
	DataType treeData[15] = { 'A','B','#','C','D','#','#','E','#','#','F','#','G','#','#' };
	CreateBTree_Pre(btree, treeData);
	cout << "叶子结点个数为：";
	LeafNodeCount(btree);
	cout << nodecount << endl;
	cout << "深度为：";
	cout << Depth(btree) << endl;
	return 0;
}