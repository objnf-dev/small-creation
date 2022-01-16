#include <iostream>
using namespace std;

typedef char DataType;

typedef struct Node{		
	DataType	data;    //数据域	
	struct Node *lchild;
	struct Node *rchild; //结点的左右子树指针	
}BTNode;//二叉树结点类型

//初始化空二叉树
void TreeInit(BTNode* &root);

//按照前序遍历序列建立二叉树
void CreateBTree_Pre(BTNode  *&root, DataType Array[]);

//释放二叉树中所有结点
void ClearBTree(BTNode* &root);

void TraverseTree_Pre(BTNode* &root, DataType ResArray[]);

void TraverseTree_Mid(BTNode* &root, DataType ResArray[]);

void TraverseTree_Post(BTNode* &root, DataType ResArray[]);