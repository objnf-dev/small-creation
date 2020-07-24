#include "BiTree.h"

//初始化空二叉树
void TreeInit(BTNode* &root)
{
	root=NULL;
}

//按照前序遍历序列建立二叉树
void CreateBTree_Pre(BTNode  *&root, DataType Array[]) 
{ 
	static int count=0;	//静态变量count
    char item=Array[count];//读取Array[]数组中的第count个元素
	count++;
	if(item == '#') //如果读入#字符，创建空树
	{ root = NULL; return ;}
    else
	{
		root = new BTNode;
        root->data = item;
	    CreateBTree_Pre (root->lchild,Array);    //建左子树 
	    CreateBTree_Pre (root->rchild,Array); //建右子树 
 	 }
}

//释放二叉树中所有结点
void ClearBTree(BTNode* &root)
{
    if(root!=NULL)
    {
        ClearBTree( root->lchild );
        ClearBTree( root->rchild );
        delete root;
        root=NULL;
    }
}