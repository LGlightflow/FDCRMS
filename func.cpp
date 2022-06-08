#include"stdafx.h"
#include "fdcrms.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//创建链表
struct Node *CreateList()
{
	struct  Node *HeadNode = (struct  Node*)malloc(sizeof(struct Node));
	HeadNode->next = NULL;
	return HeadNode; //返回头结点
}

//创建数据
struct data CreateData(){
    struct data Data;
    int i=0,flag=0;
    //需要简化的输入报错处理
    while(true){
		printf("请输入消费日期年份:\n");
		int r=scanf("%d",&Data.date.year);
		fflush(stdin);
		if(Data.date.year>=1946&&Data.date.year<3000&&r==1){
			printf("请输入消费日期月份:\n");
			r=scanf("%d",&Data.date.month);
			fflush(stdin);
			if(Data.date.month>=1&&Data.date.month<=12&&r==1){
				printf("请输入消费日期日份:\n");
				r=scanf("%d",&Data.date.day);
				fflush(stdin);
				if(r==1&&Data.date.day>=1&&Data.date.day<=31){ //判断闰年并求其对应月内的天数有点麻烦，（emmm有空一定写！）
					break;
				}
			}
		}
		printf("输入有误(可能输入了非法字符或输入超出范围)，请重新输入\n");
	}

    while(true){	
		printf("请输入成员身份（如母亲，儿子）：\n");
		int r=scanf("%s", &Data.ID);
		fflush(stdin);
		flag=0;
		for(i=0;i<25;i++){
			if(Data.ID[i]=='\0'){
				flag=1;
				break;
			}
		}
		if(flag==1&&r==1){
			break;
		}                     
		printf("输入错误(可能输入字符太多)，请重新输入\n");              
	}

	while(true){	
		printf("请输入消费金额：\n");
		int r=scanf("%f", &Data.amount);
		fflush(stdin);
		if(r==1&&Data.amount>=0){
			break;
		}
		printf("输入错误(可能有非法输入)，请重新输入\n");
	}


    while(true){	
		//printf("请输入消费品类：（可输入相应数字：1.食品 2.日用品 3.服装 4.电器 5.水电煤气 6.房贷 7.学费 8.交通费 9.其他）\n");
		printf("请输入消费品类：（可输入：食品 日用品 服装 电器 水电煤气 房贷 学费 交通费 其他）\n");
		int r=scanf("%s", &Data.type);
		fflush(stdin);
		if(r==1&&((strcmp(Data.type,"食品"))==0||(strcmp(Data.type,"日用品"))==0||(strcmp(Data.type,"服装"))==0||(strcmp(Data.type,"电器"))==0||(strcmp(Data.type,"水电煤气"))==0||(strcmp(Data.type,"房贷"))==0||(strcmp(Data.type,"学费"))==0||(strcmp(Data.type,"交通费"))==0||(strcmp(Data.type,"其他"))==0)){
			break;
		}                     
		printf("输入错误,与可输入内容不匹配，请重新输入\n");              
	}

    while(true){	
		printf("请输入支出方式：(可输入内容：微信，支付宝，信用卡，现金，其他)\n");
		int r=scanf("%s", &Data.method);
		fflush(stdin);
		if(r==1&&((strcmp(Data.method,"微信"))==0||(strcmp(Data.method,"支付宝"))==0||(strcmp(Data.method,"信用卡"))==0||(strcmp(Data.method,"现金"))==0||(strcmp(Data.method,"其他"))==0)){
			break;
		}                     
		printf("输入错误，与可输入内容不匹配，请重新输入\n");              
	}

	    while(true){	
		printf("请输入消费场所：(可输入内容：线下，美团，京东，淘宝，其他)\n");
		int r=scanf("%s", &Data.site);
		fflush(stdin);
		if(r==1&&((strcmp(Data.site,"线下"))==0||(strcmp(Data.site,"美团"))==0||(strcmp(Data.site,"京东"))==0||(strcmp(Data.site,"淘宝"))==0||(strcmp(Data.site,"其他"))==0)){
			break;
		}                     
		printf("输入错误，与可输入内容不匹配，请重新输入\n");              
	}

	while(true){	
		printf("请输入商品详情：\n");
		int r=scanf("%s", &Data.detail);
		fflush(stdin);
		flag=0;
		for(i=0;i<50;i++){
			if(Data.detail[i]=='\0'){
				flag=1;
				break;
			}
		}
		if(flag==1&&r==1){
			break;
		}                     
		printf("输入错误(可能输入字符太多)，请重新输入\n");              
	}

	return Data;
}

//创建新结点
struct Node *CreateNode(struct data Data)
{
	struct  Node *NewNode = (struct  Node *)malloc(sizeof(struct  Node ));
	NewNode->data=Data;
	NewNode->next = NULL;
	return NewNode;
}

//把新结点插入链表
struct Node *InsertNode(struct  Node *HeadNode,struct data Data)
{	
	struct Node *NewNode = CreateNode(Data);
	NewNode->next = HeadNode->next;
	HeadNode->next = NewNode;
	return HeadNode;
}


void SearchNode_date(struct Node *HeadNode){
	struct  Node *MatchNode = HeadNode->next; //匹配到的结点
	if (MatchNode == NULL)
	{
		printf("失败，不存在任何数据！\n\n");
		return ;
	}
	else{
		int ys,ms,ds,ye,me,de,date_s,date_e,date_Node,i=0;
		printf("请输入起始年份\n");
		scanf("%d",&ys);
		fflush(stdin);
		printf("请输入起始月份\n");
		scanf("%d",&ms);
		fflush(stdin);
		printf("请输入起始日份\n");
		scanf("%d",&ds);
		printf("请输入截止年份\n");
		scanf("%d",&ye);
		fflush(stdin);
		printf("请输入截止月份\n");
		scanf("%d",&me);
		fflush(stdin);
		printf("请输入截止日份\n");
		scanf("%d",&de);
		fflush(stdin);
		date_s=ds+ms*100+ys*10000;
		date_e=de+me*100+ye*10000;
		date_Node=MatchNode->data.date.day+MatchNode->data.date.month*100+MatchNode->data.date.year*10000;
		while (MatchNode!=NULL){ 
		    if(date_Node>=date_s&&date_Node<=date_e){
				i=i+1;
				printf("消费日期：%d年%d月%d日\n成员身份：%s\n消费金额：%.1f元\n消费品类：%s\n支出方式：%s\n消费场所：%s\n商品详情：%s\n\n\n",MatchNode->data.date.year,MatchNode->data.date.month,MatchNode->data.date.day,MatchNode->data.ID,MatchNode->data.amount,MatchNode->data.type,MatchNode->data.method,MatchNode->data.site,MatchNode->data.detail);
			}
			MatchNode=MatchNode->next;
		}
		printf("共查询到%d条数据\n\n\n",i);
	}
}

void SearchNode_date_ID(struct Node *HeadNode){
	struct  Node *MatchNode = HeadNode->next; //匹配到的结点
	if (MatchNode == NULL)
	{
		printf("失败，不存在任何数据！\n\n");
		return ;
	}
	else{
		int ys,ms,ds,ye,me,de,date_s,date_e,date_Node,i=0;
		char MatchID[25];
		printf("请输入起始年份\n");
		scanf("%d",&ys);
		fflush(stdin);
		printf("请输入起始月份\n");
		scanf("%d",&ms);
		fflush(stdin);
		printf("请输入起始日份\n");
		scanf("%d",&ds);
		printf("请输入截止年份\n");
		scanf("%d",&ye);
		fflush(stdin);
		printf("请输入截止月份\n");
		scanf("%d",&me);
		fflush(stdin);
		printf("请输入截止日份\n");
		scanf("%d",&de);
		fflush(stdin);
		printf("请输入要查询的家庭成员身份\n");
		scanf("%s",&MatchID);
		fflush(stdin);
		date_s=ds+ms*100+ys*10000;//便于比较，试试题目提供给我的思路
		date_e=de+me*100+ye*10000;
		date_Node=MatchNode->data.date.day+MatchNode->data.date.month*100+MatchNode->data.date.year*10000;
		while (MatchNode!=NULL){ 
		    if(date_Node>=date_s&&date_Node<=date_e&&strcmp(MatchID,MatchNode->data.ID)==0){
				i=i+1;
				printf("消费日期：%d年%d月%d日\n成员身份：%s\n消费金额：%.1f元\n消费品类：%s\n支出方式：%s\n消费场所：%s\n商品详情：%s\n\n\n",MatchNode->data.date.year,MatchNode->data.date.month,MatchNode->data.date.day,MatchNode->data.ID,MatchNode->data.amount,MatchNode->data.type,MatchNode->data.method,MatchNode->data.site,MatchNode->data.detail);
			}
			MatchNode=MatchNode->next;
		}
		printf("共查询到%d条数据\n\n\n",i);
	}
}

void SearchNode_date_type(struct Node *HeadNode){
	struct  Node *MatchNode = HeadNode->next; //匹配到的结点
	if (MatchNode->next == NULL)
	{
		printf("失败，不存在任何数据！\n\n");
		return ;
	}
	else{
		int ys,ms,ds,ye,me,de,date_s,date_e,date_Node,i=0;
		char MatchType[25];
		printf("请输入起始年份\n");
		scanf("%d",&ys);
		fflush(stdin);
		printf("请输入起始月份\n");
		scanf("%d",&ms);
		fflush(stdin);
		printf("请输入起始日份\n");
		scanf("%d",&ds);
		printf("请输入截止年份\n");
		scanf("%d",&ye);
		fflush(stdin);
		printf("请输入截止月份\n");
		scanf("%d",&me);
		fflush(stdin);
		printf("请输入截止日份\n");
		scanf("%d",&de);
		fflush(stdin);
		printf("请输入要查询的消费品类\n");
		scanf("%s",&MatchType);
		fflush(stdin);
		date_s=ds+ms*100+ys*10000;
		date_e=de+me*100+ye*10000;
		do{ 
			date_Node=MatchNode->data.date.day+MatchNode->data.date.month*100+MatchNode->data.date.year*10000;
		    if(date_Node>=date_s&&date_Node<=date_e&&strcmp(MatchType,MatchNode->data.type)==0){
				i=i+1;
				printf("消费日期：%d年%d月%d日\n成员身份：%s\n消费金额：%.1f元\n消费品类：%s\n支出方式：%s\n消费场所：%s\n商品详情：%s\n\n\n",MatchNode->data.date.year,MatchNode->data.date.month,MatchNode->data.date.day,MatchNode->data.ID,MatchNode->data.amount,MatchNode->data.type,MatchNode->data.method,MatchNode->data.site,MatchNode->data.detail);
			}
			MatchNode=MatchNode->next;	
		}while (MatchNode!=NULL);
		printf("共查询到%d条数据\n\n\n",i);
	}
}

void SearchNode_amount(struct Node *HeadNode){
	struct  Node *MatchNode = HeadNode->next; //匹配到的结点
	if (MatchNode->next == NULL)
	{
		printf("失败，不存在任何数据！\n\n");
		return ;
	}
	else{
		int i=0;
		float MatchAmount;
		printf("请输入要查询的消费金额（至少精确到个位）\n");
		scanf("%f",&MatchAmount);
		fflush(stdin);
		while (MatchNode!=NULL){ 
		    if(MatchAmount==MatchNode->data.amount){
				i=i+1;
				printf("消费日期：%d年%d月%d日\n成员身份：%s\n消费金额：%.1f元\n消费品类：%s\n支出方式：%s\n消费场所：%s\n商品详情：%s\n\n\n",MatchNode->data.date.year,MatchNode->data.date.month,MatchNode->data.date.day,MatchNode->data.ID,MatchNode->data.amount,MatchNode->data.type,MatchNode->data.method,MatchNode->data.site,MatchNode->data.detail);
			}
			MatchNode=MatchNode->next;
		}
		printf("共查询到%d条数据\n\n\n",i);
	}
}



void ChangeNode(struct Node *HeadNode){
	struct Node *ChgNode=HeadNode->next;
	if(HeadNode->next==NULL){
		printf("修改失败，文件中不存在可以修改的数据\n\n\n");
		return;
	}
	else{
		char ChgID[25];
		printf("请输入要修改信息中的家庭成员身份\n");
		scanf("%s",&ChgID);
		fflush(stdin);
		int Chgy,Chgm,Chgd;
		printf("请输入要修改信息中的年份\n");
		scanf("%d",&Chgy);
		fflush(stdin);
		printf("请输入要修改信息中的月份\n");
		scanf("%d",&Chgm);
		fflush(stdin);
		printf("请输入要修改信息中的日份\n");
		scanf("%d",&Chgd);
		fflush(stdin);
		char Chgtype[10];
		printf("请输入要修改信息中的消费品类\n");
		scanf("%s",&Chgtype);
		fflush(stdin);
		int ChgDate=0,Date=0;
		ChgDate=Chgd+Chgm*100+Chgy*10000;
		Date=ChgNode->data.date.day+ChgNode->data.date.month*100+ChgNode->data.date.year*10000;
		while(ChgNode!=NULL){
			if(strcmp(Chgtype,ChgNode->data.type)==0&&strcmp(ChgID,ChgNode->data.ID)==0&&ChgDate==Date){
				ChangeNodemenu(ChgNode);
				printf("修改成功！\n\n");
				break; 
			}
			ChgNode=ChgNode->next;
		}
		if (ChgNode == NULL)
			{
				printf("\n未找到相应的数据，是否重新进行操作？(y继续，n或其他输入退出)\n");
				char judge=getchar();
				fflush(stdin);
				printf("\n\n");
				if (judge == 'y')
				{	
					ChangeNode(HeadNode);
				}
				else
				{
					return ;
				}
			}
	}
}


//遍历链表
void PrintList(struct  Node *HeadNode)
{
	struct  Node *PtMove = HeadNode->next;
	if(HeadNode->next==NULL||PtMove==NULL){
		printf("没有找到任何数据！\n\n");
		return;
	}
	printf(" ___________________________________________________________________________________ \n");
	printf("|消费日期      |身份      |金额(元) |消费品类|支出方式|消费场所|商品详情            |\n");
	while (PtMove!=NULL)
	{	
		//printf("消费日期：%d年%d月%d日\n成员身份：%s\n消费金额：%.1f元\n消费品类：%s\n支出方式：%s\n消费场所：%s\n商品详情：%s\n\n\n",PtMove->data.date.year,PtMove->data.date.month,PtMove->data.date.day,PtMove->data.ID,PtMove->data.amount,PtMove->data.type,PtMove->data.method,PtMove->data.site,PtMove->data.detail);
		printf("|______________|__________|_________|________|________|________|____________________|\n");
		printf("|%-4d年%-2d月%-2d日|%-10s|%-9.1f|%-8s|%-8s|%-8s|%-20s|",PtMove->data.date.year,PtMove->data.date.month,PtMove->data.date.day,PtMove->data.ID,PtMove->data.amount,PtMove->data.type,PtMove->data.method,PtMove->data.site,PtMove->data.detail);
		printf("\n");
		PtMove = PtMove->next;
	}
	printf("|______________|__________|_________|________|________|________|____________________|\n");
	printf("\n\n");
}


void SumAmount(struct Node *HeadNode,int choice){ //传入菜单中输入的值
	struct  Node *PtMove = HeadNode->next; //匹配到的结点
	if(choice==34)
		return;
	if (PtMove == NULL)
	{
		printf("失败，不存在任何数据！\n\n");
		return ;
	}
	else{
		if (choice!=31&&choice!=32&&choice!=33){
			printf("没有输入相应数字，请重新输入\n\n");
			return;
		}
		
		int ys,ms,ds,ye,me,de,date_s,date_e,date_Node;
		float sum=0;
		printf("请输入起始年份\n");
		scanf("%d",&ys);
		fflush(stdin);
		printf("请输入起始月份\n");
		scanf("%d",&ms);
		fflush(stdin);
		printf("请输入起始日份\n");
		scanf("%d",&ds);
		printf("请输入截止年份\n");
		scanf("%d",&ye);
		fflush(stdin);
		printf("请输入截止月份\n");
		scanf("%d",&me);
		fflush(stdin);
		printf("请输入截止日份\n");
		scanf("%d",&de);
		fflush(stdin);
		date_s=ds+ms*100+ys*10000;
		date_e=de+me*100+ye*10000;
		switch (choice)
		{
		case 31:{
			do{ 
				date_Node=PtMove->data.date.day+PtMove->data.date.month*100+PtMove->data.date.year*10000;
				if(date_Node>=date_s&&date_Node<=date_e){
					sum=sum+PtMove->data.amount;
				}
				PtMove=PtMove->next;
			}while (PtMove!=NULL);
			printf("%d年%d月%d日到%d年%d月%d日的消费总额:%.1f元\n\n\n",ys,ms,ds,ye,me,de,sum);
			break;
		}

		case 32:{
			char SumID[25];
			printf("请输入要统计总额的家庭成员\n");
			scanf("%s",&SumID);
			fflush(stdin);
			date_s=ds+ms*100+ys*10000;
			date_e=de+me*100+ye*10000;
			do{ 
				date_Node=PtMove->data.date.day+PtMove->data.date.month*100+PtMove->data.date.year*10000;
				if(date_Node>=date_s&&date_Node<=date_e&&strcmp(SumID,PtMove->data.ID)==0){
					sum=sum+PtMove->data.amount;
				}
				PtMove=PtMove->next;
			}while (PtMove!=NULL);
			printf("\"%s\"在%d年%d月%d日到%d年%d月%d日的消费总额:%.1f元\n\n\n",SumID,ys,ms,ds,ye,me,de,sum);
			break;
		}

		case 33:{
			char SumType[10];
			printf("请输入要统计的消费品类\n");
			scanf("%s",&SumType);
			fflush(stdin);
			do{ 
				date_Node=PtMove->data.date.day+PtMove->data.date.month*100+PtMove->data.date.year*10000;
		    	if(date_Node>=date_s&&date_Node<=date_e&&strcmp(SumType,PtMove->data.type)==0){
					sum=sum+PtMove->data.amount;
				}
				PtMove=PtMove->next;
			}while (PtMove!=NULL);
			printf("\"%s\"品类在%d年%d月%d日到%d年%d月%d日的消费总额:%.1f元\n\n\n",SumType,ys,ms,ds,ye,me,de,sum);
			break;
		}

		default:
			printf("没有输入相应数字，请重新输入\n\n");
			break;
		}
	}
}

struct Node* SortList_Date(struct Node *HeadNode) {
	struct Node *PtMove1 = HeadNode->next;
	struct Node *PtMove2 = PtMove1;
	struct Node *PtMove_Min = PtMove1;
	while (PtMove1 != NULL) {
		PtMove_Min = PtMove1;
		PtMove2 = PtMove1->next;
		while (PtMove2 != NULL) {
			int date_min = PtMove_Min->data.date.day + PtMove_Min->data.date.month * 100 + PtMove_Min->data.date.year * 10000;
			int date_2 = PtMove2->data.date.day + PtMove2->data.date.month * 100 + PtMove2->data.date.year * 10000;
			if (date_2 > date_min)
				PtMove_Min = PtMove2;
			PtMove2 = PtMove2->next;
		}
		if (PtMove_Min != PtMove1) {
			struct data temp = PtMove_Min->data;
			PtMove_Min->data = PtMove1->data;
			PtMove1->data = temp;
		}
		PtMove1 = PtMove1->next;
	}
	return HeadNode;
}


struct Node* SortList_Amount(struct Node *HeadNode) {
	struct Node *PtMove1 = HeadNode->next;
	struct Node *PtMove2 = PtMove1;
	struct Node *PtMove_Min = PtMove1;
	while (PtMove1 != NULL) {
		PtMove_Min = PtMove1;
		PtMove2 = PtMove1->next;
		while (PtMove2 != NULL) {
			if (PtMove2->data.amount > PtMove_Min->data.amount) {
				PtMove_Min = PtMove2;
			}
			PtMove2 = PtMove2->next;
		}
		if (PtMove_Min != PtMove1) {
			struct data temp = PtMove_Min->data;
			PtMove_Min->data = PtMove1->data;
			PtMove1->data = temp;

		}
		PtMove1 = PtMove1->next;
	}
	return HeadNode;
}


void SortList(struct Node *HeadNode,int choice){
	struct Node *PtMove1=HeadNode->next;
	struct Node *PtMove2=PtMove1;
	struct Node *PtMove_Min=PtMove1;
	if(choice==23)
		return;
	
	if(choice!=21&&choice!=22){
		printf("没有输入对应数字，请重新输入\n\n");
	}

	if(HeadNode->next==NULL){
		printf("不存在任何数据\n\n\n");
		return;
	}

	switch (choice)
	{
	case 21://日期
		while(PtMove1!=NULL){//这里选择排序的做法是直接交换数据域，原来是把最小值结点从链表断开再用头插法
		PtMove_Min=PtMove1;
		PtMove2=PtMove1->next;
		while(PtMove2!=NULL){
			int date_min=PtMove_Min->data.date.day+PtMove_Min->data.date.month*100+PtMove_Min->data.date.year*10000;
			int date_2=PtMove2->data.date.day+PtMove2->data.date.month*100+PtMove2->data.date.year*10000;
			if(date_2 < date_min)
				PtMove_Min=PtMove2;
			PtMove2=PtMove2->next;
		}
		if(PtMove_Min!=PtMove1){
			struct data temp=PtMove_Min->data;
			PtMove_Min->data=PtMove1->data;
			PtMove1->data=temp;
			}
		PtMove1=PtMove1->next;
	}
		printf("排序完成\n\n");
		break;
	
	case 22://金额
		while(PtMove1!=NULL){
		PtMove_Min=PtMove1;
		PtMove2=PtMove1->next;
		while(PtMove2!=NULL){
			if(PtMove2->data.amount < PtMove_Min->data.amount){
				PtMove_Min=PtMove2;
			}
			PtMove2=PtMove2->next;
		}
		if(PtMove_Min!=PtMove1){
			struct data temp=PtMove_Min->data;
			PtMove_Min->data=PtMove1->data;
			PtMove1->data=temp;

			}
		PtMove1=PtMove1->next;
	}
		printf("排序完成\n\n");
		break;

	case 23:
		printf("准备返回......\n\n");
		break;

	default:
		printf("没有输入相应数字，请重新输入\n\n");
		break;
	}
	
	PrintList(HeadNode);
	ReverseList(HeadNode);
}


struct Node* ReverseList(struct Node *HeadNode){
	
	if(HeadNode->next==NULL){
		printf("不存在任何数据\n\n\n");
		return HeadNode;
	}
	//h->1->2->3->4
	struct Node* PtMove_Front=HeadNode->next;//ptfront 1
	struct Node* PtMove=HeadNode->next->next;//pt 2
	HeadNode->next->next=NULL;//让头指针的下一个结点（1）指向空（后面的结点依次插入头结点和头结点的下一个结点的中间）
	while(PtMove!=NULL){
		PtMove_Front=PtMove;
		PtMove=PtMove->next;
		PtMove_Front->next=HeadNode->next;
		HeadNode->next=PtMove_Front;
	}

	return HeadNode;
}

//保存链表
void WriteList(struct Node *HeadNode,char path[]){
	struct Node *PtMove=HeadNode->next;
	FILE *fp=NULL;
	
	if(PtMove==NULL){
		//printf("保存失败，没有任何数据可以保存！\n\n");
		//return; //暂时允许保存空数据
	}
	if((fp=fopen(path,"r"))==NULL){
		//printf("数据文件不存在，即将创建...\n");
	}
	fp=fopen(path,"wb");
	if(fp==NULL){
		//printf("创建文件数据失败！请检查权限！\n\n");
		return;
	}

	while(PtMove!=NULL){
		fwrite(&PtMove->data,sizeof(struct data),1,fp);
		PtMove=PtMove->next;
	}
	//printf("保存数据成功！\n\n");
	fclose(fp);
}





//读取链表
struct Node* ReadList(struct Node *HeadNode,char path[]){

	//printf("准备读取数据...\n");
	FILE *fp=NULL;
	struct data data;
	if((fp=fopen(path,"r"))==NULL){
		//printf("数据文件不存在，读取失败.\n即将创建新数据文件...\n\n");
		fp=fopen(path,"w+b");
		//printf("创建文件成功！\n\n\n");
		fclose(fp);//测试
		return NULL; //测试
	}

	fp=fopen(path,"rb");
	while(fread(&data,sizeof(struct data),1,fp)!=0){    //fread()：成功读取的数据总数会以(struct data)的整型数据返回
		if(ferror(fp)){                                                                   //如果返回的值不为0，说明读取异常或已读到文件末尾,==0就读取完了
			//printf("读取文件时发生错误\n\n");
			fclose(fp);
			return NULL;
		}
		InsertNode(HeadNode,data);	
	}
	printf("读取数据成功！\n\n\n");
	fclose(fp);

	return HeadNode;
}

void FreeList(struct Node* HeadNode) {
	
	while (HeadNode != NULL) {
		struct Node *p = HeadNode;
		HeadNode=p->next;
		free(p);
	}
}


//没有投入使用的函数
int NumList(struct Node *HeadNode){
	int n=0;
	HeadNode=HeadNode->next;
	while(HeadNode!=NULL){
		n=n+1;
		HeadNode=HeadNode->next;
	}
	return n;
}
