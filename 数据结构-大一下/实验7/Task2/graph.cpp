#include "graph.h"
#include <algorithm>

//创建邻接矩阵, g是指向图的指针变量，m[][MAXVEX]是邻接矩阵，d[]是顶点表,n顶点个数
void CreateGraph(AdjMetrix g,int m[][MAXVEX], DataType d[],int n){
  int i,j;
  g->vexs=n;//为图g的顶点个数域赋值
  for(i=0;i<n;i++){//为图g的顶点表赋值
    g->data[i]=d[i];
    for(j=0;j<n;j++)//为图g的邻接矩阵赋值
     g->arcs[i][j]=m[i][j];
  }
}

//显示邻接矩阵
void DispGraph(AdjMetrix g){
   int i,j;
   cout<<"图的顶点：  ";
   for(i=0;i<g->vexs;i++)//输出图g的顶点
      cout<<" "<<g->data[i];
   cout<<"\n\n图的邻接矩阵:"<<endl;
  //外层for循环控制对每一个顶点进行遍历
   for(i=0;i<g->vexs;i++){
      cout<<" "<<g->data[i];//输出顶点i的数据
      for(j=0;j<g->vexs;j++)//在输出顶点i的数据之后，输出顶点i对应在邻接矩阵的第i行的数据
        cout<<" "<<g->arcs[i][j];
      cout<<endl;
   } 
   cout<<endl;
}

//取顶点k第一个邻接点
int GetFirst(AdjMetrix g,int k)
{
   int i;
   if(k<0||k>g->vexs)//顶点表的下标范围在0到g->vexs-1之间，下标即是顶点的序号
	{
	   cout<<"参数k超出范围"<<endl;
	   return -1;
   }
   for(i=0;i<g->vexs;i++)
      if(g->arcs[k][i]==1)//扫描顶点k所在行的元素值，第一个元素值为1的对应的顶点即是顶点k第一个邻接点
		return   i;//返回顶点k第一个邻接点的序号
    return -1;
 
}

//取顶点k的邻接点t的下一个邻接点
int GetNext(AdjMetrix g,int k,int t){
	 int i;
     if(k<0||k>g->vexs||t<0||t>g->vexs)
		{
	      cout<<"参数k或t超出范围"<<endl;
	      return -1;
	 	}
     for(i=t+1;i<g->vexs;i++)
       if(g->arcs[k][i]==1)	
		   return   i;
    return -1;
}

//给顶点k赋值x
void PutVex(AdjMetrix g,int k,DataType x){
  if(k<0||k>g->vexs)  
     {
	      cout<<"参数k超出范围"<<endl;
	      return ;
	 	}
   g->data[k]=x;
}

//取顶点k的值
DataType  GetVex(AdjMetrix g,int k){
  if(k<0||k>g->vexs)  
     {
	      cout<<"参数k超出范围"<<endl;
	      return -1;
	 	}
  return  g->data[k];
}


//连通图深度优先遍历
void DFS(AdjMetrix g,int k,int visited[]){
  int u;
  cout<<" "<<g->data[k];
  visited[k]=1;
  u=GetFirst(g,k);
  while(u!=-1)
  {
    if(visited[u]==0)
      DFS(g,u,visited);
    u=GetNext(g,k,u);
  }
}
