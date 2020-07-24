#include "listinarray.h"

int main(void)
{

	LIST my_List1;//定义线标表LIST类型的变量
	DataType Array[]={{"9787302257646", "程序设计基础", 25.00}, {"9787302164340", "程序设计基础（第2版）", 20.00},  \
	{"9787811234923", "汇编语言程序设计教程", 21.00}, {"9787810827430", "工业计算机控制技术——原理与应用", 29.00}, \
	{"9787302219972", "单片机技术及应用", 32.00}};

	//初始化线性表
	InitList(my_List1);

	//向线性表的指定位置插入数据
	for (int i=0; i<5; i++)
		ListInsert(my_List1,1,Array[i]);

	//输出线性表元素
	DataType book3;
	GetElem(my_List1, 3, &book3);
	cout<<"书名："<<book3.bookName<<"  书号："<<book3.bookNumber<<"  价格："<<book3.bookPrice<<endl;
	
	return 0;
}