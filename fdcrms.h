#pragma once
#ifndef _FDCRMS_H
#define _FDCRMS_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "locale.h"


//数据域

struct date {
	int year;
	int month;
	int day;
};

struct data {
	struct date date;
	char ID[25];//成员身份mother son
	float amount;//消费金额
	char type[10];//消费品类
	char method[10];//支出方式
	char site[10];//消费场所
	char detail[50];//商品详情
};



//链表
struct Node {
	struct data data;
	struct Node *next;
};

struct Node *CreateList(); //创建链表，返回链表头指针
struct data CreateData();//创建数据供创建结点
struct Node *CreateNode(struct data Data);//创建结点
struct Node *InsertNode(struct  Node *HeadNode, struct data Data);//将结点插入链表 头插
void SearchNode_date(struct Node *HeadNode);
void SearchNode_date_ID(struct Node *HeadNode);
void SearchNode_date_type(struct Node *HeadNode);
void SearchNode_amount(struct Node *HeadNode);//
//void DeleteNode(struct Node *HeadNode);
void PrintList(struct  Node *HeadNode);
void SumAmount(struct Node *HeadNode, int choice);
void SortList(struct Node *HeadNode, int choice);
struct Node* SortList_Amount(struct Node *HeadNode);
struct Node* SortList_Date(struct Node *HeadNode);
struct Node* ReverseList(struct Node *HeadNode);
void ChangeNode(struct Node *HeadNode);
void WriteList(struct Node *HeadNode, char path[]);
struct Node* ReadList(struct Node *HeadNode, char path[]);
void FreeList(struct Node* HeadNode);


void mainmenu();
void statisticmenu(struct Node *HeadNode);
void sortmenu(struct Node *HeadNode);
void searchmenu(struct Node *HeadNode);
void ChangeNodemenu(struct Node *ChgNode);

#endif