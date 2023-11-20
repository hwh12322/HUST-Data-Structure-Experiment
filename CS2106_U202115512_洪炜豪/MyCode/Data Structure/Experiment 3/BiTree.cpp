#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include <stack>
#include <iostream>
using namespace std;
//1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 5 e  0 null  0 null -1 null
//1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 3 e  0 null  0 null -1 null
//1 a 2 b 0 null  3 c 4 d 0 null  5 e  0 null 0 null  0 null  0 null -1 null

//湖南 1 a 2 b 0 null 0 null 3 c 4 d 0 null 0 null 5 e 0 null 0 null -1 null
//湖北 1 a 2 b 3 c 0 null 0 null 0 null 0 null -1 null
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

int i,num[1000];

typedef int status;
typedef int KeyType; 
typedef struct {
         KeyType  key;
         char others[20];
	} TElemType; //二叉树结点类型定义

typedef struct BiTNode{  //二叉链表结点的定义
	      TElemType  data;
	      struct BiTNode *lchild,*rchild;
	} BiTNode, *BiTree;

typedef struct moretrees{  //多二叉树的管理表定义
     struct { char name[30];
     		  BiTree T;	
      } elem[10];
      int length;
 }BiTrees;

void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}
BiTNode* Parent(BiTree T,BiTree p);
status CreateBiTree(BiTree& T, TElemType definition[],int &i);
status CreateBiTNode(BiTree& T, TElemType definition[], int num[], int& i);
status DestroyBiTree(BiTree &T);
status ClearBiTree(BiTree &T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree root,KeyType value);
void LocateNode1(BiTree T,KeyType e,int &i);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
BiTNode* LocateNode2(BiTree T,KeyType e,KeyType &k);
status DeleteNode(BiTree &T,KeyType e);
void PreOrderTraverse(BiTree T,void (*visit)(BiTree));
void InOrderTraverse(BiTree T,void (*visit)(BiTree));
void PostOrderTraverse(BiTree T,void (*visit)(BiTree));
void LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
//附加函数 
int MaxPathSum(int &self,BiTree root,int Sum);
BiTNode* LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2);
void InvertTree(BiTree &T);
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree& T, char FileName[]);
void BITREES();
status AddBiTree(BiTrees &Lists,char ListName[]);
status RemoveBiTree(BiTrees &Lists,char ListName[]);
int LocateBiTree(BiTrees Lists,char ListName[]);
void printfBiTrees(BiTrees Lists);
void _BITREES(BiTrees Lists,int n);

int main(void){
	TElemType definition[100];
	TElemType value,c;
	BiTree T=NULL,p=NULL;
	int ans,e,self=0,Sum=0,op=100,e1,e2;
	int LR;
	char filename[50]; 
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1.  CreateBiTree     11. PreOrderTraverse\n");
		printf("    	  2.  DestroyBiTree    12. InOrderTraverse\n");
		printf("    	  3.  ClearBiTree      13. PostOrderTraverse\n");
		printf("    	  4.  BiTreeEmpty      14. LevelOrderTraverse\n");
		printf("    	  5.  BiTreeDepth      15. MaxPathSum\n");
		printf("    	  6.  LocateNode       16. LowestCommonAncestor\n");
		printf("    	  7.  Assign           17. InvertTree\n");
		printf("    	  8.  GetSibling       18. SaveBiTree\n");
		printf("    	  9.  InsertNode       19. LoadBiTree\n");
		printf("    	  10. DeleteNode       20. BiTrees\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~20]:");
		scanf("%d",&op);
    switch(op){
       case 0:
         break;
	   case 1:
	     if(T){
			 printf("二叉树已存在！\n");
			 getchar();getchar();
			 break;
		 }
		 i=0;
		 printf("以前序遍历输入二叉树各结点数据，以“-1 null“结束\n");
		 do {
		    scanf("%d %s",&definition[i].key,definition[i].others);
			} while (definition[i++].key!=-1);
		 ans=CreateBiTree(T,definition,i);
		 if (ans==OK){
  			  printf("二叉树创建成功！\n");
			}
		 else if(ans==ERROR){
			  printf("关键字不唯一！创建失败！\n");
		 }
		 getchar();getchar();
		 break;
	   case 2:
	     if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 ans=DestroyBiTree(T);
         if (ans==OK) printf("成功销毁二叉树");
         else printf("错误释放元素空间"); 
		 memset(definition, 0, 100); 
		 getchar();getchar();
		 break;
	   case 3:
	     if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 ans=ClearBiTree(T);
		 if (ans==OK) printf("成功清空二叉树");
	  	 else printf("错误释放元素空间");  
		 memset(definition, 0, 100);  
	 	 getchar();getchar();
		 break;
	   case 4:
		 ans=BiTreeEmpty(T);
		 if (ans==TRUE) printf("二叉树为空树");
	     else if (ans==ERROR) printf("二叉树不为空！");
		 getchar();getchar();
		 break;
	   case 5:
	     if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 ans=BiTreeDepth(T); 
		 printf("二叉树的深度为%d", ans);
		 getchar();getchar();
		 break;
	   case 6:
	     if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("请输入要查找的结点的关键字\n"); 
		 scanf("%d",&e);    
		 p=LocateNode(T,e);
		 if (p) printf("查找成功！结点数据为%d,%s",p->data.key,p->data.others); 
		 else printf("查无此结点！");
	 	 getchar();getchar();
		 break;
	   case 7: 
		 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("依次输入要赋值结点的关键字和要赋值的数据\n");
		 scanf("%d %d %s",&e,&value.key,value.others);
		 ans=Assign(T,e,value);
		 if (ans==OK) printf("赋值操作成功");
		 if (ans==ERROR) printf("赋值操作失败，原因：查无具有该关键字的结点");
		 if (ans==13) printf("赋值操作失败，原因：关键字发生重复");
		 getchar();getchar();
		 break;
	   case 8: 
		 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("请输入结点关键字以查找其兄弟结点\n"); 
		 scanf("%d",&e);    
		 p=GetSibling(T,e);
		 if (p) printf("查找成功！兄弟结点数据为%d,%s",p->data.key,p->data.others); 
		 else printf("无兄弟结点！");
		 getchar();getchar();
		 break;
	   case 9:   
		 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("依次输入要插入结点位置的关键字,左右子树选择（左0右1，-1为作为根节点插入）以及结点的数据\n");
		 scanf("%d %d %d %s",&e,&LR,&c.key,c.others);
		 ans=InsertNode(T,e,LR,c);
		 if (ans==OK) printf("插入操作成功");
		 if (ans==ERROR) printf("插入操作失败，原因：查无具有该关键字的结点");
		 if (ans==13) printf("插入操作失败，原因：关键字发生重复");
		 getchar();getchar();
		 break;
	   case 10:
	   	 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("请输入要删除的结点的关键字\n"); 
		 scanf("%d",&e);
		 ans=DeleteNode(T,e);
		 if (ans==OK ) printf("删除操作成功");
		 else printf("删除操作失败，查无此结点！");
		 getchar();getchar();
		 break;
	   case 11:
		 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 PreOrderTraverse(T,visit);
		 getchar();getchar();
		 break;
	   case 12:
		 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 InOrderTraverse(T,visit);
		 getchar();getchar();
		 break;
	   case 13:
	   	 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 PostOrderTraverse(T,visit);
	   	 getchar();getchar();
		 break;
	   case 14:
	   	 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 LevelOrderTraverse(T,visit);
	   	 getchar();getchar();
		 break;	
	   case 15:
	     if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 ans=MaxPathSum(self,T,Sum);
	   	 printf("根节点到叶子结点的最大路径和为%d\n",self);
	   	 getchar();getchar();
		 break;	
	   case 16:
	   	 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("请输入两个结点的关键字\n");
		 scanf("%d %d",&e1,&e2);
		 p=LowestCommonAncestor(T,e1,e2);
		 if (p) printf("查找成功！最近公共祖先结点数据为%d,%s",p->data.key,p->data.others);
		 else printf("无公共祖先！");
	   	 getchar();getchar();
		 break;	
	   case 17:
	   	 if(!T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 InvertTree(T);
		 printf("二叉树翻转成功！");
	   	 getchar();getchar();
		 break;	
	   case 18:
		 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 ans=SaveBiTree(T,filename);
	   	  if (ans==INFEASIBLE) printf("二叉树不存在"); 
		 else if(ans==OK) printf("写入文件完成");
	   	 getchar();getchar();
		 break;	 
	   case 19:
	   	 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 ans=LoadBiTree(T,filename);
	   	 if(ans==INFEASIBLE) printf("二叉树已存在"); 
		 else if(ans==OK) printf("读入文件完成");
	   	 getchar();getchar();
		 break;	
	   case 20:
	     BITREES();
	 	}
    }
}


BiTNode* Parent(BiTree T,BiTree p)
{/*根据已知节点求父节点的核心代码*/
    if(T==NULL||T==p||p==NULL){/*T==p说明p是根节点，所有没有父节点*/
    	return NULL;
	}
	if(T->lchild==p||T->rchild==p){/*在递归过程中除根节点以外的所有节点总会先被这句代码检查一次，所以T==P只会在根节点处可能被成功触发*/
		return T;
	}
	BiTree temp;
	temp=Parent(T->lchild,p);
	if(temp!=NULL){
		return temp;
	}else{
		return Parent(T->rchild,p);
	}
}

int jiance(TElemType definition[])
{
    int a[10000]={0},b=0,j;
	memset(a, 0, 1000);
    while(definition[b].key!=-1){
        a[definition[b].key]++;
        b++;
    }
    for(j=1;j<1000;j++){
        if(a[j]>1) return 0;
    }
    return 1;
}

status CreateBiTree(BiTree& T, TElemType definition[],int &i)
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (jiance(definition)==0) return ERROR;
	BiTree ans;
	ans = (BiTree)malloc(sizeof(BiTNode));
	T = ans;
	memset(num, 0, 1000);//num全部置0
	if (definition[0].key == 0|| definition[0].key == -1) {
		T = NULL;
		return OK;
	}//根结点为空的空二叉树
	i = 0;
	
	T = (BiTree)malloc(sizeof(BiTNode));
	T->data.key = definition[i].key;
	strcpy(T->data.others, definition[i].others);
	num[definition[i].key] = 1;
	i++;
	if (ERROR == CreateBiTNode(T->lchild, definition, num, i) || ERROR == CreateBiTNode(T->rchild, definition, num, i))
		return ERROR;
	return OK;
	/********** End **********/
}

status CreateBiTNode(BiTree& T, TElemType definition[], int num[], int& i) {

	if (definition[i].key == 0 || definition[i].key == -1) {
		T = NULL;
		i += definition[i].key + 1;
		return OK;
	}
	T = (BiTree)malloc(sizeof(BiTNode));
	T->data.key = definition[i].key;
	strcpy(T->data.others, definition[i].others);
	num[definition[i].key] = 1;
	i++;
	if (ERROR == CreateBiTNode(T->lchild, definition, num, i) || ERROR == CreateBiTNode(T->rchild, definition, num, i))
		return ERROR;
	return OK;
}

status DestroyBiTree(BiTree &T)
{
   if (T)
   {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T=NULL;
   }
   return OK;
}

status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    if(T)
    {
        ClearBiTree(T->lchild);
        ClearBiTree(T->rchild);
        free(T);
    }
    T=NULL;
    return OK;
}

status BiTreeEmpty(BiTree T)
{
    if(T)
        return FALSE;
    else
        return TRUE;
}

int max(int a,int b)
{
    if(a>b) return a;
    else return b;
}
int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    if(T==NULL) return 0; 
    else{
         return 1 + max(BiTreeDepth(T->lchild),BiTreeDepth(T->rchild));
    }
}

BiTNode* LocateNode(BiTree root,KeyType value)
//查找结点
{
    if(root == NULL){
			return NULL;
		}
    else if(root != NULL && root->data.key ==value ){
			return root;
		}
    else{
			BiTree no1 = LocateNode(root->lchild,value);
			BiTree no2 = LocateNode(root->rchild,value);
			if(no1 != NULL && no1->data.key==value){
				return no1;
			}else if(no2 != NULL && no2->data.key==value){
				return no2;
			}
            else{
				return NULL ;
			}
		}
}

void LocateNode1(BiTree T,KeyType e,int &i)
//唯一性判断
{
    if(T==NULL) return ;
    if(e==T->data.key){
        i++;
    }
    LocateNode1(T->lchild,e,i);
    LocateNode1(T->rchild,e,i);
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。
{
    BiTree q;
    int i=0;
	TElemType j;
    q=LocateNode(T,e);
    if(q==NULL) return ERROR;
    else {
		j=q->data;
        q->data=value;
    }
    LocateNode1(T,value.key,i);
    if(i<=1) return OK;
    else{
		q->data=j;
		return 13;
	}
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    if(T->data.key==e) return NULL;
	BiTree q=LocateNode(T,e);
	BiTree T1=Parent(T,q);
    if(T1->lchild==q){
        return T1->rchild;
    }
   if(T1->rchild==q){
        return T1->lchild;
    }
	return NULL;
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点
{
    LocateNode1(T,c.key,i);
    if(!LocateNode(T,e)){
        return ERROR;
    }
	if(i) return 13;
    if(LR==-1){
        BiTree q = (BiTree)malloc(sizeof(BiTNode));
        q->lchild=NULL;
        q->rchild=T;
        q->data=c;
        T=q;
        return OK;
    }
    else{
        BiTree p=LocateNode(T,e);
        BiTree p1 = (BiTree)malloc(sizeof(BiTNode));
        p1->data=c;
        if(LR==0){
            p1->rchild=p->lchild;
            p1->lchild=NULL;
            p->lchild=p1;
            return OK;
        }
        if(LR==1){
            p1->rchild=p->rchild;
            p1->lchild=NULL;
            p->rchild=p1;
            return OK;
        }
    }
	return 0;
}

BiTNode* LocateNode2(BiTree T,KeyType e,KeyType &k)
//查找父结点
{
   BiTree q=LocateNode(T,e);
    if(T->lchild==q){
        k=1;
        return T;
    }
    if(T->rchild==q){
        k=2;
        return T;
    }
   if(T->lchild!=q&&T->rchild!=q){
   LocateNode2(T->lchild,e,k);
   LocateNode2(T->rchild,e,k);
   }
   return NULL;
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点
{
    BiTree q1=T;
    int k;
    if(!LocateNode(T,e)){
        return ERROR;
    }
    if(T->data.key==e){
        if(T->lchild==NULL&&T->rchild==NULL){
           T=NULL;
        }
        if(T->lchild&&T->rchild==NULL){
            T=T->lchild;
            free(q1);
        }
        if(T->rchild&&T->lchild==NULL){
            T=T->rchild;
            free(q1);
        }
        if(T->rchild&&T->lchild){
           BiTree q=T->lchild;
           while(q){
               if(q->rchild){
                   q=q->rchild;
               }
               if(q->rchild==NULL&&q->lchild){
                   q=q->lchild;
               }
               if(q->rchild==NULL&&q->lchild==NULL){
                   break;
               }
           }
           q->rchild=T->rchild;
           T=T->lchild;
           free(q1);
        }
        return OK;
    }
    else{
       BiTree p=LocateNode(T,e);
       BiTree p1=LocateNode2(T,e,k);
	    BiTree p2=Parent(T,p);
         if(p->lchild==NULL&&p->rchild==NULL){
           if(k==1) p2->lchild=NULL;

         if(k==2) p2->rchild=NULL;
          
       }
       if(p->lchild&&p->rchild==NULL){
         if(k==1) p1->lchild=p->lchild;
         if(k==2) p1->rchild=p->lchild;
          free(p);
       }
       if(p->rchild&&p->lchild==NULL){
         if(k==1) p1->lchild=p->rchild;
         if(k==2) p1->rchild=p->rchild;
          free(p);
       }
       if(p->rchild&&p->lchild){
           BiTree p2=T->lchild;
           while(p2){
               if(p2->rchild){
                   p2=p2->rchild;
               }
               if(p2->rchild==NULL&&p2->lchild){
                   p2=p2->lchild;
               }
               if(p2->rchild==NULL&&p2->lchild==NULL){
                   break;
               }
           }
           p2->rchild=p->rchild;
           if(k==1) p1->lchild=p->lchild;
           if(k==2) p1->rchild=p->lchild;
          free(p);
       }
       return OK;
    }
}

void PreOrderTraverse(BiTree T,void (*visit)(BiTree))
{
	BiTree p=T;
	stack <BiTree> s;	
    while (p || !s.empty())				//设置循环并以p和栈都为空时为结束循环标志;
	{
		if (p) {						//如果p不是空;
			visit(p);
			s.push(p);					//把p结点入栈，为的是保存p结点的右子树的位置;
			p = p->lchild;				//访问p结点的左子树;
		}
		else {
			p = s.top()->rchild;		//如果p为空,说明上个结点的左子树是空的，此时需要访问上个节点的右子树;
			s.pop();					//弹出栈顶元素，即上个节点;
		}
	}
}

void InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    if (T)
    {
        InOrderTraverse(T->lchild,visit);
        visit(T);
        InOrderTraverse(T->rchild,visit);
    }
}

void PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    if (T)
    {
        PostOrderTraverse(T->lchild,visit);
        PostOrderTraverse(T->rchild,visit);
        visit(T);
    }
}

int front=0,rear=0;
//入队函数
void EnQueue(BiTree *a,BiTree node){
    a[rear++]=node;
}
//出队函数
BiTNode* DeQueue(BiTNode** a){
    return a[front++];
}
void LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
	BiTNode * p;
    //采用顺序队列，初始化创建队列数组
    BiTree a[20];
    //根结点入队
    EnQueue(a, T);
    //当队头和队尾相等时，表示队列为空
    while(front<rear) {
        //队头结点出队
        p=DeQueue(a);
        visit(p);
        //将队头结点的左右孩子依次入队
        if (p->lchild!=NULL) {
            EnQueue(a, p->lchild);
        }
        if (p->rchild!=NULL) {
            EnQueue(a, p->rchild);
        }
    }
}

//附加功能//
int MaxPathSum(int& self,BiTree root,int Sum)
{
	if (root == NULL) return self;
    if ((root->lchild != NULL) && (root->rchild != NULL)){
			MaxPathSum(self,root->lchild, Sum + root->data.key);
            MaxPathSum(self,root->rchild, Sum + root->data.key);
		}           
    else if ((root->lchild != NULL) && (root->rchild == NULL))
            MaxPathSum(self,root->lchild, Sum + root->data.key);
    else if ((root->lchild == NULL) &&(root->rchild != NULL))
            MaxPathSum(self,root->rchild, Sum + root->data.key);
	else{
			if ((Sum + root->data.key) > self)
                self = Sum + root->data.key;
		} 
	return OK;    
}

//使用递归查找 , 如果有一个节点与根节点匹配 , 那么直接返回根节点 , 否则依次在左子树和右子树中查找 ,
//并且用left和right分别记录左子树的返回值和右子树的返回值 , 如果节点都存在左子树中 , 那么right就一
//定为NULL , 只需要返回 left , 如果节点都存在右子树中那么直接返回 right , 如果left和right都为空 返回NULL ;
BiTNode* LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2)
{
	struct BiTNode* left = NULL;
    struct BiTNode* right = NULL;
	struct BiTNode* p=LocateNode(T,e1);
	struct BiTNode* q=LocateNode(T,e2);
    if(T == NULL)
    {
        return NULL;
    }
    if(p == T || q == T)
    {
        return T;
    }

    left = LowestCommonAncestor(T->lchild, e1, e2);
    right = LowestCommonAncestor(T->rchild, e1, e2);

    if(NULL == left)
    {
        return right;
    }
    if(NULL == right)
    {
        return left;
    }
    return T;
}

void InvertTree(BiTree &T)
{
	if(T==NULL) return ;
	BiTree p=T->lchild;
	T->lchild=T->rchild;
	T->rchild=p;
	InvertTree(T->lchild);
	InvertTree(T->rchild);
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
	FILE* fp;
	if ((fp = fopen(FileName, "w+")) == NULL) {
		printf("File open erroe\n ");
		return ERROR;
	};//文件写入失败
	BiTNode* stack[100], * now = T;
	int top = 0;
	stack[0] = (BiTNode*)malloc(sizeof(BiTNode));
	stack[0]->lchild = stack[0]->rchild = NULL;
	while (top > 0 || now) {//输出带空结点的二叉树前序遍历序列
		if (now) {
			fprintf(fp, "%d %s ", now->data.key, now->data.others);
			top++;
			stack[top] = now;
			now = now->lchild;
		}
		else {
			fprintf(fp, "0 null ");
			now = stack[top--]->rchild;
		}
	}//while
	fprintf(fp, "0 null -1 null ");
	fclose(fp);
	return OK;
}
status LoadBiTree(BiTree& T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
	if (NULL != T) return INFEASIBLE;
	FILE* fp;
	if ((fp = fopen(FileName, "r+")) == NULL) {
		printf("File open erroe\n ");
		exit(-1);
	};//文件打开失败
	TElemType definition[100];
	int q = 0;
	do {//将带空结点的二叉树前序遍历序列存进definition
		fscanf(fp, "%d %s ", &definition[q].key, definition[q].others);
	} while (definition[q++].key != -1);
	fclose(fp);
	if (OK == CreateBiTree(T, definition,i))//创建二叉树
		return OK;
	return 0;
}


void BITREES()//多二叉树操作 
{ 
	BiTrees Lists;
	TElemType definition[100];
    int n,e,op=100,ans,i;
    char name[30];
    Lists.length=0;
    printf("请输入要创建的二叉树个数\n");
	scanf("%d", &n);
	while(n--)
   {
    	i=0;
		printf("请输入二叉树名字\n");
		scanf("%s",name);
   		AddBiTree(Lists,name);
   		printf("以前序遍历输入二叉树各结点数据，以“-1 null“结束\n");
		do {
		    scanf("%d %s",&definition[i].key,definition[i].others);
			} while (definition[i++].key!=-1);
    	ans=CreateBiTree(Lists.elem[Lists.length-1].T,definition,i);
		 if (ans==OK){
  			  printf("二叉树创建成功！\n");
			}
		 else if(ans==ERROR){
			  printf("关键字不唯一！创建失败！\n");
			  RemoveBiTree(Lists,name);
		 }
		 memset(definition,0,100);
		 getchar();getchar();
   }
	printf("1.增加新二叉树 2.移除一棵二叉树 3.查找二叉树 4.前中后序遍历全二叉树 5.对特定树操作 0.返回上级\n");
	printf("输入您的选项\n");
	while(op){
	 	system("cls");	printf("\n\n");
	 	printf("1.增加新二叉树 2.移除一棵二叉树 3.查找二叉树 4.前中后序遍历全二叉树 5.对特定树操作 0.返回上级\n");
	 	printf("输入您的选项\n");
	 	scanf("%d",&op);
	 	switch(op){
	 		case 1:
	 			printf("请输入要创建的二叉树个数\n");
				scanf("%d", &n);
				while(n--)
  				{
    				i=0;
					printf("请输入二叉树名字\n");
					scanf("%s",name);
   					AddBiTree(Lists,name);
   					printf("以前序遍历输入二叉树各结点数据，以“-1 null“结束\n");
					do {
					    scanf("%d %s",&definition[i].key,definition[i].others);
						} while (definition[i++].key!=-1);
   			 		ans=CreateBiTree(Lists.elem[Lists.length-1].T,definition,i);
					if (ans==OK){
  						  printf("二叉树创建成功！\n");
						}
					else if(ans==ERROR){
						  printf("关键字不唯一！创建失败！\n");
						  RemoveBiTree(Lists,name);
						}
					memset(definition,0,100);
					getchar();getchar();
 				}
  				getchar();getchar();
		 		break;
	   		case 2:
	   			printf("请输入要删除的二叉树名字\n");
				scanf("%s",name);
	   			if (RemoveBiTree(Lists,name)==OK) printf("删除成功"); 
   				else printf("删除失败");
   				getchar();getchar();
		 		break;
	   		case 3:
	   			printf("请输入要查找的二叉树名字\n");
				scanf("%s",name);
	   			if (n=LocateBiTree(Lists,name))
   				{
   					printf("%s",Lists.elem[n-1].name);
					putchar('\n');
   					PreOrderTraverse(Lists.elem[n-1].T,visit);
					putchar('\n');
					InOrderTraverse(Lists.elem[n-1].T,visit);
					putchar('\n');
					PostOrderTraverse(Lists.elem[n-1].T,visit);
         			putchar('\n');
   				}
   				else printf("查找失败");
   				getchar();getchar();
		 		break;
		 	case 4:
		 		printfBiTrees(Lists);
		 		getchar();getchar();
		 		break;
		 	case 5:
		 		printf("请输入要操作的二叉树名字\n");
				scanf("%s",name);
		 		if (n=LocateBiTree(Lists,name))
   				{
   					_BITREES(Lists,n-1);
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

status AddBiTree(BiTrees &Lists,char ListName[])
{
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.length++;
	return OK;
}

status RemoveBiTree(BiTrees &Lists,char ListName[])
// Lists中删除一个名称为ListName的二叉树
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

int LocateBiTree(BiTrees Lists,char ListName[])
// 在Lists中查找一个名称为ListName的二叉树，成功返回逻辑序号，否则返回0
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

void printfBiTrees(BiTrees Lists)
{
	for(int n=0;n<Lists.length;n++)
   {
   		printf("%s",Lists.elem[n].name);
		putchar('\n');
   		PreOrderTraverse(Lists.elem[n].T,visit);
		putchar('\n');
		InOrderTraverse(Lists.elem[n].T,visit);
		putchar('\n');
		PostOrderTraverse(Lists.elem[n].T,visit);
        putchar('\n');
   }
}

void _BITREES(BiTrees Lists,int n)
{
	TElemType value,c;
	BiTree p=NULL;
	int ans,e,self=0,Sum=0,op=100,e1,e2;
	int LR;
	char filename[50]; 
	while(op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  0.  Back             10. PreOrderTraverse\n");
		printf("    	  1.  DestroyBiTree    11. InOrderTraverse\n");
		printf("    	  2.  ClearBiTree      12. PostOrderTraverse\n");
		printf("    	  3.  BiTreeEmpty      13. LevelOrderTraverse\n");
		printf("    	  4.  BiTreeDepth      14. MaxPathSum\n");
		printf("    	  5.  LocateNode       15. LowestCommonAncestor\n");
		printf("    	  6.  Assign           16. InvertTree\n");
		printf("    	  7.  GetSibling       17. SaveBiTree\n");
		printf("    	  8.  InsertNode       18. LoadBiTree\n");
		printf("    	  9. DeleteNode       \n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~18]:");
		scanf("%d",&op);
    switch(op){
       case 0:
         break;
	   case 1:
	     if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 ans=DestroyBiTree(Lists.elem[n].T);
         if (ans==OK) printf("成功销毁二叉树");
         else printf("错误释放元素空间"); 
		 getchar();getchar();
		 break;
	   case 2:
	     if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 ans=ClearBiTree(Lists.elem[n].T);
		 if (ans==OK) printf("成功清空二叉树");
	  	 else printf("错误释放元素空间");  
	 	 getchar();getchar();
		 break;
	   case 3:
		 ans=BiTreeEmpty(Lists.elem[n].T);
		 if (ans==TRUE) printf("二叉树为空树");
	     else if (ans==ERROR) printf("二叉树不为空！");
		 getchar();getchar();
		 break;
	   case 4:
	     if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 ans=BiTreeDepth(Lists.elem[n].T); 
		 printf("二叉树的深度为%d", ans);
		 getchar();getchar();
		 break;
	   case 5:
	     if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("请输入要查找的结点的关键字\n"); 
		 scanf("%d",&e);    
		 p=LocateNode(Lists.elem[n].T,e);
		 if (p) printf("查找成功！结点数据为%d,%s",p->data.key,p->data.others); 
		 else printf("查无此结点！");
	 	 getchar();getchar();
		 break;
	   case 6: 
		 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("依次输入要赋值结点的关键字和要赋值的数据\n");
		 scanf("%d %d %s",&e,&value.key,value.others);
		 ans=Assign(Lists.elem[n].T,e,value);
		 if (ans==OK) printf("赋值操作成功");
		 if (ans==ERROR) printf("赋值操作失败，原因：查无具有该关键字的结点");
		 if (ans==13) printf("赋值操作失败，原因：关键字发生重复");
		 getchar();getchar();
		 break;
	   case 7: 
		 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("请输入结点关键字以查找其兄弟结点\n"); 
		 scanf("%d",&e);    
		 p=GetSibling(Lists.elem[n].T,e);
		 if (p) printf("查找成功！兄弟结点数据为%d,%s",p->data.key,p->data.others); 
		 else printf("无兄弟结点！");
		 getchar();getchar();
		 break;
	   case 8:   
		 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("依次输入要插入结点位置的关键字,左右子树选择（左0右1，-1为作为根节点插入）以及结点的数据\n");
		 scanf("%d %d %d %s",&e,&LR,&c.key,c.others);
		 ans=InsertNode(Lists.elem[n].T,e,LR,c);
		 if (ans==OK) printf("插入操作成功");
		 if (ans==ERROR) printf("插入操作失败，原因：查无具有该关键字的结点");
		 if (ans==13) printf("插入操作失败，原因：关键字发生重复");
		 getchar();getchar();
		 break;
	   case 9:
	   	 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("请输入要删除的结点的关键字\n"); 
		 scanf("%d",&e);
		 ans=DeleteNode(Lists.elem[n].T,e);
		 if (ans==OK ) printf("删除操作成功");
		 else printf("删除操作失败，查无此结点！");
		 getchar();getchar();
		 break;
	   case 10:
		 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 PreOrderTraverse(Lists.elem[n].T,visit);
		 getchar();getchar();
		 break;
	   case 11:
		 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 InOrderTraverse(Lists.elem[n].T,visit);
		 getchar();getchar();
		 break;
	   case 12:
	   	 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 PostOrderTraverse(Lists.elem[n].T,visit);
	   	 getchar();getchar();
		 break;
	   case 13:
	   	 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 LevelOrderTraverse(Lists.elem[n].T,visit);
	   	 getchar();getchar();
		 break;	
	   case 14:
	     if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 ans=MaxPathSum(self,Lists.elem[n].T,Sum);
	   	 printf("根节点到叶子结点的最大路径和为%d\n",self);
	   	 getchar();getchar();
		 break;	
	   case 15:
	   	 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 printf("请输入两个结点的关键字\n");
		 scanf("%d %d",&e1,&e2);
		 p=LowestCommonAncestor(Lists.elem[n].T,e1,e2);
		 if (p) printf("查找成功！最近公共祖先结点数据为%d,%s",p->data.key,p->data.others);
		 else printf("无公共祖先！");
	   	 getchar();getchar();
		 break;	
	   case 16:
	   	 if(!Lists.elem[n].T){
			 printf("二叉树不存在！\n");
			 getchar();getchar();
			 break;
		 }
		 InvertTree(Lists.elem[n].T);
		 printf("二叉树翻转成功！");
	   	 getchar();getchar();
		 break;	
	   case 17:
		 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 ans=SaveBiTree(Lists.elem[n].T,filename);
	   	  if (ans==INFEASIBLE) printf("二叉树不存在"); 
		 else if(ans==OK) printf("写入文件完成");
	   	 getchar();getchar();
		 break;	 
	   case 18:
	   	 printf("请输入文件名\n");
		 scanf("%s",filename);  
	   	 ans=LoadBiTree(Lists.elem[n].T,filename);
	   	 if(ans==INFEASIBLE) printf("二叉树已存在"); 
		 else if(ans==OK) printf("读入文件完成");
	   	 getchar();getchar();
		 break;	
		}
	}
}
