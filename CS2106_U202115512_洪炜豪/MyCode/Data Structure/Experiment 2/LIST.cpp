#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef int status; 
typedef int ElemType; 

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define INFEASIBLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct LIST{  //多链表的管理表定义
     struct { char name[30];
     		  LinkList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;

int cmp(const void *a, const void *b){
   ElemType *c=(ElemType*)a; ElemType *d=(ElemType*)b; 
   return *c-*d;
}

status InitList(LinkList& L);
status DestroyList(LinkList& L);
status ClearList(LinkList& L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
status LocateElem(LinkList L,ElemType e); 
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);  
//附加函数 
status reverseList(LinkList L);
status RemoveNthFromEnd(LinkList L,int n,ElemType &e);
status sortList(LinkList L);
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L,char FileName[]);
void _LISTS();
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
void printflist(LISTS Lists);
void __LISTS(LISTS Lists,int n);
 
int main(void){
	LinkList L=NULL;  
	int op=100,j,i,e=0,pre,next,k,n;
	char filename[50]; 
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList       10. ListInsert\n");
		printf("    	  2. DestroyList    11. ListDelete\n");
		printf("    	  3. ClearList      12. ListTrabverse\n");
		printf("    	  4. ListEmpty      13. reverseList\n");
		printf("    	  5. ListLength     14. RemoveNthFromEnd\n");
		printf("    	  6. GetElem        15. sortList\n");
		printf("    	  7. LocateElem     16. SaveList\n");
		printf("    	  8. PriorElem      17. LoadList\n");
		printf("    	  9. NextElem       18. LISTS\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~18]:");
		scanf("%d",&op);
    switch(op){
       case 0:
         break;
	   case 1:
		 if(InitList(L)==OK) printf("线性表创建成功！\n");
		     else printf("线性表创建失败！\n");
		 getchar();getchar();
		 break;
	   case 2:
		 j=DestroyList(L);
		if (j==INFEASIBLE) printf("线性表不存在！");
        if (j==OK) printf("成功释放线性表空间");
        else printf("错误释放元素空间");    
		 getchar();getchar();
		 break;
	   case 3:
		j=ClearList(L);
		if (j==INFEASIBLE) printf("线性表不存在！");
		if (j==OK) printf("成功清空线性表L");
		else printf("错误释放元素空间");    
		getchar();getchar();
		break;
	   case 4:
		 j=ListEmpty(L);
		if (j==OK) printf("线性表L长度为0");
		else if (j==ERROR) printf("线性表L长度为不为0");
		else if (j==INFEASIBLE) printf("线性表不存在！");
		else printf("未正确判空");
		 getchar();getchar();
		 break;
	   case 5:
		 j=ListLength(L); 
		if (j==INFEASIBLE) printf("线性表不存在！"); 
		else printf("线性表L的长度为%d", j);
		 getchar();getchar();
		 break;
	   case 6:
		 printf("请输入要获取元素的元素逻辑序号\n"); 
		 scanf("%d",&i);    
		 j=GetElem(L,i,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		else if(j==OK) printf("元素的值为%d",e);
		else if(j==ERROR) printf("元素逻辑序号不合法");
		getchar();getchar();
		 break;
	   case 7: 
		 printf("请输入要查找元素的值e\n"); 
		 scanf("%d",&e);  
		 j=LocateElem(L,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(j==ERROR) printf("没有找到指定的元素，查找失败");
		 else printf("查找成功，元素逻辑序号为%d",j);
		 getchar();getchar();
		 break;
	   case 8: 
		 printf("请输入指定元素的值e\n");
		 scanf("%d",&e);  
		 j=PriorElem(L,e,pre); 
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(j==ERROR) printf("没有找到指定元素");
		 else if(j==12) printf("指定元素存在，前驱不存在");
		 else if(j==OK) printf("前驱元素的值为%d",pre);
		 getchar();getchar();
		 break;
	   case 9:   
		 printf("请输入指定元素的值e\n");
		 scanf("%d",&e);
		 j=NextElem(L,e,next);  
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(j==ERROR) printf("没有找到指定元素");
		 else if(j==13) printf("指定元素存在，后继不存在");
		 else if(j==OK) printf("后继元素的值为%d",next);
		 getchar();getchar();
		 break;
	   case 10:
	   	if (L==NULL){
	   		printf("线性表不存在！"); 
	   		getchar();getchar();
		 break;
		   }
		 printf("请输入插入的位置i\n");
		 scanf("%d",&i);  
		 printf("请输入插入元素的值e\n");
		 scanf("%d",&e);
		 j=ListInsert(L,i,e); 
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		if (j!=INFEASIBLE) {
		 	printf("%s\n", j==OK? "插入成功" : j==ERROR? "插入失败" : "数据溢出");
		 getchar();getchar();
		 break;
	   case 11:
		 printf("请输入删除的位置i\n");
		 scanf("%d",&i);
		 j=ListDelete(L,i,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 if(j==ERROR) printf("删除失败，不存在第%d个元素！\n",i);
		 if(j==OK) printf("删除成功，被删除元素的值为%d\n",e);
		 getchar();getchar();
		 break;
	   case 12:
		 j=ListTraverse(L);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 if(j==OK && !L->next) printf("空线性表\n");
		getchar();getchar();
		 break;
	   case 13:
	   	 j=reverseList(L);
	   	  if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else printf("链表翻转成功!");
	   	 getchar();getchar();
		 break;
	   case 14:
	   	 printf("请输入要删除的是倒数第几个结点\n");
		 scanf("%d",&n);    
	   	 j=RemoveNthFromEnd(L,n,e);
	   	  if (j==INFEASIBLE) printf("线性表不存在 "); 
	   	  if (L&&L->next==NULL) printf("线性表为空 "); 
		 else printf("删除成功，被删除元素的值为%d\n",e);
	   	 getchar();getchar();
		 break;	 
	   case 15:
	   	 j=sortList(L);
	   	  if (j==INFEASIBLE) printf("线性表L不存在 "); 
		 else printf("由小到大排序完成");
	   	 getchar();getchar();
		 break;	
	   case 16:
		 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 j=SaveList(L,filename);
	   	  if (j==INFEASIBLE) printf("线性表L不存在"); 
		 else if(j==OK) printf("写入文件完成");
	   	 getchar();getchar();
		 break;	 
	   case 17:
	   	 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 j=LoadList(L,filename);
	   	 if(j==INFEASIBLE) printf("线性表L已存在"); 
		 else if(j==OK) printf("读入文件完成");
	   	 getchar();getchar();
		 break;	
	   case 18:
	   	 _LISTS();
    default:
    	printf("输入有误，请重新输入");
	 	}
    }
	printf("欢迎下次再使用本系统！\n");
	}
}
status InitList(LinkList& L)//线性表初始化 
{
	if(L){
        return INFEASIBLE;
	}
    L= (LNode *) malloc(sizeof( LNode ));
    L->data=0;
    L->next=NULL;
    return OK;
}

status DestroyList(LinkList& L)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    LNode *p=L,*q;
    while(p){
        q=p->next;
        free(p);
        p=q;
    }
    L=NULL;
    return OK;
}

status ClearList(LinkList& L)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    LNode *p = L->next;
    LNode *q;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
    return OK;
}

status ListEmpty(LinkList L)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    if(L->next==NULL) return TRUE;
    return FALSE;
}

status ListLength(LinkList L)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    LNode *p = L->next;
    int length=0;
    while(p){
        length++;
        p=p->next;
    }
    return length;
}

status GetElem(LinkList L,int i,ElemType &e)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    LNode *p = L->next,*q = L->next;
    int length=0,num=0;
    while(p){
        length++;
        p=p->next;
    }
    if(i<1||i>length) return ERROR;
    while(q){
        num++;
        if(num==i){
            e=q->data;
            return OK;
        }
        q=q->next;
    }
	return OK;
}

status LocateElem(LinkList L,ElemType e)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    int length=0,num=0;
    LNode *p = L->next,*q = L->next;
    while(p){
        length++;
        p=p->next;
    }
    while(q){
        num++;
        if(q->data==e) return num;
        q=q->next;
    }
    if(num==length) return ERROR;
	return OK;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    int length=0,num=0;
    LNode *p=L ,*q = L->next;
     while(q){
        length++;
        q=q->next;
    }
    q = L->next;
    while(q){
        num++;
        if(q->data==e&&num!=1) {pre=p->data;return OK;}
        if(q->data==e&&num==1) break;
        q=q->next;
        p=p->next;
    }
    if(num==length) return ERROR;
    else if(num==1) return 12;
	return OK;
}

status NextElem(LinkList L,ElemType e,ElemType &next)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    int length=0,num=0;
    LNode *q=L->next ,*p = L->next;
     while(p){
        length++;
        p=p->next;
    }
    if(L->next==NULL||q->next==NULL) return ERROR;
    p = L->next->next;
    while(q){
        num++;
        if(q->data==e&&num!=length) {next=p->data;return OK;}
        if(q->data!=e&&num==length) return ERROR;
        if(q->data==e&&num==length) return 13;
        q=q->next;
        p=p->next;
    }
	return OK;
}

status ListInsert(LinkList &L,int i,ElemType e)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    int length=0,num=0;
    LNode *p=L ,*q = L->next;
     while(q){
        length++;
        q=q->next;
    }
    q = L->next;
    if(i<1||i>length&&i!=length+1) return ERROR;
    while(q){
        num++;
        if(num==i) {
            LNode *fp= (LNode *) malloc(sizeof( LNode ));
            p->next=fp;
            fp->data=e;
            fp->next=q;
            return OK;}
        q=q->next;
        p=p->next;
    }
    LNode *fp1= (LNode *) malloc(sizeof( LNode ));
    p->next=fp1;
    fp1->data=e;
    fp1->next=NULL;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType &e)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    int length=0,num=0;
    LNode *p=L ,*q = L->next;
     while(q){
        length++;
        q=q->next;
    }
    if(i<1||i>length) return ERROR;
    q = L->next;
    while(q){
        num++;
        if(num==i) {
        p->next=q->next;
        e=q->data;
        free(q);
        return OK;}
        
        q=q->next;
        p=p->next;
    }
	return OK;
}

status ListTraverse(LinkList L)
{
    if(L==NULL){
        return INFEASIBLE;
	}
    if(L->next==NULL) return OK;
    printf("\n-----------all elements -----------------------\n");
    LNode *p=L->next;
    while (p){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

//附加功能//
status reverseList(LinkList L)//链表翻转
{
	if(L==NULL){
        return INFEASIBLE;
	}
	LinkList p=L->next,newHead = NULL;
    while (p != NULL) {
        LinkList remain = p->next;
        p->next = newHead;
        newHead = p;
        p = remain;
        }
    L->next=newHead;
    return OK;
}

status RemoveNthFromEnd(LinkList L,int n,ElemType &e)//删除链表的倒数第n个结点
{
	if(L==NULL){
        return INFEASIBLE;
	}
	int length=ListLength(L);
	if(n<1||n>length) return ERROR;
	ListDelete(L,length-n+1,e);
	return OK;
}


status sortList(LinkList L)//链表排序
{
	if(L==NULL){
        return INFEASIBLE;
	}
	struct LNode *q,*tail;
	int tmp;
	for(tail=NULL;L!=tail;tail=q){
		for(q=L;q->next!=tail;q=q->next){
			if(q->data>q->next->data&&q!=L){
				tmp=q->data;
				q->data=q->next->data;
				q->next->data=tmp;
			}
		}
	}
	return OK;	
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{

    if(L==NULL){
        return INFEASIBLE;
	}
    LNode *p=L->next;
    FILE *fp = fopen(FileName , "w");
    if (fp == NULL)
	{
	    puts("Fail to open file!");
	    exit(1);
	}
    while(p){
        fprintf(fp,"%d ",p->data); 
        p=p->next;
    }
    fclose(fp);  
    return OK;
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L){
        return INFEASIBLE;
	}
    L= (LNode *) malloc(sizeof( LNode ));
    LNode *h=L;
    FILE* fp = fopen(FileName , "r");
    if (fp == NULL)
	{
	    puts("Fail to open file!");
	    exit(1);
	}
   
    while(!feof(fp)){
        LNode *hp= (LNode *) malloc(sizeof( LNode ));
        fscanf(fp,"%d ",&hp->data); 
        h->next=hp;
        hp->next=NULL;
        h=hp;
    }
    fclose(fp); 
    return OK;
}


void _LISTS()//多线性表操作 
{ 
	LISTS Lists;
    int n,e,op=100;
    char name[30];
    Lists.length=0;
    printf("请输入要创建的顺序表个数\n");
	scanf("%d", &n);
	while(n--)
   {
    	printf("请输入表名\n");
		scanf("%s",name);
   		AddList(Lists,name);
   		printf("输入元素，以回车结束\n");
    	do
  			{
     		scanf("%d",&e); 
			ListInsert(Lists.elem[Lists.length-1].L,ListLength(Lists.elem[Lists.length-1].L)+1,e); 
   			}while(getchar()!='\n');
   }
	printf("1.增加新表 2.移除一个线性表 3.查找线性表 4.查看全表 5.对特定表操作 0.返回上级\n");
	printf("输入您的选项\n");
	while(op){
	 	system("cls");	printf("\n\n");
	 	printf("1.增加新表 2.移除一个线性表 3.查找线性表 4.查看全表 5.对特定表操作 0.返回上级\n");
	 	printf("输入您的选项\n");
	 	scanf("%d",&op);
	 	switch(op){
	 		case 1:
	 			printf("请输入要创建的顺序表个数\n");
				scanf("%d", &n);
				while(n--)
   				{
    				printf("请输入表名\n");
					scanf("%s",name);
   					AddList(Lists,name);
   					printf("输入元素，以回车结束\n");
    				do{
     				scanf("%d",&e); 
					ListInsert(Lists.elem[Lists.length-1].L,ListLength(Lists.elem[Lists.length-1].L)+1,e); 
   					}while(getchar()!='\n');
  				getchar();getchar();
		 		break;
	   		case 2:
	   			printf("请输入要删除的表名\n");
				scanf("%s",name);
	   			if (RemoveList(Lists,name)==OK) printf("删除成功"); 
   				else printf("删除失败");
   				getchar();getchar();
		 		break;
	   		case 3:
	   			printf("请输入要查找的表名\n");
				scanf("%s",name);
	   			if (n=LocateList(Lists,name))
   				{
   					printf("%s ",Lists.elem[n-1].name);
   					ListTraverse(Lists.elem[n-1].L);
         			putchar('\n');
   				}
   				else printf("查找失败");
   				getchar();getchar();
		 		break;
		 	case 4:
		 		printflist(Lists);
		 		getchar();getchar();
		 		break;
		 	case 5:
		 		printf("请输入要操作的表名\n");
				scanf("%s",name);
		 		if (n=LocateList(Lists,name))
   				{
   					__LISTS(Lists,n);
   				}
   				else{
   					printf("该表不存在！");
				   }
		 		getchar();getchar();
		 		break;
   			case 0:
        		 break;
    		default:
    			printf("输入有误，请重新输入");
    		}	
		}	
  	}
}

status AddList(LISTS &Lists,char ListName[])
{
    Lists.elem[Lists.length].L= (LNode *) malloc(sizeof( LNode ));
    Lists.elem[Lists.length].L->data=0;
    Lists.elem[Lists.length].L->next=NULL;
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.length++;
	return OK;
	
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    int i=0;
    while(Lists.elem[i].name[0]){
        if(!strcmp(Lists.elem[i].name,ListName)){
        	strcpy(Lists.elem[i].name,"0");
            for(int j=i;j<Lists.length-1;j++){
                Lists.elem[j]=Lists.elem[j+1];
            }
            Lists.length--;
            return OK;
        }
        i++;
    }
    return FALSE;
}

int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    int i=0;
    while(Lists.elem[i].name[0]){
        if(!strcmp(Lists.elem[i].name,ListName)){
            return i+1;
        }
        i++;
    }
    return FALSE;
}

void printflist(LISTS Lists)
{
	for(int n=0;n<Lists.length;n++)
   {
   		printf("%s ",Lists.elem[n].name);
   		ListTraverse(Lists.elem[n].L);
        putchar('\n');
   }
}

void __LISTS(LISTS Lists,int n)
{
	int op=100,j,i,e=0,pre,next,k;
	char filename[50]; 
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  0. Exit           9. ListInsert\n");
		printf("    	  1. DestroyList    10. ListDelete\n");
		printf("    	  2. ClearList      11. ListTrabverse\n");
		printf("    	  3. ListEmpty      12. reverseList\n");
		printf("    	  4. ListLength     13. RemoveNthFromEnd\n");
		printf("    	  5. GetElem        14. sortList\n");
		printf("    	  6. LocateElem     15. SaveList\n");
		printf("    	  7. PriorElem      16. LoadList\n");
		printf("    	  8. NextElem       ");
		printf("    	  ");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~16]:");
		scanf("%d",&op);
    switch(op){
	   case 1:
		 j=DestroyList(Lists.elem[Lists.length-1].L);
		if (j==INFEASIBLE) printf("线性表不存在！");
        if (j==OK) printf("成功释放线性表空间");
        else printf("错误释放元素空间");    
		 getchar();getchar();
		 break;
	   case 2:
		j=ClearList(Lists.elem[Lists.length-1].L);
		if (j==INFEASIBLE) printf("线性表不存在！");
		if (j==OK) printf("成功清空线性表L");
		else printf("错误释放元素空间");    
		getchar();getchar();
		break;
	   case 3:
		 j=ListEmpty(Lists.elem[Lists.length-1].L);
		if (j==OK) printf("线性表L长度为0");
		else if (j==ERROR) printf("线性表L长度为不为0");
		else if (j==INFEASIBLE) printf("线性表不存在！");
		else printf("未正确判空");
		 getchar();getchar();
		 break;
	   case 4:
		 j=ListLength(Lists.elem[Lists.length-1].L); 
		if (j==INFEASIBLE) printf("线性表不存在！"); 
		else printf("线性表L的长度为%d", j);
		 getchar();getchar();
		 break;
	   case 5:
		 printf("请输入要获取元素的元素逻辑序号\n"); 
		 scanf("%d",&i);    
		 j=GetElem(Lists.elem[Lists.length-1].L,i,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		else if(j==OK) printf("元素的值为%d",e);
		else if(j==ERROR) printf("元素逻辑序号不合法");
		getchar();getchar();
		 break;
	   case 6: 
		 printf("请输入要查找元素的值e\n"); 
		 scanf("%d",&e);  
		 j=LocateElem(Lists.elem[Lists.length-1].L,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(j==ERROR) printf("没有找到指定的元素，查找失败");
		 else printf("查找成功，元素逻辑序号为%d",j);
		 getchar();getchar();
		 break;
	   case 7: 
		 printf("请输入指定元素的值e\n");
		 scanf("%d",&e);  
		 j=PriorElem(Lists.elem[Lists.length-1].L,e,pre); 
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(j==ERROR) printf("没有找到指定元素");
		 else if(j==12) printf("指定元素存在，前驱不存在");
		 else if(j==OK) printf("前驱元素的值为%d",pre);
		 getchar();getchar();
		 break;
	   case 8:   
		 printf("请输入指定元素的值e\n");
		 scanf("%d",&e);
		 j=NextElem(Lists.elem[Lists.length-1].L,e,next);  
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(j==13) printf("指定元素存在，后继不存在");
		 else if(j==OK) printf("后继元素的值为%d",next);
		 getchar();getchar();
		 break;
	   case 9:
	   	if (Lists.elem[Lists.length-1].L==NULL){
	   		printf("线性表不存在！"); 
	   		getchar();getchar();
		 break;
		   }
		 printf("请输入插入的位置i\n");
		 scanf("%d",&i);  
		 printf("请输入插入元素的值e\n");
		 scanf("%d",&e);
		 j=ListInsert(Lists.elem[Lists.length-1].L,i,e); 
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		if (j!=INFEASIBLE) 
		 	printf("%s\n", j==OK? "插入成功" : j==ERROR? "插入失败" : "数据溢出");
		 getchar();getchar();
		 break;
	   case 10:
		 printf("请输入删除的位置i\n");
		 scanf("%d",&i);
		 j=ListDelete(Lists.elem[Lists.length-1].L,i,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 if(j==ERROR) printf("删除失败，不存在第%d个元素！\n",i);
		 if(j==OK) printf("删除成功，被删除元素的值为%d\n",e);
		 getchar();getchar();
		 break;
	   case 11:
		 j=ListTraverse(Lists.elem[Lists.length-1].L);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 if(j==OK && !Lists.elem[Lists.length-1].L->next) printf("空线性表\n");
		getchar();getchar();
		 break;
	   case 12:
	   	 j=reverseList(Lists.elem[Lists.length-1].L);
	   	  if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else printf("链表翻转成功!");
	   	 getchar();getchar();
		 break;
	   case 13:
	   	 printf("请输入要删除的是倒数第几个结点\n");
		 scanf("%d",&n);    
	   	 j=RemoveNthFromEnd(Lists.elem[Lists.length-1].L,n,e);
	   	  if (j==INFEASIBLE) printf("线性表不存在 "); 
	   	  if (Lists.elem[Lists.length-1].L&&Lists.elem[Lists.length-1].L->next==NULL) printf("线性表为空 "); 
		 else printf("删除成功，被删除元素的值为%d\n",e);
	   	 getchar();getchar();
		 break;	 
	   case 14:
	   	 j=sortList(Lists.elem[Lists.length-1].L);
	   	  if (j==INFEASIBLE) printf("线性表L不存在 "); 
		 else printf("由小到大排序完成");
	   	 getchar();getchar();
		 break;	
	   case 15:
		 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 j=SaveList(Lists.elem[Lists.length-1].L,filename);
	   	  if (j==INFEASIBLE) printf("线性表L不存在"); 
		 else if(j==OK) printf("写入文件完成");
	   	 getchar();getchar();
		 break;	 
	   case 16:
	   	 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 j=LoadList(Lists.elem[Lists.length-1].L,filename);
	   	 if(j==INFEASIBLE) printf("线性表L已存在"); 
		 else if(j==OK) printf("读入文件完成");
	   	 getchar();getchar();
		 break;	
	   case 0:
         break;
       default:
       	 printf("输入有误，请重新输入");		
    		
		}
	}
}