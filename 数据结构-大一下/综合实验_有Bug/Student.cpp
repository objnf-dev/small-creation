#include "Student.h"

void MainMenu()
{
	printf("########## 考试报名管理系统 v1.0 ##########\n");
	printf("                          18271241 ***\n");
	printf("           1. 添加考生信息\n");
	printf("           2. 查询考生信息\n");
	printf("           3. 输出全部考生信息\n");
	printf("           4. 退出程序\n");
	printf("#########################################\n\n\n");
	printf("请输入操作符：");
}

void OutputStudent(Examinee a)
{
	printf("\n学生详情：\n");
	printf("姓名：%s\n", a.Name);
	printf("考号：%s\n", a.ExamNum);
	printf("性别：");
	if (a.Gender == false)
		printf("男\n");
	else
		printf("女\n");
	printf("年龄：%d\n", (int)a.Age);
	printf("考试科目：%s\n", a.examtype);
}

int InitList(DataNode*& H)
{
	H = new DataNode;
	if (!H)
	{
		cout << "初始化错误" << endl;
		return 0;
	}
	H->next = NULL;
	return 1;
}

void AddStudent(DataNode* H, bool* HeadStatus)
{
	system("cls");
	DataNode* p = H;
	while (p->next != NULL)
		p = p->next;
	DataNode* t = new DataNode;
	system("cls");
	printf("请输入学号：");
	scanf("%s", t->data.ExamNum);
	printf("请输入姓名（英文）：");
	scanf("%s", t->data.Name);
	printf("请输入性别（0为男，1为女）：");
	int tmp = 0;
	scanf("%d", &tmp);
	if (tmp == 1)
		t->data.Gender = true;
	else
		t->data.Gender = false;
	printf("请输入年龄：");
	scanf("%hu", &t->data.Age);
	printf("请输入考试科目：");
	scanf("%s", t->data.examtype);
	t->next = NULL;
	if (*HeadStatus == false)
	{
		*H = *t;
		*HeadStatus = true;
	}
	else
		p->next = t;
	printf("添加学生信息成功！\n\n");
	system("pause");
}

int FindStudent(DataNode* H, int option, char data[], DataNode **item)
{
	DataNode* p = H;
	if (option == 1)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.Name, data) == 0)
			{
				*item = p;
				return 1;
			}
			p = p->next;
		}
		printf("\n未找到该学生！");
		system("pause");
		return 0;
	}
	else if (option == 2)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.ExamNum, data) == 0)
			{
				*item = p;
				return 1;
			}
			p = p->next;
		}
		printf("\n未找到该学生！");
		system("pause");
		return 0;
	}
	return 0;
}

void ChangeValue(Examinee* item)
{
	while (true)
	{
		printf("请选择你要修改的数据：\n");
		printf("【1】姓名    【2】学号    【3】年龄    【4】性别\n");
		printf("【5】考试科目\n请输入操作符：");
		int opt = 0;
		if (scanf("%d", &opt) != 1 || opt < 1 || opt > 5)
		{
			printf("操作符错误！\n");
			system("pause");
			continue;
		}
		printf("请输入修改后的数据：");
		if (opt == 1)
		{
			char tmp[20];
			scanf("%s", tmp);
			strcpy(item->Name, tmp);
		}
		else if (opt == 2)
		{
			char tmp[20];
			scanf("%s", tmp);
			strcpy(item->ExamNum, tmp);
		}
		else if (opt == 3)
		{
			int tmp = 0;
			scanf("%d", &tmp);
			item->Age = (unsigned short)tmp;
		}
		else if (opt == 4)
		{
			int tmp = 0;
			printf("\n（0为男生，1为女生）\n");
			scanf("%d", &tmp);
			if (tmp == 0)
				item->Gender = false;
			else
				item->Gender = true;
		}
		else if (opt == 5)
		{
			char tmp[10];
			scanf("%s", tmp);
			strcpy(item->examtype, tmp);
		}
		printf("数据修改完成！\n");
		system("pause");
		break;
	}
}

int JudgeEqual(const Examinee a, const Examinee b)
{
	if (a.Age == b.Age && a.Gender == b.Gender && strcmp(a.ExamNum, a.ExamNum) == 0 && strcmp(a.examtype, b.examtype) == 0 && strcmp(a.Name, b.Name) == 0)
		return 1;
	else
		return 0;
}

/*
 * 注意：程序存在问题。
 * 该部分函数未能处理当p为头节点时的删除情况。
 * 删除头结点处的数据会导致野指针。
 * 由于作业的时间问题（不到半天写完这些）没有改，请使用者使用前改掉。
 */

void DeleteStudent(DataNode* H, DataNode* item)
{
	DataNode* p = H;
	while (p != NULL)
	{
		if (JudgeEqual(p->next->data, item->data))
		{
			if (p->next == NULL)
				item->next = NULL;
			else
				p->next = item->next;
			delete item;
			printf("删除成功！\n");
			system("pause");
			return;
		}
		p = p->next;
	}
}

void ListFirstMenu()
{
	system("cls");
	printf("请选择排序方式：\n");
	printf("【1】按照学号进行排序    【2】按照姓名进行排序\n");
	printf("请输入操作符：");
}

void SortStudent(DataNode* H, int option, bool HeadStatus)
{
	if (option == 1)
	{
		struct comp {
			bool operator()(const Examinee &x, const Examinee &y)
			{
				int tmp = strcmp(x.ExamNum, y.ExamNum);
				if (tmp <= 0)
					return false;
				else
					return true;
			}
		};
		priority_queue<Examinee, vector<Examinee>, comp> pq;
		DataNode* p = H;
		while (p != NULL)
		{
			if (HeadStatus == false)
				break;
			pq.push(p->data);
			p = p->next;
		}
		int i = 1;
		while (!pq.empty())
		{
			Examinee tmp = pq.top();
			pq.pop();
			printf("#########%d#########\n", i);
			OutputStudent(tmp);
			printf("####################\n");
			i++;
		}
		system("pause");
	}
	else if (option == 2)
	{
		struct comp {
			bool operator()(Examinee x, Examinee y)
			{
				int tmp = strcmp(x.Name, y.Name);
				if (tmp <= 0)
					return false;
				else
					return true;
			}
		};
		priority_queue<Examinee, vector<Examinee>, comp> pq;
		DataNode* p = H;
		while (p != NULL)
		{
			if (HeadStatus == false)
				break;
			pq.push(p->data);
			p = p->next;
		}
		int i = 1;
		while (!pq.empty())
		{
			Examinee tmp = pq.top();
			pq.pop();
			printf("#########%d#########\n", i);
			OutputStudent(tmp);
			printf("####################\n");
			i++;
		}
		system("pause");
	}
}
