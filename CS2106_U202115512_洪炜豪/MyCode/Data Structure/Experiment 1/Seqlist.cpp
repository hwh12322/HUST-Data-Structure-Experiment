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
typedef struct{  //���Ա�Ĺ������
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
//���Ӻ��� 
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
        if (j==OK) 
            if (L.elem)
                printf("δ��ȷ�ͷ�����Ԫ�ؿռ�");
            else printf("�ɹ��ͷ����Ա�ռ�");
        else printf("ERROR");    
		 getchar();getchar();
		 break;
	   case 3:
		j=ClearList(L);
		if (j==INFEASIBLE) printf("���Ա����ڣ�");
		if (L.length) printf("δ��ȷ���");
		if (!L.elem)  printf("�����ͷ�Ԫ�ؿռ�");
		if (j==OK) printf("�ɹ�������Ա�L");
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
		else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա����");
		else printf("���Ա�L�ĳ���Ϊ%d", j);
		 getchar();getchar();
		 break;
	   case 6:
		 printf("������Ҫ��ȡԪ�ص�Ԫ���߼����\n"); 
		 scanf("%d",&i);    
		 j=GetElem(L,i,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա��ȡԪ��");
		else if(j==OK) printf("Ԫ�ص�ֵΪ%d",e);
		else if(j==ERROR) printf("Ԫ���߼���Ų��Ϸ�");
		getchar();getchar();
		 break;
	   case 7: 
		 printf("������Ҫ����Ԫ�ص�ֵe\n"); 
		 scanf("%d",&e);  
		 j=LocateElem(L,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա����Ԫ��");
		 else if(j==ERROR) printf("û���ҵ�ָ����Ԫ�أ�����ʧ��");
		 else printf("���ҳɹ���Ԫ���߼����Ϊ%d",j);
		 getchar();getchar();
		 break;
	   case 8: 
		 printf("������ָ��Ԫ�ص�ֵe\n");
		 scanf("%d",&e);  
		 j=PriorElem(L,e,pre); 
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա����ǰ��Ԫ��");
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
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա���Һ��Ԫ��");
		 else if(j==ERROR) printf("û���ҵ�ָ��Ԫ��");
		 else if(j==13) printf("ָ��Ԫ�ش��ڣ���̲�����");
		 else if(j==OK) printf("���Ԫ�ص�ֵΪ%d",next);
		 getchar();getchar();
		 break;
	   case 10:
		 printf("����������λ��i\n");
		 scanf("%d",&i);  
		 printf("���������Ԫ�ص�ֵe\n");
		 scanf("%d",&e);
		 j=ListInsert(L,i,e); 
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա���в��������");
		 else{
		 	printf("%s\n", j==OK? "����ɹ�" : j==ERROR? "����ʧ��" : "�������");
		 getchar();getchar();
		 break;
	   case 11:
		 printf("������ɾ����λ��i\n");
		 scanf("%d",&i);
		 j=ListDelete(L,i,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա����ɾ��������");
		 if(j==ERROR) printf("ɾ��ʧ�ܣ������ڵ�%d��Ԫ�أ�\n",i);
		if(j==OK) printf("ɾ���ɹ�����ɾ��Ԫ�ص�ֵΪ%d\n",e);
		 getchar();getchar();
		 break;
	   case 12:
		 j=ListTraverse(L);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա���б���������");
		 if(j==OK && !L.length) printf("�����Ա�\n");
		getchar();getchar();
		 break;
	   case 13:
	   	 j=MaxSubArray(L);
	   	  if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(j==OK && !L.length) printf("�����Ա�\n");
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա�������������������Ͳ�����");
		 else printf("��������������Ϊ%d",j);
	   	 getchar();getchar();
		 break;
	   case 14:
	   	 printf("������k\n");
		 scanf("%d",&k);    
	   	 j=SubArrayNum(L,k);
	   	  if (j==INFEASIBLE||(L.elem&&L.length==0)) printf("���Ա�L�����ڻ�Ϊ�� "); 
		 else if(j==OK && !L.length) printf("�����Ա�\n");
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա�������Ϊk������������ĸ���������");
		 else printf("���Ա��к�Ϊk������������ĸ���Ϊ%d",j);
	   	 getchar();getchar();
		 break;	 
	   case 15:
	   	 j=sortList(L);
	   	  if (j==INFEASIBLE||(L.elem&&L.length==0)) printf("���Ա�L�����ڻ�Ϊ�� "); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա������С�������������");
		 else if(j==OK && !L.length) printf("�����Ա�\n");
		 else printf("��С�����������");
	   	 getchar();getchar();
		 break;	
	   case 16:
		 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 j=SaveList(L,filename);
	   	  if (j==INFEASIBLE||(L.elem&&L.length==0)) printf("���Ա�L�����ڻ�Ϊ�� "); 
		 else if(L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա���в�����");
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
status InitList(SqList& L)//���Ա��ʼ�� 
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
    if(!L.length&&L.elem){//���Ա������Ϊ�� 
        return OK;
    }
    if(L.length&&L.elem){//���Ա�����ҷǿ� 
        return ERROR;
    }
    if(L.elem==NULL&&L.length==0){//���Ա�����
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
		printf("���Ա����ڣ�");
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

//���ӹ���//
status MaxSubArray(SqList L)//��������������
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
	for(j=0;j<L.length;j++)//ֻ�����һ�飬�㷨���Ӷ�O(n) ,����ǰ�ۼƵ�ֵС��0������������ۼ� 
	{
		thissum+=L.elem[j];
		if(thissum>maxsum)
			maxsum=thissum;
		else if(thissum<0)
			thissum=0;
	}
	return maxsum;
}

status SubArrayNum(SqList L,int k)//��ΪK����������� 
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
    for (i=0;i<L.length;i++)//����ÿ��Ԫ�أ�����������������Ԫ�ؽ����ۼӣ����Ӷ�O(n^2) 
    {
        int num=0;
        for(j=i;j<L.length;j++){
            num+=L.elem[j];
            if(num==k) sum++;
        }
    }
    return sum;
}
/*��ϣ��
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
            //����ܺ�û���ֹ�������ӽ���ϣ��,������ֹ�����ϣ���е�ֵ+1
            if(map.get(sum)==null)
                map.put(sum,1 );
            else
                map.put(sum,map.get(sum)+1 );
        }
        return count;
} 
*/

status sortList(SqList L)//��������
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
	qsort(L.elem,L.length,sizeof(L.elem[0]),cmp);//���� 
	return OK;
}

status  SaveList(SqList L,char FileName[])//ʵ�����Ա���ļ���ʽ���� 
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
			ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e); 
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
					ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e); 
   					}while(getchar()!='\n');
  				getchar();getchar();
		 		break;
	   		case 2:
	   			printf("������Ҫɾ���ı���\n");
				scanf("%s",name);
	   			if (RemoveList(Lists,name)==OK)
	   			{
   					printf("ɾ���ɹ�"); 
				}
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
    Lists.elem[Lists.length].L.elem = (ElemType *) malloc(LIST_INIT_SIZE  * sizeof( ElemType ));	
	if ( !Lists.elem[Lists.length].L.elem ){
		printf("�洢�ռ�����ʧ��\n");
		exit(OVERFLOW);
	} 
    Lists.elem[Lists.length].L.length=0;
    Lists.elem[Lists.length].L.listsize=100;
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
		printf("    	  3. ListEmpty      12. MaxSubArray\n");
		printf("    	  4. ListLength     13. SubArrayNum\n");
		printf("    	  5. GetElem        14. sortList\n");
		printf("    	  6. LocateElem     15. SaveList\n");
		printf("    	  7. PriorElem      16. LoadList\n");
		printf("    	  8. NextElem       ");
		printf("    	  \n");
		printf("-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~16]:");
		scanf("%d",&op);
    switch(op){
	   case 1:
		 j=DestroyList(Lists.elem[n-1].L);
		if (j==INFEASIBLE) printf("���Ա����ڣ�");
        if (j==OK) 
            if (Lists.elem[n-1].L.elem)
                printf("δ��ȷ�ͷ�����Ԫ�ؿռ�");
            else printf("�ɹ��ͷ����Ա�ռ�");
        else printf("ERROR");    
		 getchar();getchar();
		 break;
	   case 2: 
		j=ClearList(Lists.elem[n-1].L);
		if (j==INFEASIBLE) printf("���Ա����ڣ�");
		if (Lists.elem[n-1].L.length) printf("δ��ȷ���");
		if (!Lists.elem[n-1].L.elem)  printf("�����ͷ�Ԫ�ؿռ�");
		if (j==OK) printf("�ɹ�������Ա�L");
		getchar();getchar();
		break;
	   case 3:
		 j=ListEmpty(Lists.elem[n-1].L);
		if (j==OK) printf("���Ա�L����Ϊ0");
		else if (j==ERROR) printf("���Ա�L����Ϊ��Ϊ0");
		else if (j==INFEASIBLE) printf("���Ա����ڣ�");
		else printf("δ��ȷ�п�");
		 getchar();getchar();
		 break;
	   case 4:
		 j=ListLength(Lists.elem[n-1].L); 
		if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա����");
		else printf("���Ա�L�ĳ���Ϊ%d", j);
		 getchar();getchar();
		 break;
	   case 5:
		 printf("������Ҫ��ȡԪ�ص�Ԫ���߼����\n"); 
		 scanf("%d",&i);    
		 j=GetElem(Lists.elem[n-1].L,i,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա��ȡԪ��");
		else if(j==OK) printf("Ԫ�ص�ֵΪ%d",e);
		else if(j==ERROR) printf("Ԫ���߼���Ų��Ϸ�");
		getchar();getchar();
		 break;
	   case 6:
		 printf("������Ҫ����Ԫ�ص�ֵe\n"); 
		 scanf("%d",&e);  
		 j=LocateElem(Lists.elem[n-1].L,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա����Ԫ��");
		 else if(j==ERROR) printf("û���ҵ�ָ����Ԫ�أ�����ʧ��");
		 else printf("���ҳɹ���Ԫ���߼����Ϊ%d",j);
		 getchar();getchar();
		 break;
	   case 7:
		 printf("������ָ��Ԫ�ص�ֵe\n");
		 scanf("%d",&e);  
		 j=PriorElem(Lists.elem[n-1].L,e,pre); 
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա����ǰ��Ԫ��");
		 else if(j==ERROR) printf("û���ҵ�ָ��Ԫ��");
		 else if(j==12) printf("ָ��Ԫ�ش��ڣ�ǰ��������");
		 else if(j==OK) printf("ǰ��Ԫ�ص�ֵΪ%d",pre);
		 getchar();getchar();
		 break;
	   case 8:
		 printf("������ָ��Ԫ�ص�ֵe\n");
		 scanf("%d",&e);
		 j=NextElem(Lists.elem[n-1].L,e,next);  
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա���Һ��Ԫ��");
		 else if(j==13) printf("ָ��Ԫ�ش��ڣ���̲�����");
		 else if(j==OK) printf("���Ԫ�ص�ֵΪ%d",next);
		 getchar();getchar();
		 break;
	   case 9:
		 printf("����������λ��i\n");
		 scanf("%d",&i);  
		 printf("���������Ԫ�ص�ֵe\n");
		 scanf("%d",&e);
		 j=ListInsert(Lists.elem[n-1].L,i,e); 
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա���в��������");
		 else
		 	printf("%s\n", j==OK? "����ɹ�" : j==ERROR? "����ʧ��" : "�������");
		 getchar();getchar();
		 break;
	   case 10:
		 printf("������ɾ����λ��i\n");
		 scanf("%d",&i);
		 j=ListDelete(Lists.elem[n-1].L,i,e);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա����ɾ��������");
		 if(j==ERROR) printf("ɾ��ʧ�ܣ������ڵ�%d��Ԫ�أ�\n",i);
		if(j==OK) printf("ɾ���ɹ�����ɾ��Ԫ�ص�ֵΪ%d\n",e);
		 getchar();getchar();
		 break;
	   case 11:
		 j=ListTraverse(Lists.elem[n-1].L);
		 if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܻ�Բ����ڵ����Ա���б���������");
		 if(j==OK && !Lists.elem[n-1].L.length) printf("�����Ա�\n");
		getchar();getchar();
		 break;
	   case 12:
	   	 j=MaxSubArray(Lists.elem[n-1].L);
	   	  if (j==INFEASIBLE) printf("���Ա����ڣ�"); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա�������������������Ͳ�����");
		 else printf("��������������Ϊ%d",j);
	   	 getchar();getchar();
		 break;
	   case 13:
	   	 printf("������k\n");
		 scanf("%d",&k);    
	   	 j=SubArrayNum(Lists.elem[n-1].L,k);
	   	  if (j==INFEASIBLE||(Lists.elem[n-1].L.elem&&Lists.elem[n-1].L.length==0)) printf("���Ա�L�����ڻ�Ϊ�� "); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա�������Ϊk������������ĸ���������");
		 else printf("���Ա��к�Ϊk������������ĸ���Ϊ%d",j);
	   	 getchar();getchar();
		 break;	 
	   case 14:
	   	 j=sortList(Lists.elem[n-1].L);
	   	  if (j==INFEASIBLE||(Lists.elem[n-1].L.elem&&Lists.elem[n-1].L.length==0)) printf("���Ա�L�����ڻ�Ϊ�� "); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա������С�������������");
		 else printf("��С�����������");
	   	 getchar();getchar();
		 break;	
	   case 15:
		 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 j=SaveList(Lists.elem[n-1].L,filename);
	   	  if (j==INFEASIBLE||(Lists.elem[n-1].L.elem&&Lists.elem[n-1].L.length==0)) printf("���Ա�L�����ڻ�Ϊ�� "); 
		 else if(Lists.elem[n-1].L.elem==NULL&&j!=INFEASIBLE) printf("���ܶԲ����ڵ����Ա���в�����");
		 else if(j==OK) printf("д���ļ����");
	   	 getchar();getchar();
		 break;	 
	   case 16:
	   	 printf("�������ļ���\n");
		 scanf("%s",filename);  
	   	 j=LoadList(Lists.elem[n-1].L,filename);
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
