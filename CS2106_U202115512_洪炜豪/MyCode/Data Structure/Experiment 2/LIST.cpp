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
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct LIST{  //������Ĺ������
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
//���Ӻ��� 
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
		printf("    ��ѡ����Ĳ���[0~18]:");
		scanf("%d",&op);
    switch(op){
       case 0:
         break;
	   case 1:
		 if(InitList(L)==OK) printf("���Ա����ɹ���\n");
		     else printf("���Ա���ʧ�ܣ�\n");
		 getchar();getchar();
		 break;
	   case 2:
		 j=DestroyList(L);
		if (j==INFEASIBLE) printf("���Ա����ڣ�");
        if (j==OK) printf("�ɹ��ͷ����Ա�ռ�");
        else printf("�����ͷ�Ԫ�ؿռ�");    
		 getchar();getchar();
		 break;
	   case 3:
		j=ClearList(L);
		if (j==INFEASIBLE) printf("���Ա����ڣ�");
		if (j==OK) printf("�ɹ�������Ա�L");
		else printf("�����ͷ�Ԫ�ؿռ�");    
		getchar();getchar();
		break;
	   case 4:
		 j=ListEmpty(L);
		if (j==OK) printf("���Ա�L����Ϊ0");
		else if (j==ERROR) printf("���Ա�L����Ϊ��Ϊ0");
		else if (j==INFEASIBLE) printf("���Ա����ڣ�");
		else printf("δ��ȷ�п�");
		 getchar();getchar();
		 break;
	   case 5:
		 j=ListLength(L); 
		if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		else printf("���Ա�L�ĳ���Ϊ%d", j);
		 getchar();getchar();
		 break;
	   case 6:
		 printf("������Ҫ��ȡԪ�ص�Ԫ���߼����\n"); 
		 scanf("%d",&i);    
		 j=GetElem(L,i,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		else if(j==OK) printf("Ԫ�ص�ֵΪ%d",e);
		else if(j==ERROR) printf("Ԫ���߼���Ų��Ϸ�");
		getchar();getchar();
		 break;
	   case 7: 
		 printf("������Ҫ����Ԫ�ص�ֵe\n"); 
		 scanf("%d",&e);  
		 j=LocateElem(L,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(j==ERROR) printf("û���ҵ�ָ����Ԫ�أ�����ʧ��");
		 else printf("���ҳɹ���Ԫ���߼����Ϊ%d",j);
		 getchar();getchar();
		 break;
	   case 8: 
		 printf("������ָ��Ԫ�ص�ֵe\n");
		 scanf("%d",&e);  
		 j=PriorElem(L,e,pre); 
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(j==ERROR) printf("û���ҵ�ָ��Ԫ��");
		 else if(j==12) printf("ָ��Ԫ�ش��ڣ�ǰ��������");
		 else if(j==OK) printf("ǰ��Ԫ�ص�ֵΪ%d",pre);
		 getchar();getchar();
		 break;
	   case 9:   
		 printf("������ָ��Ԫ�ص�ֵe\n");
		 scanf("%d",&e);
		 j=NextElem(L,e,next);  
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(j==ERROR) printf("û���ҵ�ָ��Ԫ��");
		 else if(j==13) printf("ָ��Ԫ�ش��ڣ���̲�����");
		 else if(j==OK) printf("���Ԫ�ص�ֵΪ%d",next);
		 getchar();getchar();
		 break;
	   case 10:
	   	if (L==NULL){
	   		printf("���Ա����ڣ�"); 
	   		getchar();getchar();
		 break;
		   }
		 printf("����������λ��i\n");
		 scanf("%d",&i);  
		 printf("���������Ԫ�ص�ֵe\n");
		 scanf("%d",&e);
		 j=ListInsert(L,i,e); 
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		if (j!=INFEASIBLE) {
		 	printf("%s\n", j==OK? "����ɹ�" : j==ERROR? "����ʧ��" : "�������");
		 getchar();getchar();
		 break;
	   case 11:
		 printf("������ɾ����λ��i\n");
		 scanf("%d",&i);
		 j=ListDelete(L,i,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 if(j==ERROR) printf("ɾ��ʧ�ܣ������ڵ�%d��Ԫ�أ�\n",i);
		 if(j==OK) printf("ɾ���ɹ�����ɾ��Ԫ�ص�ֵΪ%d\n",e);
		 getchar();getchar();
		 break;
	   case 12:
		 j=ListTraverse(L);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 if(j==OK && !L->next) printf("�����Ա�\n");
		getchar();getchar();
		 break;
	   case 13:
	   	 j=reverseList(L);
	   	  if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else printf("����ת�ɹ�!");
	   	 getchar();getchar();
		 break;
	   case 14:
	   	 printf("������Ҫɾ�����ǵ����ڼ������\n");
		 scanf("%d",&n);    
	   	 j=RemoveNthFromEnd(L,n,e);
	   	  if (j==INFEASIBLE) printf("���Ա����� "); 
	   	  if (L&&L->next==NULL) printf("���Ա�Ϊ�� "); 
		 else printf("ɾ���ɹ�����ɾ��Ԫ�ص�ֵΪ%d\n",e);
	   	 getchar();getchar();
		 break;	 
	   case 15:
	   	 j=sortList(L);
	   	  if (j==INFEASIBLE) printf("���Ա�L������ "); 
		 else printf("��С�����������");
	   	 getchar();getchar();
		 break;	
	   case 16:
		 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 j=SaveList(L,filename);
	   	  if (j==INFEASIBLE) printf("���Ա�L������"); 
		 else if(j==OK) printf("д���ļ����");
	   	 getchar();getchar();
		 break;	 
	   case 17:
	   	 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 j=LoadList(L,filename);
	   	 if(j==INFEASIBLE) printf("���Ա�L�Ѵ���"); 
		 else if(j==OK) printf("�����ļ����");
	   	 getchar();getchar();
		 break;	
	   case 18:
	   	 _LISTS();
    default:
    	printf("������������������");
	 	}
    }
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	}
}
status InitList(LinkList& L)//���Ա��ʼ�� 
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

//���ӹ���//
status reverseList(LinkList L)//����ת
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

status RemoveNthFromEnd(LinkList L,int n,ElemType &e)//ɾ������ĵ�����n�����
{
	if(L==NULL){
        return INFEASIBLE;
	}
	int length=ListLength(L);
	if(n<1||n>length) return ERROR;
	ListDelete(L,length-n+1,e);
	return OK;
}


status sortList(LinkList L)//��������
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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


void _LISTS()//�����Ա���� 
{ 
	LISTS Lists;
    int n,e,op=100;
    char name[30];
    Lists.length=0;
    printf("������Ҫ������˳������\n");
	scanf("%d", &n);
	while(n--)
   {
    	printf("���������\n");
		scanf("%s",name);
   		AddList(Lists,name);
   		printf("����Ԫ�أ��Իس�����\n");
    	do
  			{
     		scanf("%d",&e); 
			ListInsert(Lists.elem[Lists.length-1].L,ListLength(Lists.elem[Lists.length-1].L)+1,e); 
   			}while(getchar()!='\n');
   }
	printf("1.�����±� 2.�Ƴ�һ�����Ա� 3.�������Ա� 4.�鿴ȫ�� 5.���ض������ 0.�����ϼ�\n");
	printf("��������ѡ��\n");
	while(op){
	 	system("cls");	printf("\n\n");
	 	printf("1.�����±� 2.�Ƴ�һ�����Ա� 3.�������Ա� 4.�鿴ȫ�� 5.���ض������ 0.�����ϼ�\n");
	 	printf("��������ѡ��\n");
	 	scanf("%d",&op);
	 	switch(op){
	 		case 1:
	 			printf("������Ҫ������˳������\n");
				scanf("%d", &n);
				while(n--)
   				{
    				printf("���������\n");
					scanf("%s",name);
   					AddList(Lists,name);
   					printf("����Ԫ�أ��Իس�����\n");
    				do{
     				scanf("%d",&e); 
					ListInsert(Lists.elem[Lists.length-1].L,ListLength(Lists.elem[Lists.length-1].L)+1,e); 
   					}while(getchar()!='\n');
  				getchar();getchar();
		 		break;
	   		case 2:
	   			printf("������Ҫɾ���ı���\n");
				scanf("%s",name);
	   			if (RemoveList(Lists,name)==OK) printf("ɾ���ɹ�"); 
   				else printf("ɾ��ʧ��");
   				getchar();getchar();
		 		break;
	   		case 3:
	   			printf("������Ҫ���ҵı���\n");
				scanf("%s",name);
	   			if (n=LocateList(Lists,name))
   				{
   					printf("%s ",Lists.elem[n-1].name);
   					ListTraverse(Lists.elem[n-1].L);
         			putchar('\n');
   				}
   				else printf("����ʧ��");
   				getchar();getchar();
		 		break;
		 	case 4:
		 		printflist(Lists);
		 		getchar();getchar();
		 		break;
		 	case 5:
		 		printf("������Ҫ�����ı���\n");
				scanf("%s",name);
		 		if (n=LocateList(Lists,name))
   				{
   					__LISTS(Lists,n);
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
// Lists��ɾ��һ������ΪListName�����Ա�
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
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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
		printf("    ��ѡ����Ĳ���[0~16]:");
		scanf("%d",&op);
    switch(op){
	   case 1:
		 j=DestroyList(Lists.elem[Lists.length-1].L);
		if (j==INFEASIBLE) printf("���Ա����ڣ�");
        if (j==OK) printf("�ɹ��ͷ����Ա�ռ�");
        else printf("�����ͷ�Ԫ�ؿռ�");    
		 getchar();getchar();
		 break;
	   case 2:
		j=ClearList(Lists.elem[Lists.length-1].L);
		if (j==INFEASIBLE) printf("���Ա����ڣ�");
		if (j==OK) printf("�ɹ�������Ա�L");
		else printf("�����ͷ�Ԫ�ؿռ�");    
		getchar();getchar();
		break;
	   case 3:
		 j=ListEmpty(Lists.elem[Lists.length-1].L);
		if (j==OK) printf("���Ա�L����Ϊ0");
		else if (j==ERROR) printf("���Ա�L����Ϊ��Ϊ0");
		else if (j==INFEASIBLE) printf("���Ա����ڣ�");
		else printf("δ��ȷ�п�");
		 getchar();getchar();
		 break;
	   case 4:
		 j=ListLength(Lists.elem[Lists.length-1].L); 
		if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		else printf("���Ա�L�ĳ���Ϊ%d", j);
		 getchar();getchar();
		 break;
	   case 5:
		 printf("������Ҫ��ȡԪ�ص�Ԫ���߼����\n"); 
		 scanf("%d",&i);    
		 j=GetElem(Lists.elem[Lists.length-1].L,i,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		else if(j==OK) printf("Ԫ�ص�ֵΪ%d",e);
		else if(j==ERROR) printf("Ԫ���߼���Ų��Ϸ�");
		getchar();getchar();
		 break;
	   case 6: 
		 printf("������Ҫ����Ԫ�ص�ֵe\n"); 
		 scanf("%d",&e);  
		 j=LocateElem(Lists.elem[Lists.length-1].L,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(j==ERROR) printf("û���ҵ�ָ����Ԫ�أ�����ʧ��");
		 else printf("���ҳɹ���Ԫ���߼����Ϊ%d",j);
		 getchar();getchar();
		 break;
	   case 7: 
		 printf("������ָ��Ԫ�ص�ֵe\n");
		 scanf("%d",&e);  
		 j=PriorElem(Lists.elem[Lists.length-1].L,e,pre); 
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(j==ERROR) printf("û���ҵ�ָ��Ԫ��");
		 else if(j==12) printf("ָ��Ԫ�ش��ڣ�ǰ��������");
		 else if(j==OK) printf("ǰ��Ԫ�ص�ֵΪ%d",pre);
		 getchar();getchar();
		 break;
	   case 8:   
		 printf("������ָ��Ԫ�ص�ֵe\n");
		 scanf("%d",&e);
		 j=NextElem(Lists.elem[Lists.length-1].L,e,next);  
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(j==13) printf("ָ��Ԫ�ش��ڣ���̲�����");
		 else if(j==OK) printf("���Ԫ�ص�ֵΪ%d",next);
		 getchar();getchar();
		 break;
	   case 9:
	   	if (Lists.elem[Lists.length-1].L==NULL){
	   		printf("���Ա����ڣ�"); 
	   		getchar();getchar();
		 break;
		   }
		 printf("����������λ��i\n");
		 scanf("%d",&i);  
		 printf("���������Ԫ�ص�ֵe\n");
		 scanf("%d",&e);
		 j=ListInsert(Lists.elem[Lists.length-1].L,i,e); 
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		if (j!=INFEASIBLE) 
		 	printf("%s\n", j==OK? "����ɹ�" : j==ERROR? "����ʧ��" : "�������");
		 getchar();getchar();
		 break;
	   case 10:
		 printf("������ɾ����λ��i\n");
		 scanf("%d",&i);
		 j=ListDelete(Lists.elem[Lists.length-1].L,i,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 if(j==ERROR) printf("ɾ��ʧ�ܣ������ڵ�%d��Ԫ�أ�\n",i);
		 if(j==OK) printf("ɾ���ɹ�����ɾ��Ԫ�ص�ֵΪ%d\n",e);
		 getchar();getchar();
		 break;
	   case 11:
		 j=ListTraverse(Lists.elem[Lists.length-1].L);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 if(j==OK && !Lists.elem[Lists.length-1].L->next) printf("�����Ա�\n");
		getchar();getchar();
		 break;
	   case 12:
	   	 j=reverseList(Lists.elem[Lists.length-1].L);
	   	  if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else printf("����ת�ɹ�!");
	   	 getchar();getchar();
		 break;
	   case 13:
	   	 printf("������Ҫɾ�����ǵ����ڼ������\n");
		 scanf("%d",&n);    
	   	 j=RemoveNthFromEnd(Lists.elem[Lists.length-1].L,n,e);
	   	  if (j==INFEASIBLE) printf("���Ա����� "); 
	   	  if (Lists.elem[Lists.length-1].L&&Lists.elem[Lists.length-1].L->next==NULL) printf("���Ա�Ϊ�� "); 
		 else printf("ɾ���ɹ�����ɾ��Ԫ�ص�ֵΪ%d\n",e);
	   	 getchar();getchar();
		 break;	 
	   case 14:
	   	 j=sortList(Lists.elem[Lists.length-1].L);
	   	  if (j==INFEASIBLE) printf("���Ա�L������ "); 
		 else printf("��С�����������");
	   	 getchar();getchar();
		 break;	
	   case 15:
		 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 j=SaveList(Lists.elem[Lists.length-1].L,filename);
	   	  if (j==INFEASIBLE) printf("���Ա�L������"); 
		 else if(j==OK) printf("д���ļ����");
	   	 getchar();getchar();
		 break;	 
	   case 16:
	   	 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 j=LoadList(Lists.elem[Lists.length-1].L,filename);
	   	 if(j==INFEASIBLE) printf("���Ա�L�Ѵ���"); 
		 else if(j==OK) printf("�����ļ����");
	   	 getchar();getchar();
		 break;	
	   case 0:
         break;
       default:
       	 printf("������������������");		
    		
		}
	}
}