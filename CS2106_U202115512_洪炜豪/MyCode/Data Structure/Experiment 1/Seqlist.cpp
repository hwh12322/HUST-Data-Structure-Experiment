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
typedef struct{  
	ElemType *elem;
	int length;
	int listsize;
}SqList;
typedef struct{  //线性表的管理表定义
     struct { char name[30];
     		  SqList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;

int cmp(const void *a, const void *b){
   ElemType *c=(ElemType*)a; ElemType *d=(ElemType*)b; 
   return *c-*d;
}

status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
status LocateElem(SqList L,ElemType e); 
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int j,ElemType e);
status ListDelete(SqList &L,int j,ElemType &e);
status ListTraverse(SqList L);  
//附加函数 
status MaxSubArray(SqList L);
status SubArrayNum(SqList L,int k);
status sortList(SqList L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList &L,char FileName[]);
void _LISTS();
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
void printflist(LISTS Lists);
void __LISTS(LISTS Lists,int n);
 
int main(void){
	SqList L;  
	L.elem=NULL;
	int op=100,j,i,e=0,pre,next,k;
	char filename[50]; 
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList       10. ListInsert\n");
		printf("    	  2. DestroyList    11. ListDelete\n");
		printf("    	  3. ClearList      12. ListTrabverse\n");
		printf("    	  4. ListEmpty      13. MaxSubArray\n");
		printf("    	  5. ListLength     14. SubArrayNum\n");
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
        if (j==OK) 
            if (L.elem)
                printf("未正确释放数据元素空间");
            else printf("成功释放线性表空间");
        else printf("ERROR");    
		 getchar();getchar();
		 break;
	   case 3:
		j=ClearList(L);
		if (j==INFEASIBLE) printf("线性表不存在！");
		if (L.length) printf("未正确清空");
		if (!L.elem)  printf("错误释放元素空间");
		if (j==OK) printf("成功清空线性表L");
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
		else if(L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表求表长");
		else printf("线性表L的长度为%d", j);
		 getchar();getchar();
		 break;
	   case 6:
		 printf("请输入要获取元素的元素逻辑序号\n"); 
		 scanf("%d",&i);    
		 j=GetElem(L,i,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		else if(L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表获取元素");
		else if(j==OK) printf("元素的值为%d",e);
		else if(j==ERROR) printf("元素逻辑序号不合法");
		getchar();getchar();
		 break;
	   case 7: 
		 printf("请输入要查找元素的值e\n"); 
		 scanf("%d",&e);  
		 j=LocateElem(L,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表查找元素");
		 else if(j==ERROR) printf("没有找到指定的元素，查找失败");
		 else printf("查找成功，元素逻辑序号为%d",j);
		 getchar();getchar();
		 break;
	   case 8: 
		 printf("请输入指定元素的值e\n");
		 scanf("%d",&e);  
		 j=PriorElem(L,e,pre); 
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表查找前驱元素");
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
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表查找后继元素");
		 else if(j==ERROR) printf("没有找到指定元素");
		 else if(j==13) printf("指定元素存在，后继不存在");
		 else if(j==OK) printf("后继元素的值为%d",next);
		 getchar();getchar();
		 break;
	   case 10:
		 printf("请输入插入的位置i\n");
		 scanf("%d",&i);  
		 printf("请输入插入元素的值e\n");
		 scanf("%d",&e);
		 j=ListInsert(L,i,e); 
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行插入操作！");
		 else{
		 	printf("%s\n", j==OK? "插入成功" : j==ERROR? "插入失败" : "数据溢出");
		 getchar();getchar();
		 break;
	   case 11:
		 printf("请输入删除的位置i\n");
		 scanf("%d",&i);
		 j=ListDelete(L,i,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行删除操作！");
		 if(j==ERROR) printf("删除失败，不存在第%d个元素！\n",i);
		if(j==OK) printf("删除成功，被删除元素的值为%d\n",e);
		 getchar();getchar();
		 break;
	   case 12:
		 j=ListTraverse(L);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表进行遍历操作！");
		 if(j==OK && !L.length) printf("空线性表\n");
		getchar();getchar();
		 break;
	   case 13:
	   	 j=MaxSubArray(L);
	   	  if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(j==OK && !L.length) printf("空线性表\n");
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行求最大连续子数组和操作！");
		 else printf("最大连续子数组和为%d",j);
	   	 getchar();getchar();
		 break;
	   case 14:
	   	 printf("请输入k\n");
		 scanf("%d",&k);    
	   	 j=SubArrayNum(L,k);
	   	  if (j==INFEASIBLE||(L.elem&&L.length==0)) printf("线性表L不存在或为空 "); 
		 else if(j==OK && !L.length) printf("空线性表\n");
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行求和为k的连续子数组的个数操作！");
		 else printf("线性表中和为k的连续子数组的个数为%d",j);
	   	 getchar();getchar();
		 break;	 
	   case 15:
	   	 j=sortList(L);
	   	  if (j==INFEASIBLE||(L.elem&&L.length==0)) printf("线性表L不存在或为空 "); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行由小到大排序操作！");
		 else if(j==OK && !L.length) printf("空线性表\n");
		 else printf("由小到大排序完成");
	   	 getchar();getchar();
		 break;	
	   case 16:
		 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 j=SaveList(L,filename);
	   	  if (j==INFEASIBLE||(L.elem&&L.length==0)) printf("线性表L不存在或为空 "); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行操作！");
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
status InitList(SqList& L)//线性表初始化 
{
	if(L.elem){
        return INFEASTABLE;
	}
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}

status DestroyList(SqList& L)
{
    if(!L.elem){
        return INFEASTABLE;
	}
	
	L.elem=NULL;
    L.length=0;
    L.listsize=0;
	return OK; 
}

status ClearList(SqList& L)
{
    if(!L.elem){
        return INFEASTABLE;
	}
	free (L.elem);
	
    L.length=0;
    L.listsize=0;
	return OK; 
}

status ListEmpty(SqList L)
{
    if(!L.length&&L.elem){//线性表存在且为空 
        return OK;
    }
    if(L.length&&L.elem){//线性表存在且非空 
        return ERROR;
    }
    if(L.elem==NULL&&L.length==0){//线性表不存在
        return INFEASTABLE;
    }
	return 0;
}

status ListLength(SqList L)
{
    if(L.elem){
        return L.length;
    }
    return INFEASTABLE;
}

status GetElem(SqList L,int i,ElemType &e)
{
    if(L.elem==NULL){
        return INFEASTABLE;
    }
    if(i<1||i>L.length){
        return ERROR;
    }
    e=L.elem[i-1];
    return OK;
}

status LocateElem(SqList L,ElemType e)
{
    if(L.elem==NULL){
        return INFEASTABLE;
    }
    int j;
    for(j=0;j<L.listsize;j++){
        if(e==L.elem[j]){
            return j+1;
        }
    }
    return 0;
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
{
    if(L.elem==NULL){
        return INFEASTABLE;
    }
    int j;
    for(j=0;j<L.length;j++){
        if(e==L.elem[j])
		{
            if(j!=0){
            pre=L.elem[j-1];
            return OK;
			}
			else{
				return 12;
			}
        }
    }
    return ERROR;
}

status NextElem(SqList L,ElemType e,ElemType &next)
{
    if(L.elem==NULL){
        return INFEASTABLE;
    }
    int j;
    for(j=0;j<L.length;j++){
        if(e==L.elem[j]){
        	if(j!=L.length-1){
        		 next=L.elem[j+1];
            return OK;
			}
           if(j==L.length-1){
           	return 13;
		   }
        }
        
    }
    return ERROR;
}

status ListInsert(SqList &L,int j,ElemType e)
{
    if(L.elem==NULL){
		printf("线性表不存在！");
        return INFEASTABLE;
    }
    int i;
	if(j==0||j>L.length+1){
        return ERROR;
    }
     if(L.length==0){
        L.elem[0]=e;
        L.length++;
        return OK;
    }
    
    int a[100];
    for(i=0;i<L.length;i++){
        a[i]=L.elem[i];
    }
    L.length++;L.listsize++;
    L.elem=(ElemType *) malloc(sizeof(ElemType)*L.listsize);
    for(i=j;i<L.length;i++){
        L.elem[i]=a[i-1];
    }
    L.elem[j-1]=e;
    for(i=0;i<j-1;i++){
        L.elem[i]=a[i];
    }
    return OK;
}

status ListDelete(SqList &L,int j,ElemType &e)
{
    if(L.elem==NULL){
        return INFEASTABLE;
    }
    int i;
    if(j==0||j>L.length){
        return ERROR;
    }
    L.length--;L.listsize--;
    e=L.elem[j-1];
    for(i=j-1;i<L.length;i++){
    L.elem[i]=L.elem[i+1];
        }
    return OK;
}

status ListTraverse(SqList L)
{
    if(L.elem==NULL){
        return INFEASTABLE;
    }
    else{
        if(L.length==0){
        L.length++;
        return OK;
    	}
    }
    printf("\n-----------all elements -----------------------\n");
    for(int i=0;i<L.length;i++){
        if(i==0){
            printf("%d",L.elem[i]);
        }
        else{
            printf(" %d",L.elem[i]);
        }
    }
    printf("\n");
    return OK;
}

//附加功能//
status MaxSubArray(SqList L)//最大连续子数组和
{
	 if(L.elem==NULL){
        return INFEASTABLE;
    }
    else{
        if(L.length==0){
        L.length++;
        return OK;
    	}
    }
	int thissum=0,maxsum=0,j;
	for(j=0;j<L.length;j++)//只需遍历一遍，算法复杂度O(n) ,当当前累计的值小于0，则归零重新累加 
	{
		thissum+=L.elem[j];
		if(thissum>maxsum)
			maxsum=thissum;
		else if(thissum<0)
			thissum=0;
	}
	return maxsum;
}

status SubArrayNum(SqList L,int k)//和为K的子数组个数 
{
	if(L.elem==NULL){
        return INFEASTABLE;
    }
    else{
        if(L.length==0){
        L.length++;
        return OK;
    	}
    }
	int sum=0,i,j;
    for (i=0;i<L.length;i++)//对于每个元素，都对其与后面的所有元素进行累加，复杂度O(n^2) 
    {
        int num=0;
        for(j=i;j<L.length;j++){
            num+=L.elem[j];
            if(num==k) sum++;
        }
    }
    return sum;
}
/*哈希表
status SubArrayNum(SqList L,int k)
{
	 Map<Integer,Integer> map=new HashMap<Integer, Integer>();
        map.put(0,1);
        int count=0;
        int sum=0;
        for (int i=0;i<L.length;i++){
            sum+=L.elem[i];
            if (map.get(sum-k)!=null){
                count+=map.get(sum-k);
            }
            //如果总和没出现过，则添加进哈希表,如果出现过，哈希表中的值+1
            if(map.get(sum)==null)
                map.put(sum,1 );
            else
                map.put(sum,map.get(sum)+1 );
        }
        return count;
} 
*/

status sortList(SqList L)//链表排序
{
	if(L.elem==NULL){
        return INFEASTABLE;
    }
    else{
        if(L.length==0){
        L.length++;
        return OK;
    	}
    }
	qsort(L.elem,L.length,sizeof(L.elem[0]),cmp);//快排 
	return OK;
}

status  SaveList(SqList L,char FileName[])//实现线性表的文件形式保存 
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    FILE *fp = fopen(FileName , "w");
    if (fp == NULL)
	{
	    puts("Fail to open file!");
	    exit(1);
	}
    for(int i=0;i<L.length;i++)  
        fprintf(fp,"%d ",L.elem[i]); 
    fclose(fp);  
    return OK;
}
status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
   
    int i=0;
	if(L.elem){
        return INFEASIBLE;
    }
    FILE* fp = fopen(FileName , "r");
    if (fp == NULL)
	{
	    puts("Fail to open file!");
	    exit(1);
	}
    L.elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    while(!feof(fp)){
    	fscanf(fp,"%d ",&L.elem[i++]); 
    	L.length++;
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
			ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e); 
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
					ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e); 
   					}while(getchar()!='\n');
  				getchar();getchar();
		 		break;
	   		case 2:
	   			printf("请输入要删除的表名\n");
				scanf("%s",name);
	   			if (RemoveList(Lists,name)==OK)
	   			{
   					printf("删除成功"); 
				}
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
    Lists.elem[Lists.length].L.elem = (ElemType *) malloc(LIST_INIT_SIZE  * sizeof( ElemType ));	
	if ( !Lists.elem[Lists.length].L.elem ){
		printf("存储空间申请失败\n");
		exit(OVERFLOW);
	} 
    Lists.elem[Lists.length].L.length=0;
    Lists.elem[Lists.length].L.listsize=100;
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
		printf("    	  3. ListEmpty      12. MaxSubArray\n");
		printf("    	  4. ListLength     13. SubArrayNum\n");
		printf("    	  5. GetElem        14. sortList\n");
		printf("    	  6. LocateElem     15. SaveList\n");
		printf("    	  7. PriorElem      16. LoadList\n");
		printf("    	  8. NextElem       ");
		printf("    	  \n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~16]:");
		scanf("%d",&op);
    switch(op){
	   case 1:
		 j=DestroyList(Lists.elem[n-1].L);
		if (j==INFEASIBLE) printf("线性表不存在！");
        if (j==OK) 
            if (Lists.elem[n-1].L.elem)
                printf("未正确释放数据元素空间");
            else printf("成功释放线性表空间");
        else printf("ERROR");    
		 getchar();getchar();
		 break;
	   case 2: 
		j=ClearList(Lists.elem[n-1].L);
		if (j==INFEASIBLE) printf("线性表不存在！");
		if (Lists.elem[n-1].L.length) printf("未正确清空");
		if (!Lists.elem[n-1].L.elem)  printf("错误释放元素空间");
		if (j==OK) printf("成功清空线性表L");
		getchar();getchar();
		break;
	   case 3:
		 j=ListEmpty(Lists.elem[n-1].L);
		if (j==OK) printf("线性表L长度为0");
		else if (j==ERROR) printf("线性表L长度为不为0");
		else if (j==INFEASIBLE) printf("线性表不存在！");
		else printf("未正确判空");
		 getchar();getchar();
		 break;
	   case 4:
		 j=ListLength(Lists.elem[n-1].L); 
		if (j==INFEASIBLE) printf("线性表不存在！"); 
		else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表求表长");
		else printf("线性表L的长度为%d", j);
		 getchar();getchar();
		 break;
	   case 5:
		 printf("请输入要获取元素的元素逻辑序号\n"); 
		 scanf("%d",&i);    
		 j=GetElem(Lists.elem[n-1].L,i,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表获取元素");
		else if(j==OK) printf("元素的值为%d",e);
		else if(j==ERROR) printf("元素逻辑序号不合法");
		getchar();getchar();
		 break;
	   case 6:
		 printf("请输入要查找元素的值e\n"); 
		 scanf("%d",&e);  
		 j=LocateElem(Lists.elem[n-1].L,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表查找元素");
		 else if(j==ERROR) printf("没有找到指定的元素，查找失败");
		 else printf("查找成功，元素逻辑序号为%d",j);
		 getchar();getchar();
		 break;
	   case 7:
		 printf("请输入指定元素的值e\n");
		 scanf("%d",&e);  
		 j=PriorElem(Lists.elem[n-1].L,e,pre); 
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表查找前驱元素");
		 else if(j==ERROR) printf("没有找到指定元素");
		 else if(j==12) printf("指定元素存在，前驱不存在");
		 else if(j==OK) printf("前驱元素的值为%d",pre);
		 getchar();getchar();
		 break;
	   case 8:
		 printf("请输入指定元素的值e\n");
		 scanf("%d",&e);
		 j=NextElem(Lists.elem[n-1].L,e,next);  
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表查找后继元素");
		 else if(j==13) printf("指定元素存在，后继不存在");
		 else if(j==OK) printf("后继元素的值为%d",next);
		 getchar();getchar();
		 break;
	   case 9:
		 printf("请输入插入的位置i\n");
		 scanf("%d",&i);  
		 printf("请输入插入元素的值e\n");
		 scanf("%d",&e);
		 j=ListInsert(Lists.elem[n-1].L,i,e); 
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行插入操作！");
		 else
		 	printf("%s\n", j==OK? "插入成功" : j==ERROR? "插入失败" : "数据溢出");
		 getchar();getchar();
		 break;
	   case 10:
		 printf("请输入删除的位置i\n");
		 scanf("%d",&i);
		 j=ListDelete(Lists.elem[n-1].L,i,e);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行删除操作！");
		 if(j==ERROR) printf("删除失败，不存在第%d个元素！\n",i);
		if(j==OK) printf("删除成功，被删除元素的值为%d\n",e);
		 getchar();getchar();
		 break;
	   case 11:
		 j=ListTraverse(Lists.elem[n-1].L);
		 if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("可能会对不存在的线性表进行遍历操作！");
		 if(j==OK && !Lists.elem[n-1].L.length) printf("空线性表\n");
		getchar();getchar();
		 break;
	   case 12:
	   	 j=MaxSubArray(Lists.elem[n-1].L);
	   	  if (j==INFEASIBLE) printf("线性表不存在！"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行求最大连续子数组和操作！");
		 else printf("最大连续子数组和为%d",j);
	   	 getchar();getchar();
		 break;
	   case 13:
	   	 printf("请输入k\n");
		 scanf("%d",&k);    
	   	 j=SubArrayNum(Lists.elem[n-1].L,k);
	   	  if (j==INFEASIBLE||(Lists.elem[n-1].L.elem&&Lists.elem[n-1].L.length==0)) printf("线性表L不存在或为空 "); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行求和为k的连续子数组的个数操作！");
		 else printf("线性表中和为k的连续子数组的个数为%d",j);
	   	 getchar();getchar();
		 break;	 
	   case 14:
	   	 j=sortList(Lists.elem[n-1].L);
	   	  if (j==INFEASIBLE||(Lists.elem[n-1].L.elem&&Lists.elem[n-1].L.length==0)) printf("线性表L不存在或为空 "); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行由小到大排序操作！");
		 else printf("由小到大排序完成");
	   	 getchar();getchar();
		 break;	
	   case 15:
		 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 j=SaveList(Lists.elem[n-1].L,filename);
	   	  if (j==INFEASIBLE||(Lists.elem[n-1].L.elem&&Lists.elem[n-1].L.length==0)) printf("线性表L不存在或为空 "); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("不能对不存在的线性表进行操作！");
		 else if(j==OK) printf("写入文件完成");
	   	 getchar();getchar();
		 break;	 
	   case 16:
	   	 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 j=LoadList(Lists.elem[n-1].L,filename);
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
