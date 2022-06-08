#include"stdafx.h"
#include"fdcrms.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


void mainmenu(){
    char path[250]="";
    //printf("请输入保存数据的路径(例：D:/abc/ )：");
	//scanf("%s",path);
    strcat(path,"fee.dat");
    struct Node *List=CreateList();
    ReadList(List,path);
    int n;
    do{   
        printf("**************************************************************************\n");
        printf("                         请输入数字来执行对应操作                           \n");
        printf("1----查询 2----排序 3----统计 4----录入 5----更新(修改) 6----退出  \n");
        printf("**************************************************************************\n");
        scanf("%d",&n);
        fflush(stdin);
        switch (n){

            case 1:
                searchmenu(List);
                break;

            case 2:
                sortmenu(List);
                break;
            
            case 3:
                statisticmenu(List);
                break;

            case 4:{
                char judge;
                do{
                struct data Data =CreateData();
                struct Node *p = InsertNode(List,Data);
                printf("录入成功\n");
                WriteList(List,path);
                printf("输入y继续录入（键入其他退出）");
                scanf("%c",&judge);
                fflush(stdin);
                }while(judge=='y');
                break;   
            }

            case 5:
                ChangeNode(List);
                WriteList(List,path);
                break; 
            
            case 6:{
                printf("按y执行自动保存......\n");
                char judge=getchar();
				fflush(stdin);
				if (judge == 'y'){
                    WriteList(List,path);
                    printf("准备退出......\n");	
				}
				else{
					printf("准备退出......\n");
				}
                break;
            }

            default:
                printf("没有输入对应的数字,请重新输入\n");
                break;
            }
        }while(n!=6);
}


void searchmenu(struct Node *HeadNode){
    int n;
    do{
        printf("**************************************************************************\n");
        printf("                         请输入数字来执行对应操作                           \n");
        printf("11----按日期区间段查询              12----按交易金额查询  \n");
        printf("13----按家庭成员加日期区间查询       14----按消费品类加日期区间查询 \n");
        printf("15----查看所有数据                  16----返回上级菜单 \n");
        printf("**************************************************************************\n");
        scanf("%d",&n);
        fflush(stdin);
        switch (n)
        {
            case 11:
                SearchNode_date(HeadNode);
                break;

            case 12:
                SearchNode_amount(HeadNode);
                break;

            case 13:
                SearchNode_date_ID(HeadNode);
                break;

            case 14:
                SearchNode_date_type(HeadNode);
                break;    
            
            case 15:
                PrintList(HeadNode);
                break;

            case 16:
                printf("准备返回......\n\n");
                break;

            default:
                printf("没有输入对应的数字,请重新输入\n");
                break;
        }
    }while(n!=16);
}


void statisticmenu(struct Node *HeadNode){
    int n;
    do{
        printf("**************************************************************************\n");
        printf("                         请输入数字来执行对应操作                           \n");
        printf("31----给定时间段家庭消费总额统计        32----特定成员在给定时间段消费总额统计   \n");
        printf("33----特定品类在给定时间段消费总额统计     34----返回上级菜单\n");
        printf("**************************************************************************\n");
        scanf("%d",&n);
        fflush(stdin);
        SumAmount(HeadNode,n);
    }while(n!=34);
    printf("准备返回......\n\n");
}

void sortmenu(struct Node *HeadNode){
    int n;
    do{
        printf("**************************************************************************\n");
        printf("                         请输入数字来执行对应操作                           \n");
        printf("21----按照消费日期升序排序        22----按照消费金额升序排序   \n");
        printf("23----返回上级菜单\n");
        printf("**************************************************************************\n");
        scanf("%d",&n);
        fflush(stdin);
        SortList(HeadNode,n);
    }while(n!=23);
    printf("准备返回......\n\n");
}

void ChangeNodemenu(struct Node *ChgNode){
    int n,i=0,flag=0;
    do{
        printf("**************************************************************************\n");
        printf("                         请输入数字来执行对应操作                           \n");
        printf("51----修改成员身份          52----修改消费金额          53----修改消费品类   \n");
        printf("54----修改支出方式          55----修改消费场所          56----修改商品详情   \n");
        printf("57----修改消费日期          58----返回上级菜单                              \n");
        printf("**************************************************************************\n");
        scanf("%d",&n);
        fflush(stdin);
        switch (n)
        {
        case 51:
            while(true){	
                printf("请输入修改后的成员身份：\n");
                int r=scanf("%s", &ChgNode->data.ID);
                fflush(stdin);
                flag=0;
                for(i=0;i<25;i++){
                if(ChgNode->data.ID[i]=='\0'){
                    flag=1;
                    break;
                }
                }if(flag==1&&r==1){
                    break;
                }                     
		        printf("输入错误(可能输入字符太多)，请重新输入\n");              
	        }
            break;
        
        case 52:
        	while(true){	
                printf("请输入修改后的消费金额：\n");
                int r=scanf("%f", &ChgNode->data.amount);
                fflush(stdin);
                if(r==1&&ChgNode->data.amount>=0){
                    break;
                }
		        printf("输入错误(可能有非法输入)，请重新输入\n");
	        }
            break;

        case 53:
            while(true){	
                printf("请输入修改后的消费品类：（可输入：食品 日用品 服装 电器 水电煤气 房贷 学费 交通费 其他）\n");
                int r=scanf("%s", &ChgNode->data.type);
                fflush(stdin);
                if(r==1&&((strcmp(ChgNode->data.type,"食品"))==0||(strcmp(ChgNode->data.type,"日用品"))==0||(strcmp(ChgNode->data.type,"服装"))==0||(strcmp(ChgNode->data.type,"电器"))==0||(strcmp(ChgNode->data.type,"水电煤气"))==0||(strcmp(ChgNode->data.type,"房贷"))==0||(strcmp(ChgNode->data.type,"学费"))==0||(strcmp(ChgNode->data.type,"交通费"))==0||(strcmp(ChgNode->data.type,"其他"))==0)){
                    break;
                }                     
                printf("输入错误,与可输入内容不匹配，请重新输入\n");              
            }
            break;

        case 54:
            while(true){	
                printf("请输入修改后的支出方式：(可输入内容：微信，支付宝，信用卡，现金，其他)\n");
                int r=scanf("%s", &ChgNode->data.method);
                fflush(stdin);
                if(r==1&&((strcmp(ChgNode->data.method,"微信"))==0||(strcmp(ChgNode->data.method,"支付宝"))==0||(strcmp(ChgNode->data.method,"信用卡"))==0||(strcmp(ChgNode->data.method,"现金"))==0||(strcmp(ChgNode->data.method,"其他"))==0)){
                    break;
                }                       
		        printf("输入错误，与可输入内容不匹配，请重新输入\n");              
	        }
            break;
        case 55:
            while(true){	
                printf("请输入消费场所：(可输入内容：线下，美团，京东，淘宝，其他)\n");
                int r=scanf("%s", &ChgNode->data.site);
                fflush(stdin);
                if(r==1&&((strcmp(ChgNode->data.site,"线下"))==0||(strcmp(ChgNode->data.site,"美团"))==0||(strcmp(ChgNode->data.site,"京东"))==0||(strcmp(ChgNode->data.site,"淘宝"))==0||(strcmp(ChgNode->data.site,"其他"))==0)){
                    break;
                }                     
                printf("输入错误，与可输入内容不匹配，请重新输入\n");              
	        }
            break;

        case 56:
            while(true){	
                printf("请输入商品详情：\n");
                int r=scanf("%s", &ChgNode->data.detail);
                fflush(stdin);
                flag=0;
                for(i=0;i<50;i++){
                    if(ChgNode->data.detail[i]=='\0'){
                        flag=1;
                        break;
                    }
                }
		        if(flag==1&&r==1){
			        break;
		        }                     
		        printf("输入错误(可能输入字符太多)，请重新输入\n");              
	        }
            break;

        case 57:
                while(true){
                    printf("请输入修改后的消费日期年份:\n");
                    int r=scanf("%d",&ChgNode->data.date.year);
                    fflush(stdin);
                    if(ChgNode->data.date.year>=1946&&ChgNode->data.date.year<3000&&r==1){
                        printf("请输入修改后的消费日期月份:\n");
                        r=scanf("%d",&ChgNode->data.date.month);
                        fflush(stdin);
                        if(ChgNode->data.date.month>=1&&ChgNode->data.date.month<=12&&r==1){
                            printf("请输入修改后的消费日期日份:\n");
                            r=scanf("%d",&ChgNode->data.date.day);
                            fflush(stdin);
                            if(r==1&&ChgNode->data.date.day>=1&&ChgNode->data.date.day<=31){ //判断闰年并求其对应月内的天数有点麻烦，（emmm有空一定写！）
                                break;
                            }
                        }
		            }
		            printf("输入有误(可能输入了非法字符或输入超出范围)，请重新输入\n");
	            }
            break;

        case 58:
            //printf("准备返回......\n\n");
            break; 

        default:
            printf("没有输入对应的数字,请重新输入\n");
            break;
        }
    }while(n!=58);
}