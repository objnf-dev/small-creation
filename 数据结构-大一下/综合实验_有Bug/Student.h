#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

typedef struct {
	char ExamNum[20];
	char Name[20];
	bool Gender;
	unsigned short Age;
	char examtype[10];
} Examinee;

typedef struct Node {
	Examinee data;
	Node* next;
} DataNode;

void MainMenu();
void OutputStudent(Examinee a);
int InitList(DataNode*& H);
void AddStudent(DataNode* H, bool* HeadStatus);
int FindStudent(DataNode* H, int option, char data[], DataNode** item);
int JudgeEqual(const Examinee a, const Examinee b);
void ChangeValue(Examinee* item);
void DeleteStudent(DataNode* H, DataNode* item);
void ListFirstMenu();
void SortStudent(DataNode* H, int option, bool HeadStatus);
