#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAXN 100
#define INF 50000000
using namespace std;
typedef int status;
typedef int KeyType;
typedef struct {
	KeyType  key;
	char others[20];
} VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
	int adjvex;              //����λ�ñ��
	struct ArcNode* nextarc;	   //��һ������ָ��
} ArcNode;
typedef struct VNode {				//ͷ��㼰���������Ͷ���
	VertexType data;       	//������Ϣ
	ArcNode* firstarc;      	 //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
	AdjList vertices;     	 //ͷ�������
	int vexnum, arcnum;   	  //������������
} ALGraph;

typedef struct {
	ALGraph G;
	char name[20];
}GType;

typedef struct {
	GType Graph[20];//���ͼ���в���
	int length;
}SqList;

SqList L;
int num=1;
void (*VisitFunc)(VertexType);
int visited[MAX_VERTEX_NUM];
queue <VertexType> q;
char filename[30];
int lx,rx,xy;
int pa[MAX_VERTEX_NUM];
int map[MAXN][MAXN]; 
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
status FirstAdjVex(ALGraph G,KeyType u);
status NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
void visit(VertexType v);
void DFS(ALGraph G, int v);
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
void WArc(int VR[][2], ArcNode *p, int &cnt, int i);
status SaveGraph(ALGraph G,char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]) ;
int VerticesSetLessThanK(ALGraph G,KeyType v,int k);
int ShortestPathLength(ALGraph G,KeyType v,KeyType w);
int ConnectedComponentsNums(ALGraph G);
int GraphSearch(char*);
int find(int x){
	if(x!=pa[x]) return pa[x]=find(pa[x]);
	else return x;
}
void merge(int x,int y){
	int p1=find(x);
	int p2=find(y);
	if(p1!=p2) pa[p1]=p2;
}
int main(void) {
	KeyType op=1,j=0,k=0,i=0,u,v,w;
	VertexType V[30],value;
	KeyType VR[100][2]; 
	
	while (op) {	
	system("cls");  	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("1. Createraph              11. DFSTraverse\n");
	printf("2. DestroyGraph            12. BFSTraverse\n");
	printf("3. LocateVex               13. SaveGraph\n");
	printf("4. PutVex                  14. LoadGraph\n");
	printf("5. FirstAdjVex             15. VerticesSetLessThanK\n");
	printf("6. NextAdjVex              16. ShortestPathLength\n");
	printf("7. InsertVex               17. ConnectedComponentsNums\n");
	printf("8. DeleteVex               18. AlterGraph\n");
	printf("9. InsertArc               19. GraphSearch\n");
	printf("10.DeleteArc               0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("��ѡ����Ĳ���[0~19]:");
	scanf("%d", &op);		
		switch (op) {
			case 0:
				break;

			case 1:
			printf("\t\t\t���������ݣ�") ;
				do {
					scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i=0;
				do {
					scanf("%d%d",&VR[i][0],&VR[i][1]);
				} while(VR[i++][0]!=-1);
				if (CreateCraph(L.Graph[num-1].G,V,VR)==ERROR) printf("\t\t\t�������ݴ��޷�����\n");
				else {
					printf("\t\t\t��������ͼ�����ƣ�\n");
	   				scanf("%s",L.Graph[num-1].name);
	   				L.length++;
	   				printf("\t\t\tͼ�����ɹ���\n");
				}
				getchar();
				getchar();
				break;

			case 2:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				if (DestroyGraph(L.Graph[num-1].G) == OK) printf("\t\t\tͼ�����ٳɹ���\n");
				else printf("\t\t\tͼ������ʧ�ܣ�\n");
				getchar();
				getchar();
				break;
				
			case 3:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t��������Ҫ���ҽ���keyֵ��");
				scanf("%d",&u);
				i = LocateVex(L.Graph[num-1].G,u);
				if(i != -1) {
					printf("\t\t\t���ҳɹ����ý����ϢΪ��\n");
					visit(L.Graph[num-1].G.vertices[i].data);
				}else printf("\t\t\t����ʧ�ܣ�\n");
				getchar();
				getchar();
				break;

			case 4:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t��������Ҫ��ֵ�Ľ��keyֵ:");
				scanf("%d",&u);
				printf("\t\t\t�����븳ֵ��Ľ��keyֵ:");
				scanf("%d",&value.key);
				printf("\t\t\t�����븳ֵ��Ľ��othersֵ:");
				scanf("%s",value.others);
				if(PutVex(L.Graph[num-1].G,u,value)) {
				printf("��ֵ�ɹ������ڸý�����ϢΪ��\n");
					visit(L.Graph[num-1].G.vertices[LocateVex(L.Graph[num-1].G,value.key)].data);
				}else printf("��ֵʧ�ܣ�\n");
				getchar();
				getchar();
				break;

			case 5:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t��������Ҫ���ҵ�һ�ڽӵ����keyֵ��");
				scanf("%d",&u);
				i = FirstAdjVex(L.Graph[num-1].G,u);
				if(i != -1) {
					printf("\t\t\t���ҵ�����һ�ڽӵ���Ϣ���£�\n���%d",i);
					visit(L.Graph[num-1].G.vertices[i].data);
				} else printf("\t\t\t����ʧ�ܣ�\n");
				getchar();
				getchar();
				break;

			case 6:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t��������Ҫ������һ�ڽӵ����keyֵv��");
				scanf("%d",&v);
				printf("\t\t\t��������Ҫ������һ�ڽӵ����keyֵw��");
				scanf("%d",&w);
				i = NextAdjVex(L.Graph[num-1].G, v, w);
				if(i != -1) {
					printf("\t\t\t���ҳɹ���v���ڽӶ��������w����һ�ڽӶ�����Ϣ���£�\n���%d",i);
					visit(L.Graph[num-1].G.vertices[i].data);
				} else printf("\t\t\t����ʧ�ܣ�\n");
				getchar();
				getchar();
				break;

			case 7:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				int keyforsib;
				printf("\t\t\t��������Ҫ����Ľ���keyֵ��");
				scanf("%d",&value.key);
				printf("\t\t\t��������Ҫ����Ľ���others��");
				scanf("%s",value.others);
				i = InsertVex(L.Graph[num-1].G,value);
				if(i == OK) {
					printf("\t\t\t����ɹ���\n");
				} else printf("\t\t\t����ʧ�ܣ�\n");
				getchar();
				getchar();
				break;

			case 8:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t��������Ҫɾ���Ľ��keyֵ��");
				scanf("%d",&v);
				i = DeleteVex(L.Graph[num-1].G,v);
				if(i == OK) {
					printf("\t\t\tɾ���ɹ���\n");
				} else printf("\t\t\tɾ��ʧ�ܣ�\n");
				getchar();
				getchar();
				break;

			case 9:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t��������Ҫ����Ļ�ͷ��keyֵ��");
				scanf("%d",&v);
				printf("\t\t\t��������Ҫ����Ļ�β��keyֵ��");
				scanf("%d",&w);
				i = InsertArc(L.Graph[num-1].G,v,w);
				if(i == OK) printf("\t\t\t���뻡�ɹ���\n");
				else printf("\t\t\t���뻡ʧ�ܣ�");
				getchar();
				getchar();
				break;

			case 10:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t��������Ҫɾ���Ļ�ͷ��keyֵ��");
				scanf("%d",&v);
				printf("\t\t\t��������Ҫɾ���Ļ�β��keyֵ��");
				scanf("%d",&w);
				i = DeleteArc(L.Graph[num-1].G,v,w);
				if(i == OK) printf("\t\t\tɾ�����ɹ���\n");
				else printf("\t\t\tɾ����ʧ�ܣ�");
				getchar();
				getchar();
				break;

			case 11:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				DFSTraverse(L.Graph[num-1].G,visit);
				printf("\t\t\t�����������������ɣ�\n");
				getchar();
				getchar();
				break;

			case 12:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				BFSTraverse(L.Graph[num-1].G,visit);
				printf("\t\t\t�����������������ɣ�\n");
				getchar();
				getchar();
				break;
				
			case 13:
	   			if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("�����ļ�����");
				scanf("%s",filename) ;
				SaveGraph(L.Graph[num-1].G,filename);
				printf("\t\t\t�����Ѿ�д���ļ���\n");
				getchar();getchar();
				break;
		
			case 14:
	   			if (L.Graph[num-1].G.vexnum != 0)
	  		 	{
	   				printf("\t\t\tͼ�Ѵ��ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("��������ͼ�����ƣ�\n");
	   			scanf("%s",L.Graph[num-1].name);
	   			getchar();
	   			L.length++;
				printf("�����ļ�����");
				scanf("%s",filename) ;
				LoadGraph(L.Graph[num-1].G,filename);
				printf("\t\t\t�ļ��Ѿ�����ͼ��\n");
				getchar();getchar();
				break;
				
			case 15:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
			
				printf("\t\t\t��������Ҫ��ѯ�Ķ����keyֵ��");
				scanf("%d",&v);
				printf("\t\t\t��������Ҫ��ѯ�ľ��룺");
				scanf("%d",&k);
				lx=LocateVex(L.Graph[num-1].G,v);
				if (lx==-1)
	   			{
	   				printf("\t\t\t��ѯ���ж��㲻���ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				xy= VerticesSetLessThanK(L.Graph[num-1].G,v,k);
				if(xy == 0) printf("\t\t\t�޾���С��k�Ķ��㣡\n");
				else  printf("\t\t\t��%d��С��%d�Ķ��㣡\n",xy,k);
				
				getchar();
				getchar();
				break;
				
			case 16:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
			
				printf("\t\t\t��������Ҫ��ѯ�ĵ�һ�������keyֵ��");
				scanf("%d",&v);
				printf("\t\t\t��������Ҫ��ѯ�ĵڶ��������keyֵ��");
				scanf("%d",&w);
				lx=LocateVex(L.Graph[num-1].G,v);
				rx=LocateVex(L.Graph[num-1].G,w);
				if (lx==-1||rx==-1)
	   			{
	   				printf("\t\t\t��ѯ���ж��㲻���ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				xy= ShortestPathLength(L.Graph[num-1].G,v,w);
				if(xy == 0) printf("\t\t\t��������Ϊͬһ����\n");
				else if(xy==INF) printf("\t\t\t�������㲻��ͨ��");
				else  printf("\t\t\t�����������С·����Ϊ%d��",xy);
				getchar();
				getchar();
				break;
				
				
				
			case 17:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\tͼ�����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
	
				printf("\t\t\t��ͼһ����%d����ͨ������\n",ConnectedComponentsNums(L.Graph[num-1].G));
				getchar();
				getchar();
				break;
				
			case 18:
					printf("\t\t\t��ǰͼΪ��%d��\n",num);
					printf("\t\t\t����ͼ�����(1~20)��");
					scanf("%d",&num); 
					printf("\t\t\tͼ�Ѿ��л�Ϊ��%d��ͼ��\n",num);
					getchar();getchar();
					break;
		
			case 19:
					printf("\t\t\t����ͼ�����ƣ�");
					char gx[20];
					scanf("%s",gx);
					if(GraphSearch(gx)!=-1)
					printf("\t\t\t��ͼ���Ϊ%d��\n",GraphSearch(gx));
					else 
					printf("\t\t\t��ͼ�����ڣ�\n");
					getchar();getchar();
					break;

			default://ȷ�����������������
				printf("\t\t\t������[0~19]ʵ�ֲ˵�����");
				break;
		}//end of switch
	}//end of while
				

	printf("\t\t\t��ӭ�´�ʹ�ñ�ϵͳ��\n");
	return 0;
}


#define MAX_VERTEX_NUM 20
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int i=0,flag=0;
	while(V[i].key!=-1){
		flag=1;
		if(i>=MAX_VERTEX_NUM) return ERROR;//����20�д�
		G.vertices[i].data=V[i];
		G.vertices[i].firstarc=NULL;
		i++;
	}//���ͷ���
	if(!flag) return ERROR;//������ݴ�ʱ 
	G.vexnum=i;
	for(i=0;i<G.vexnum;i++) {
		for(int j=0;j<G.vexnum;j++) {
			if(V[i].key==V[j].key&&i!=j)
				return ERROR;//�ڵ�ֵ����
		}
	}
	i=0;
	ArcNode *p;
    int fir,sec;
	G.arcnum=0;//����ǰ�棬�������Ķ�ֱ�������ˣ������û�и�ֵ��д���棩
	while(VR[i][0]!=-1){
		G.arcnum++;
		fir=-1;
		for(int j=0;j<G.vexnum;j++)
			if(VR[i][0]==G.vertices[j].data.key){
				fir=j;
				break;
			}//�ҽڵ���
		if(fir==-1) return ERROR;//�ڵ㲻����
        sec=-1;
		for(int j=0;j<G.vexnum;j++)
			if (VR[i][1]==G.vertices[j].data.key){
				sec=j;
				break;
			}
        if(sec==-1) return ERROR;

		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=sec;
		p->nextarc=G.vertices[fir].firstarc;//�׽�
		G.vertices[fir].firstarc=p;

        p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=fir;
		p->nextarc=G.vertices[sec].firstarc;
		G.vertices[sec].firstarc=p;//����ͼ�Գƴ洢

		i++;
	}//��ӱ߽��
    return OK;
    /********** End **********/
}


status DestroyGraph(ALGraph &G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    for(int i=0;i<G.vexnum;i++){
        ArcNode*p=G.vertices[i].firstarc,*q;//q�Ǽ�¼λ�õ�����qǰ�ǵü�*�������棩
        while(p){
            q=p->nextarc;
            free(p);
            p=q;
        }
    }
    G.vexnum = 0;//�ߵ�����
	G.arcnum = 0;//���û���ͷ�ڵ�����
    return OK;
    /********** End **********/
}


int LocateVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
        int fir=-1;
    	for(int j=0;j<G.vexnum;j++)
			if(u==G.vertices[j].data.key){
				fir=j;
				break;
			}//�ҽڵ���
		return fir;
    /********** End **********/
}


status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i=LocateVex(G,u);
	if(i!=-1) {

			G.vertices[i].data=value;
			return OK;

	} 
	 return ERROR;

    /********** End **********/
}

int FirstAdjVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i=LocateVex(G,u);
	if(i!=-1) {
        if(G.vertices[i].firstarc)return G.vertices[i].firstarc->adjvex;//���
        else return -1;
	} else return -1;

    /********** End **********/
}


int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
	if(i!=-1&&j!=-1) {
        ArcNode*p=G.vertices[i].firstarc;
        while(p){
            if(p->adjvex==j){//adjvex��λ��w��ֵ(д����)
                if(p->nextarc!=NULL)return p->nextarc->adjvex;//����������һ���ڽӵ㣨д���棩
                else return -1;
            } 
            p=p->nextarc;
        }
       return -1; 
	} else return -1;
    /********** End **********/
}


status InsertVex(ALGraph &G,VertexType v)
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    for(int i=0;i<G.vexnum;i++){
        if(v.key==G.vertices[i].data.key) return ERROR;//�ṹ��Ƚϲ�����ֱ��
    }
    G.vexnum++;
    if(G.vexnum>20) return ERROR;
    G.vertices[G.vexnum-1].data=v;//�ṹ�帳ֵ����ֱ��
    return OK;

    /********** End **********/
}



status DeleteVex(ALGraph &G,KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(G.vertices[0].data.key != -1 && G.vertices[1].data.key == -1) return ERROR;//����ɾ�ɿձ�

    int  x;
	x=LocateVex(G, v);
	if(x==-1) return ERROR;//û�ҵ�

    ArcNode *p,*q;
	p=G.vertices[x].firstarc;
	while(p){
		q=p;
		p=p->nextarc;
		free(q);
		G.arcnum--;
	}
	

	for(int i=x;i<G.vexnum;i++)//ɾͷ�ڵ�
		G.vertices[i]=G.vertices[i+1];
    G.vexnum--;

	for(int i=0;i<G.vexnum;i++){
		p=G.vertices[i].firstarc;
		while(p) {
			if(p->adjvex==x){
				if(p==G.vertices[i].firstarc){//ɾ�׸��ڵ��������
					G.vertices[i].firstarc=p->nextarc;
					free(p);
					p = G.vertices[i].firstarc;//����break,��ΪҪʹ��Ŵ�Ľڵ���ż�һ
				}else{
					q->nextarc=p->nextarc;
					free(p);
					p=q->nextarc;
				}
			}else{
				if(p->adjvex>x)//��Ľڵ����Ҫ��1
					p->adjvex--;
				q=p;
				p=p->nextarc;
			}
		}
	}
	return OK;
    /********** End **********/
}


status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
    if(i==-1||j==-1) return ERROR;//�����ڸõ�
    ArcNode *p,*q;
    p=G.vertices[i].firstarc;
    while(p){
		if(p->adjvex==j)return ERROR;
		p=p->nextarc;
	}//�Ѿ����ڸû�
    G.arcnum++;
    q=G.vertices[i].firstarc;
    p=(ArcNode*)malloc(sizeof(ArcNode));//�ǵ÷���ռ�
    p->adjvex=j;
    p->nextarc=q;
    G.vertices[i].firstarc=p;
    q=G.vertices[j].firstarc;
    p=(ArcNode*)malloc(sizeof(ArcNode));//�ǵ÷���ռ�
    p->adjvex=i;
    p->nextarc=q;
    G.vertices[j].firstarc=p;
    return OK;
    
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
    if(i==-1||j==-1) return ERROR;//�����ڸõ�
    int flag=0;
    ArcNode *p,*q=NULL,*t;
    p=G.vertices[i].firstarc;
    while(p){
		if(p->adjvex==j){
            if(p==G.vertices[i].firstarc){
                G.vertices[i].firstarc=p->nextarc;//ɾ���׸������������д���棩
                t=p;
                free(t);
            }
            else{
                q->nextarc=p->nextarc;
                t=p;
                free(t);
            }
            flag=1;
            break;
        }
        q=p;
		p=p->nextarc;
	}
    p=G.vertices[j].firstarc;
    while(p){
		if(p->adjvex==i){
             if(p==G.vertices[j].firstarc){
                G.vertices[j].firstarc=p->nextarc;//ɾ���׸������������д���棩
                t=p;
                free(t);
            }
            else{
                q->nextarc=p->nextarc;
                t=p;
                free(t);
            }
            flag=1;
            break;
        }
        q=p;
		p=p->nextarc;
	}
    if(flag){
        G.arcnum--;
        return OK;
    }else return ERROR;//û�ҵ��ñ�

    /********** End **********/
}

void DFS(ALGraph G, int v) {
	visited[v]=1;
	VisitFunc(G.vertices[v].data);
	for(int w=FirstAdjVex(G,G.vertices[v].data.key);w>= 0;w=NextAdjVex(G,G.vertices[v].data.key,w))
		if(!visited[w]) DFS(G,w);
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	VisitFunc=visit;
	for(int i=0;i<G.vexnum;i++) visited[i]=0;
	for(int i=0;i<G.vexnum;i++)
		if(!visited[i]) DFS(G,i);
    /********** End **********/
}


status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    VisitFunc=visit;
    for(int i=0;i<G.vexnum;i++){
       if(!visited[i]){
        visited[i]=1;
        q.push(G.vertices[i].data);//��0��ʼ
        while(!q.empty()){
        	VertexType t;
        	t=q.front();
        	q.pop();
        	VisitFunc(t);
        	int x=LocateVex(G,t.key);
        	ArcNode *p=G.vertices[x].firstarc;
        	while(p){
          	  	if(!visited[p->adjvex]){
                	visited[p->adjvex]=1;
                	q.push(G.vertices[p->adjvex].data);
            	}
            	p=p->nextarc;
        		}
    		}
    	}
	}
	for(int i=0;i<G.vexnum;i++) visited[i]=0;//Ҫ���³�ʼ�� 
}

//���ʽڵ�
void visit(VertexType v) {
	printf("               key = %d,others = %s\n",v.key,v.others);
}


 //��ͼ�й�ϵ������VR������
 
void WArc(int VR[][2], ArcNode *p, int &cnt, int i) {
	if(p==NULL) return;
	if(p->nextarc) WArc(VR, p->nextarc, cnt, i);
	for(int j=0;j<cnt;j++)//����߲��ƶԳ��ظ���Ϣ
		if(VR[j][1]==i&&VR[j][0]==p->adjvex) 
			return;
	VR[cnt][0]=i;
	VR[cnt++][1]=p->adjvex;
}



status SaveGraph(ALGraph G, char FileName[])
//��ͼ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
    int VR[100][2]= {0};
    FILE* fp=fopen(FileName,"w");
	int cnt=0;//��¼������
	for(int i=0;i<G.vexnum;i++){
		fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
	}
	fprintf(fp,"-1 nil ");//д�붥����Ϣ

	for(int i=0; i<G.vexnum; i++) {//����Ϣ��������
		WArc(VR, G.vertices[i].firstarc, cnt, i);
	}
	int x,y;
	for(int i=0;i<cnt;i++) {//д�����Ϣ
		x=VR[i][0];
		y=VR[i][1];
		fprintf(fp,"%d %d ", G.vertices[x].data.key, G.vertices[y].data.key);
	}
	fprintf(fp,"-1 -1");
	fclose(fp);
	return OK;

    /********** End 1 **********/
}



status LoadGraph(ALGraph &G, char FileName[])
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    FILE* fp=fopen(FileName,"r");
	int i, j, k;
	char str[20];
	VertexType V[20];
	KeyType VR[100][2];
	i=0;
	do{
        fscanf(fp,"%d %s ",&V[i].key,V[i].others);
    }while(!(V[i++].key<0));//��ȡ������Ϣ��
	i=0;
	while(fscanf(fp,"%d %d ", &VR[i++][0], &VR[i][1])!=EOF);
	fclose(fp);//��ȡ����Ϣ

	if(CreateCraph(G,V,VR)==OK){
		if(G.vertices[2].firstarc!=NULL){
			ArcNode *p, *q;
			p=G.vertices[2].firstarc;
	 		q=p->nextarc;
			p->nextarc=q->nextarc;
			q->nextarc=p;
			G.vertices[2].firstarc=q;	
		}
		return OK;
	}
 	else return ERROR;

    /********** End 2 **********/
}

int GraphSearch(char gx[]){
	for(int i=0;i<L.length;i++){
		if(!(strcmp(L.Graph[i].name,gx)))
			return i+1; 
	}
	return -1;
}


int ConnectedComponentsNums(ALGraph G){
	int cnt=0;
	for(int i=0;i<G.vexnum;i++) pa[i]=i;
	for(int i=0;i<G.vexnum;i++){
		ArcNode *p;
		p=G.vertices[i].firstarc;
		while(p){
			merge(i,p->adjvex);
			p=p->nextarc;
		}
	}
	for(int i=0;i<G.vexnum;i++)
	if(find(i)==i)cnt++;
	return cnt;
}

int ShortestPathLength(ALGraph G,KeyType v,KeyType w){
	for(int i=1;i<=G.vexnum;i++)
		for(int j=1;j<=G.vexnum;j++)
			map[i][j]=0;
			
	for(int i=0;i<G.vexnum;i++){
		ArcNode *p;
		p=G.vertices[i].firstarc;
		while(p){
			map[i][p->adjvex]=1;
			p=p->nextarc;
		}
	}
	for(int i=0;i<G.vexnum;i++)
		for(int j=0;j<G.vexnum;j++)
			if(i==j) map[i][j]=0;
			else if(map[i][j]!=1) map[i][j]=INF;	
		
	for(int k=0;k<G.vexnum;k++)
		for(int i=0;i<G.vexnum;i++)
			for(int j=0;j<G.vexnum;j++)
				if(map[i][j]>map[i][k]+map[k][j])
					map[i][j]=map[i][k]+map[k][j];
	int x=LocateVex(G,v);
	int y=LocateVex(G,w);
	return map[x][y];
}
int VerticesSetLessThanK(ALGraph G,KeyType v,int k){
	int cnt=0;
	for(int i=1;i<=G.vexnum;i++)
		for(int j=1;j<=G.vexnum;j++)
			map[i][j]=0;
			
	for(int i=0;i<G.vexnum;i++){
		ArcNode *p;
		p=G.vertices[i].firstarc;
		while(p){
			map[i][p->adjvex]=1;
			p=p->nextarc;
		}
	}
	for(int i=0;i<G.vexnum;i++)
		for(int j=0;j<G.vexnum;j++)
			if(i==j) map[i][j]=0;
			else if(map[i][j]!=1) map[i][j]=INF;	
		
	for(int t=0;t<G.vexnum;t++)
		for(int i=0;i<G.vexnum;i++)
			for(int j=0;j<G.vexnum;j++)
				if(map[i][j]>map[i][t]+map[t][j])
					map[i][j]=map[i][t]+map[t][j];
	int x=LocateVex(G,v);
	
	for(int i=0;i<G.vexnum;i++){
		if(x!=i&&map[x][i]<k){
			cnt++;
			printf("\t\t\t%d��%d\n",G.vertices[x].data.key,G.vertices[i].data.key);
		}
	}
	return cnt;
}
