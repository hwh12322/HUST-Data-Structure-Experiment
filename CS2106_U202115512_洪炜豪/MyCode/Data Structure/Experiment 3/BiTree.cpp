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

//���� 1 a 2 b 0 null 0 null 3 c 4 d 0 null 0 null 5 e 0 null 0 null -1 null
//���� 1 a 2 b 3 c 0 null 0 null 0 null 0 null -1 null
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
	} TElemType; //������������Ͷ���

typedef struct BiTNode{  //����������Ķ���
	      TElemType  data;
	      struct BiTNode *lchild,*rchild;
	} BiTNode, *BiTree;

typedef struct moretrees{  //��������Ĺ������
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
//���Ӻ��� 
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
		printf("    ��ѡ����Ĳ���[0~20]:");
		scanf("%d",&op);
    switch(op){
       case 0:
         break;
	   case 1:
	     if(T){
			 printf("�������Ѵ��ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 i=0;
		 printf("��ǰ����������������������ݣ��ԡ�-1 null������\n");
		 do {
		    scanf("%d %s",&definition[i].key,definition[i].others);
			} while (definition[i++].key!=-1);
		 ans=CreateBiTree(T,definition,i);
		 if (ans==OK){
  			  printf("�����������ɹ���\n");
			}
		 else if(ans==ERROR){
			  printf("�ؼ��ֲ�Ψһ������ʧ�ܣ�\n");
		 }
		 getchar();getchar();
		 break;
	   case 2:
	     if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 ans=DestroyBiTree(T);
         if (ans==OK) printf("�ɹ����ٶ�����");
         else printf("�����ͷ�Ԫ�ؿռ�"); 
		 memset(definition, 0, 100); 
		 getchar();getchar();
		 break;
	   case 3:
	     if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 ans=ClearBiTree(T);
		 if (ans==OK) printf("�ɹ���ն�����");
	  	 else printf("�����ͷ�Ԫ�ؿռ�");  
		 memset(definition, 0, 100);  
	 	 getchar();getchar();
		 break;
	   case 4:
		 ans=BiTreeEmpty(T);
		 if (ans==TRUE) printf("������Ϊ����");
	     else if (ans==ERROR) printf("��������Ϊ�գ�");
		 getchar();getchar();
		 break;
	   case 5:
	     if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 ans=BiTreeDepth(T); 
		 printf("�����������Ϊ%d", ans);
		 getchar();getchar();
		 break;
	   case 6:
	     if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("������Ҫ���ҵĽ��Ĺؼ���\n"); 
		 scanf("%d",&e);    
		 p=LocateNode(T,e);
		 if (p) printf("���ҳɹ����������Ϊ%d,%s",p->data.key,p->data.others); 
		 else printf("���޴˽�㣡");
	 	 getchar();getchar();
		 break;
	   case 7: 
		 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("��������Ҫ��ֵ���Ĺؼ��ֺ�Ҫ��ֵ������\n");
		 scanf("%d %d %s",&e,&value.key,value.others);
		 ans=Assign(T,e,value);
		 if (ans==OK) printf("��ֵ�����ɹ�");
		 if (ans==ERROR) printf("��ֵ����ʧ�ܣ�ԭ�򣺲��޾��иùؼ��ֵĽ��");
		 if (ans==13) printf("��ֵ����ʧ�ܣ�ԭ�򣺹ؼ��ַ����ظ�");
		 getchar();getchar();
		 break;
	   case 8: 
		 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("��������ؼ����Բ������ֵܽ��\n"); 
		 scanf("%d",&e);    
		 p=GetSibling(T,e);
		 if (p) printf("���ҳɹ����ֵܽ������Ϊ%d,%s",p->data.key,p->data.others); 
		 else printf("���ֵܽ�㣡");
		 getchar();getchar();
		 break;
	   case 9:   
		 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("��������Ҫ������λ�õĹؼ���,��������ѡ����0��1��-1Ϊ��Ϊ���ڵ���룩�Լ���������\n");
		 scanf("%d %d %d %s",&e,&LR,&c.key,c.others);
		 ans=InsertNode(T,e,LR,c);
		 if (ans==OK) printf("��������ɹ�");
		 if (ans==ERROR) printf("�������ʧ�ܣ�ԭ�򣺲��޾��иùؼ��ֵĽ��");
		 if (ans==13) printf("�������ʧ�ܣ�ԭ�򣺹ؼ��ַ����ظ�");
		 getchar();getchar();
		 break;
	   case 10:
	   	 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("������Ҫɾ���Ľ��Ĺؼ���\n"); 
		 scanf("%d",&e);
		 ans=DeleteNode(T,e);
		 if (ans==OK ) printf("ɾ�������ɹ�");
		 else printf("ɾ������ʧ�ܣ����޴˽�㣡");
		 getchar();getchar();
		 break;
	   case 11:
		 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 PreOrderTraverse(T,visit);
		 getchar();getchar();
		 break;
	   case 12:
		 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 InOrderTraverse(T,visit);
		 getchar();getchar();
		 break;
	   case 13:
	   	 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 PostOrderTraverse(T,visit);
	   	 getchar();getchar();
		 break;
	   case 14:
	   	 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 LevelOrderTraverse(T,visit);
	   	 getchar();getchar();
		 break;	
	   case 15:
	     if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 ans=MaxPathSum(self,T,Sum);
	   	 printf("���ڵ㵽Ҷ�ӽ������·����Ϊ%d\n",self);
	   	 getchar();getchar();
		 break;	
	   case 16:
	   	 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("�������������Ĺؼ���\n");
		 scanf("%d %d",&e1,&e2);
		 p=LowestCommonAncestor(T,e1,e2);
		 if (p) printf("���ҳɹ�������������Ƚ������Ϊ%d,%s",p->data.key,p->data.others);
		 else printf("�޹������ȣ�");
	   	 getchar();getchar();
		 break;	
	   case 17:
	   	 if(!T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 InvertTree(T);
		 printf("��������ת�ɹ���");
	   	 getchar();getchar();
		 break;	
	   case 18:
		 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 ans=SaveBiTree(T,filename);
	   	  if (ans==INFEASIBLE) printf("������������"); 
		 else if(ans==OK) printf("д���ļ����");
	   	 getchar();getchar();
		 break;	 
	   case 19:
	   	 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 ans=LoadBiTree(T,filename);
	   	 if(ans==INFEASIBLE) printf("�������Ѵ���"); 
		 else if(ans==OK) printf("�����ļ����");
	   	 getchar();getchar();
		 break;	
	   case 20:
	     BITREES();
	 	}
    }
}


BiTNode* Parent(BiTree T,BiTree p)
{/*������֪�ڵ��󸸽ڵ�ĺ��Ĵ���*/
    if(T==NULL||T==p||p==NULL){/*T==p˵��p�Ǹ��ڵ㣬����û�и��ڵ�*/
    	return NULL;
	}
	if(T->lchild==p||T->rchild==p){/*�ڵݹ�����г����ڵ���������нڵ��ܻ��ȱ���������һ�Σ�����T==Pֻ���ڸ��ڵ㴦���ܱ��ɹ�����*/
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
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	if (jiance(definition)==0) return ERROR;
	BiTree ans;
	ans = (BiTree)malloc(sizeof(BiTNode));
	T = ans;
	memset(num, 0, 1000);//numȫ����0
	if (definition[0].key == 0|| definition[0].key == -1) {
		T = NULL;
		return OK;
	}//�����Ϊ�յĿն�����
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
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
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
//�������T�����
{
    if(T==NULL) return 0; 
    else{
         return 1 + max(BiTreeDepth(T->lchild),BiTreeDepth(T->rchild));
    }
}

BiTNode* LocateNode(BiTree root,KeyType value)
//���ҽ��
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
//Ψһ���ж�
{
    if(T==NULL) return ;
    if(e==T->data.key){
        i++;
    }
    LocateNode1(T->lchild,e,i);
    LocateNode1(T->rchild,e,i);
}

status Assign(BiTree &T,KeyType e,TElemType value)
//ʵ�ֽ�㸳ֵ��
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
//ʵ�ֻ���ֵܽ��
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
//������
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
//���Ҹ����
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
//ɾ�����
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
    while (p || !s.empty())				//����ѭ������p��ջ��Ϊ��ʱΪ����ѭ����־;
	{
		if (p) {						//���p���ǿ�;
			visit(p);
			s.push(p);					//��p�����ջ��Ϊ���Ǳ���p������������λ��;
			p = p->lchild;				//����p����������;
		}
		else {
			p = s.top()->rchild;		//���pΪ��,˵���ϸ������������ǿյģ���ʱ��Ҫ�����ϸ��ڵ��������;
			s.pop();					//����ջ��Ԫ�أ����ϸ��ڵ�;
		}
	}
}

void InOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    if (T)
    {
        InOrderTraverse(T->lchild,visit);
        visit(T);
        InOrderTraverse(T->rchild,visit);
    }
}

void PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    if (T)
    {
        PostOrderTraverse(T->lchild,visit);
        PostOrderTraverse(T->rchild,visit);
        visit(T);
    }
}

int front=0,rear=0;
//��Ӻ���
void EnQueue(BiTree *a,BiTree node){
    a[rear++]=node;
}
//���Ӻ���
BiTNode* DeQueue(BiTNode** a){
    return a[front++];
}
void LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
	BiTNode * p;
    //����˳����У���ʼ��������������
    BiTree a[20];
    //��������
    EnQueue(a, T);
    //����ͷ�Ͷ�β���ʱ����ʾ����Ϊ��
    while(front<rear) {
        //��ͷ������
        p=DeQueue(a);
        visit(p);
        //����ͷ�������Һ����������
        if (p->lchild!=NULL) {
            EnQueue(a, p->lchild);
        }
        if (p->rchild!=NULL) {
            EnQueue(a, p->rchild);
        }
    }
}

//���ӹ���//
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

//ʹ�õݹ���� , �����һ���ڵ�����ڵ�ƥ�� , ��ôֱ�ӷ��ظ��ڵ� , �������������������������в��� ,
//������left��right�ֱ��¼�������ķ���ֵ���������ķ���ֵ , ����ڵ㶼������������ , ��ôright��һ
//��ΪNULL , ֻ��Ҫ���� left , ����ڵ㶼��������������ôֱ�ӷ��� right , ���left��right��Ϊ�� ����NULL ;
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
//���������Ľ������д�뵽�ļ�FileName��
{
	FILE* fp;
	if ((fp = fopen(FileName, "w+")) == NULL) {
		printf("File open erroe\n ");
		return ERROR;
	};//�ļ�д��ʧ��
	BiTNode* stack[100], * now = T;
	int top = 0;
	stack[0] = (BiTNode*)malloc(sizeof(BiTNode));
	stack[0]->lchild = stack[0]->rchild = NULL;
	while (top > 0 || now) {//������ս��Ķ�����ǰ���������
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
//�����ļ�FileName�Ľ�����ݣ�����������
{
	if (NULL != T) return INFEASIBLE;
	FILE* fp;
	if ((fp = fopen(FileName, "r+")) == NULL) {
		printf("File open erroe\n ");
		exit(-1);
	};//�ļ���ʧ��
	TElemType definition[100];
	int q = 0;
	do {//�����ս��Ķ�����ǰ��������д��definition
		fscanf(fp, "%d %s ", &definition[q].key, definition[q].others);
	} while (definition[q++].key != -1);
	fclose(fp);
	if (OK == CreateBiTree(T, definition,i))//����������
		return OK;
	return 0;
}


void BITREES()//����������� 
{ 
	BiTrees Lists;
	TElemType definition[100];
    int n,e,op=100,ans,i;
    char name[30];
    Lists.length=0;
    printf("������Ҫ�����Ķ���������\n");
	scanf("%d", &n);
	while(n--)
   {
    	i=0;
		printf("���������������\n");
		scanf("%s",name);
   		AddBiTree(Lists,name);
   		printf("��ǰ����������������������ݣ��ԡ�-1 null������\n");
		do {
		    scanf("%d %s",&definition[i].key,definition[i].others);
			} while (definition[i++].key!=-1);
    	ans=CreateBiTree(Lists.elem[Lists.length-1].T,definition,i);
		 if (ans==OK){
  			  printf("�����������ɹ���\n");
			}
		 else if(ans==ERROR){
			  printf("�ؼ��ֲ�Ψһ������ʧ�ܣ�\n");
			  RemoveBiTree(Lists,name);
		 }
		 memset(definition,0,100);
		 getchar();getchar();
   }
	printf("1.�����¶����� 2.�Ƴ�һ�ö����� 3.���Ҷ����� 4.ǰ�к������ȫ������ 5.���ض������� 0.�����ϼ�\n");
	printf("��������ѡ��\n");
	while(op){
	 	system("cls");	printf("\n\n");
	 	printf("1.�����¶����� 2.�Ƴ�һ�ö����� 3.���Ҷ����� 4.ǰ�к������ȫ������ 5.���ض������� 0.�����ϼ�\n");
	 	printf("��������ѡ��\n");
	 	scanf("%d",&op);
	 	switch(op){
	 		case 1:
	 			printf("������Ҫ�����Ķ���������\n");
				scanf("%d", &n);
				while(n--)
  				{
    				i=0;
					printf("���������������\n");
					scanf("%s",name);
   					AddBiTree(Lists,name);
   					printf("��ǰ����������������������ݣ��ԡ�-1 null������\n");
					do {
					    scanf("%d %s",&definition[i].key,definition[i].others);
						} while (definition[i++].key!=-1);
   			 		ans=CreateBiTree(Lists.elem[Lists.length-1].T,definition,i);
					if (ans==OK){
  						  printf("�����������ɹ���\n");
						}
					else if(ans==ERROR){
						  printf("�ؼ��ֲ�Ψһ������ʧ�ܣ�\n");
						  RemoveBiTree(Lists,name);
						}
					memset(definition,0,100);
					getchar();getchar();
 				}
  				getchar();getchar();
		 		break;
	   		case 2:
	   			printf("������Ҫɾ���Ķ���������\n");
				scanf("%s",name);
	   			if (RemoveBiTree(Lists,name)==OK) printf("ɾ���ɹ�"); 
   				else printf("ɾ��ʧ��");
   				getchar();getchar();
		 		break;
	   		case 3:
	   			printf("������Ҫ���ҵĶ���������\n");
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
   				else printf("����ʧ��");
   				getchar();getchar();
		 		break;
		 	case 4:
		 		printfBiTrees(Lists);
		 		getchar();getchar();
		 		break;
		 	case 5:
		 		printf("������Ҫ�����Ķ���������\n");
				scanf("%s",name);
		 		if (n=LocateBiTree(Lists,name))
   				{
   					_BITREES(Lists,n-1);
   				}
   				else{
   					printf("�ñ����ڣ�");
				   }
		 		getchar();getchar();
		 		break;
   			case 0:
        		 break;
    		default:
    			printf("������������������");
    			
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
// Lists��ɾ��һ������ΪListName�Ķ�����
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
// ��Lists�в���һ������ΪListName�Ķ��������ɹ������߼���ţ����򷵻�0
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
		printf("    ��ѡ����Ĳ���[0~18]:");
		scanf("%d",&op);
    switch(op){
       case 0:
         break;
	   case 1:
	     if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 ans=DestroyBiTree(Lists.elem[n].T);
         if (ans==OK) printf("�ɹ����ٶ�����");
         else printf("�����ͷ�Ԫ�ؿռ�"); 
		 getchar();getchar();
		 break;
	   case 2:
	     if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 ans=ClearBiTree(Lists.elem[n].T);
		 if (ans==OK) printf("�ɹ���ն�����");
	  	 else printf("�����ͷ�Ԫ�ؿռ�");  
	 	 getchar();getchar();
		 break;
	   case 3:
		 ans=BiTreeEmpty(Lists.elem[n].T);
		 if (ans==TRUE) printf("������Ϊ����");
	     else if (ans==ERROR) printf("��������Ϊ�գ�");
		 getchar();getchar();
		 break;
	   case 4:
	     if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 ans=BiTreeDepth(Lists.elem[n].T); 
		 printf("�����������Ϊ%d", ans);
		 getchar();getchar();
		 break;
	   case 5:
	     if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("������Ҫ���ҵĽ��Ĺؼ���\n"); 
		 scanf("%d",&e);    
		 p=LocateNode(Lists.elem[n].T,e);
		 if (p) printf("���ҳɹ����������Ϊ%d,%s",p->data.key,p->data.others); 
		 else printf("���޴˽�㣡");
	 	 getchar();getchar();
		 break;
	   case 6: 
		 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("��������Ҫ��ֵ���Ĺؼ��ֺ�Ҫ��ֵ������\n");
		 scanf("%d %d %s",&e,&value.key,value.others);
		 ans=Assign(Lists.elem[n].T,e,value);
		 if (ans==OK) printf("��ֵ�����ɹ�");
		 if (ans==ERROR) printf("��ֵ����ʧ�ܣ�ԭ�򣺲��޾��иùؼ��ֵĽ��");
		 if (ans==13) printf("��ֵ����ʧ�ܣ�ԭ�򣺹ؼ��ַ����ظ�");
		 getchar();getchar();
		 break;
	   case 7: 
		 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("��������ؼ����Բ������ֵܽ��\n"); 
		 scanf("%d",&e);    
		 p=GetSibling(Lists.elem[n].T,e);
		 if (p) printf("���ҳɹ����ֵܽ������Ϊ%d,%s",p->data.key,p->data.others); 
		 else printf("���ֵܽ�㣡");
		 getchar();getchar();
		 break;
	   case 8:   
		 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("��������Ҫ������λ�õĹؼ���,��������ѡ����0��1��-1Ϊ��Ϊ���ڵ���룩�Լ���������\n");
		 scanf("%d %d %d %s",&e,&LR,&c.key,c.others);
		 ans=InsertNode(Lists.elem[n].T,e,LR,c);
		 if (ans==OK) printf("��������ɹ�");
		 if (ans==ERROR) printf("�������ʧ�ܣ�ԭ�򣺲��޾��иùؼ��ֵĽ��");
		 if (ans==13) printf("�������ʧ�ܣ�ԭ�򣺹ؼ��ַ����ظ�");
		 getchar();getchar();
		 break;
	   case 9:
	   	 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("������Ҫɾ���Ľ��Ĺؼ���\n"); 
		 scanf("%d",&e);
		 ans=DeleteNode(Lists.elem[n].T,e);
		 if (ans==OK ) printf("ɾ�������ɹ�");
		 else printf("ɾ������ʧ�ܣ����޴˽�㣡");
		 getchar();getchar();
		 break;
	   case 10:
		 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 PreOrderTraverse(Lists.elem[n].T,visit);
		 getchar();getchar();
		 break;
	   case 11:
		 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 InOrderTraverse(Lists.elem[n].T,visit);
		 getchar();getchar();
		 break;
	   case 12:
	   	 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 PostOrderTraverse(Lists.elem[n].T,visit);
	   	 getchar();getchar();
		 break;
	   case 13:
	   	 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 LevelOrderTraverse(Lists.elem[n].T,visit);
	   	 getchar();getchar();
		 break;	
	   case 14:
	     if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 ans=MaxPathSum(self,Lists.elem[n].T,Sum);
	   	 printf("���ڵ㵽Ҷ�ӽ������·����Ϊ%d\n",self);
	   	 getchar();getchar();
		 break;	
	   case 15:
	   	 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 printf("�������������Ĺؼ���\n");
		 scanf("%d %d",&e1,&e2);
		 p=LowestCommonAncestor(Lists.elem[n].T,e1,e2);
		 if (p) printf("���ҳɹ�������������Ƚ������Ϊ%d,%s",p->data.key,p->data.others);
		 else printf("�޹������ȣ�");
	   	 getchar();getchar();
		 break;	
	   case 16:
	   	 if(!Lists.elem[n].T){
			 printf("�����������ڣ�\n");
			 getchar();getchar();
			 break;
		 }
		 InvertTree(Lists.elem[n].T);
		 printf("��������ת�ɹ���");
	   	 getchar();getchar();
		 break;	
	   case 17:
		 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 ans=SaveBiTree(Lists.elem[n].T,filename);
	   	  if (ans==INFEASIBLE) printf("������������"); 
		 else if(ans==OK) printf("д���ļ����");
	   	 getchar();getchar();
		 break;	 
	   case 18:
	   	 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 ans=LoadBiTree(Lists.elem[n].T,filename);
	   	 if(ans==INFEASIBLE) printf("�������Ѵ���"); 
		 else if(ans==OK) printf("�����ļ����");
	   	 getchar();getchar();
		 break;	
		}
	}
}
