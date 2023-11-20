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
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
	int adjvex;              //顶点位置编号
	struct ArcNode* nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode {				//头结点及其数组类型定义
	VertexType data;       	//顶点信息
	ArcNode* firstarc;      	 //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
	AdjList vertices;     	 //头结点数组
	int vexnum, arcnum;   	  //顶点数、弧数
} ALGraph;

typedef struct {
	ALGraph G;
	char name[20];
}GType;

typedef struct {
	GType Graph[20];//多个图进行操作
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
	printf("请选择你的操作[0~19]:");
	scanf("%d", &op);		
		switch (op) {
			case 0:
				break;

			case 1:
			printf("\t\t\t请输入数据：") ;
				do {
					scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i=0;
				do {
					scanf("%d%d",&VR[i][0],&VR[i][1]);
				} while(VR[i++][0]!=-1);
				if (CreateCraph(L.Graph[num-1].G,V,VR)==ERROR) printf("\t\t\t输入数据错，无法创建\n");
				else {
					printf("\t\t\t请输入新图的名称！\n");
	   				scanf("%s",L.Graph[num-1].name);
	   				L.length++;
	   				printf("\t\t\t图表创建成功！\n");
				}
				getchar();
				getchar();
				break;

			case 2:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				if (DestroyGraph(L.Graph[num-1].G) == OK) printf("\t\t\t图表销毁成功！\n");
				else printf("\t\t\t图表销毁失败！\n");
				getchar();
				getchar();
				break;
				
			case 3:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t请输入需要查找结点的key值：");
				scanf("%d",&u);
				i = LocateVex(L.Graph[num-1].G,u);
				if(i != -1) {
					printf("\t\t\t查找成功！该结点信息为：\n");
					visit(L.Graph[num-1].G.vertices[i].data);
				}else printf("\t\t\t查找失败！\n");
				getchar();
				getchar();
				break;

			case 4:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t请输入需要赋值的结点key值:");
				scanf("%d",&u);
				printf("\t\t\t请输入赋值后的结点key值:");
				scanf("%d",&value.key);
				printf("\t\t\t请输入赋值后的结点others值:");
				scanf("%s",value.others);
				if(PutVex(L.Graph[num-1].G,u,value)) {
				printf("赋值成功！现在该结点的信息为：\n");
					visit(L.Graph[num-1].G.vertices[LocateVex(L.Graph[num-1].G,value.key)].data);
				}else printf("赋值失败！\n");
				getchar();
				getchar();
				break;

			case 5:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t请输入你要查找第一邻接点结点的key值：");
				scanf("%d",&u);
				i = FirstAdjVex(L.Graph[num-1].G,u);
				if(i != -1) {
					printf("\t\t\t已找到，第一邻接点信息如下：\n编号%d",i);
					visit(L.Graph[num-1].G.vertices[i].data);
				} else printf("\t\t\t查找失败！\n");
				getchar();
				getchar();
				break;

			case 6:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t请输入你要查找下一邻接点结点的key值v：");
				scanf("%d",&v);
				printf("\t\t\t请输入你要查找下一邻接点结点的key值w：");
				scanf("%d",&w);
				i = NextAdjVex(L.Graph[num-1].G, v, w);
				if(i != -1) {
					printf("\t\t\t查找成功，v的邻接顶点相对于w的下一邻接顶点信息如下：\n编号%d",i);
					visit(L.Graph[num-1].G.vertices[i].data);
				} else printf("\t\t\t查找失败！\n");
				getchar();
				getchar();
				break;

			case 7:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				int keyforsib;
				printf("\t\t\t请输入你要插入的结点的key值：");
				scanf("%d",&value.key);
				printf("\t\t\t请输入你要插入的结点的others：");
				scanf("%s",value.others);
				i = InsertVex(L.Graph[num-1].G,value);
				if(i == OK) {
					printf("\t\t\t插入成功！\n");
				} else printf("\t\t\t插入失败！\n");
				getchar();
				getchar();
				break;

			case 8:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t请输入你要删除的结点key值：");
				scanf("%d",&v);
				i = DeleteVex(L.Graph[num-1].G,v);
				if(i == OK) {
					printf("\t\t\t删除成功！\n");
				} else printf("\t\t\t删除失败！\n");
				getchar();
				getchar();
				break;

			case 9:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t请输入你要插入的弧头的key值：");
				scanf("%d",&v);
				printf("\t\t\t请输入你要插入的弧尾的key值：");
				scanf("%d",&w);
				i = InsertArc(L.Graph[num-1].G,v,w);
				if(i == OK) printf("\t\t\t插入弧成功！\n");
				else printf("\t\t\t插入弧失败！");
				getchar();
				getchar();
				break;

			case 10:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("\t\t\t请输入你要删除的弧头的key值：");
				scanf("%d",&v);
				printf("\t\t\t请输入你要删除的弧尾的key值：");
				scanf("%d",&w);
				i = DeleteArc(L.Graph[num-1].G,v,w);
				if(i == OK) printf("\t\t\t删除弧成功！\n");
				else printf("\t\t\t删除弧失败！");
				getchar();
				getchar();
				break;

			case 11:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				DFSTraverse(L.Graph[num-1].G,visit);
				printf("\t\t\t深度优先搜索遍历完成！\n");
				getchar();
				getchar();
				break;

			case 12:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				BFSTraverse(L.Graph[num-1].G,visit);
				printf("\t\t\t广度优先搜索遍历完成！\n");
				getchar();
				getchar();
				break;
				
			case 13:
	   			if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("输入文件名：");
				scanf("%s",filename) ;
				SaveGraph(L.Graph[num-1].G,filename);
				printf("\t\t\t数据已经写入文件！\n");
				getchar();getchar();
				break;
		
			case 14:
	   			if (L.Graph[num-1].G.vexnum != 0)
	  		 	{
	   				printf("\t\t\t图已存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("请输入新图的名称！\n");
	   			scanf("%s",L.Graph[num-1].name);
	   			getchar();
	   			L.length++;
				printf("输入文件名：");
				scanf("%s",filename) ;
				LoadGraph(L.Graph[num-1].G,filename);
				printf("\t\t\t文件已经载入图！\n");
				getchar();getchar();
				break;
				
			case 15:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
			
				printf("\t\t\t请输入你要查询的顶点的key值：");
				scanf("%d",&v);
				printf("\t\t\t请输入你要查询的距离：");
				scanf("%d",&k);
				lx=LocateVex(L.Graph[num-1].G,v);
				if (lx==-1)
	   			{
	   				printf("\t\t\t查询的有顶点不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				xy= VerticesSetLessThanK(L.Graph[num-1].G,v,k);
				if(xy == 0) printf("\t\t\t无距离小于k的顶点！\n");
				else  printf("\t\t\t有%d个小于%d的顶点！\n",xy,k);
				
				getchar();
				getchar();
				break;
				
			case 16:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
			
				printf("\t\t\t请输入你要查询的第一个顶点的key值：");
				scanf("%d",&v);
				printf("\t\t\t请输入你要查询的第二个顶点的key值：");
				scanf("%d",&w);
				lx=LocateVex(L.Graph[num-1].G,v);
				rx=LocateVex(L.Graph[num-1].G,w);
				if (lx==-1||rx==-1)
	   			{
	   				printf("\t\t\t查询的有顶点不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				xy= ShortestPathLength(L.Graph[num-1].G,v,w);
				if(xy == 0) printf("\t\t\t两个顶点为同一个！\n");
				else if(xy==INF) printf("\t\t\t两个顶点不连通！");
				else  printf("\t\t\t两个顶点间最小路径和为%d！",xy);
				getchar();
				getchar();
				break;
				
				
				
			case 17:
				if (L.Graph[num-1].G.vexnum == 0)
	   			{
	   				printf("\t\t\t图不存在！\n");
	   				getchar();getchar();
	   				break;
				}
	
				printf("\t\t\t该图一共有%d个连通分量！\n",ConnectedComponentsNums(L.Graph[num-1].G));
				getchar();
				getchar();
				break;
				
			case 18:
					printf("\t\t\t当前图为第%d个\n",num);
					printf("\t\t\t输入图的序号(1~20)：");
					scanf("%d",&num); 
					printf("\t\t\t图已经切换为第%d个图！\n",num);
					getchar();getchar();
					break;
		
			case 19:
					printf("\t\t\t输入图的名称：");
					char gx[20];
					scanf("%s",gx);
					if(GraphSearch(gx)!=-1)
					printf("\t\t\t该图序号为%d！\n",GraphSearch(gx));
					else 
					printf("\t\t\t该图不存在！\n");
					getchar();getchar();
					break;

			default://确保输入的数字有意义
				printf("\t\t\t请输入[0~19]实现菜单功能");
				break;
		}//end of switch
	}//end of while
				

	printf("\t\t\t欢迎下次使用本系统！\n");
	return 0;
}


#define MAX_VERTEX_NUM 20
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	int i=0,flag=0;
	while(V[i].key!=-1){
		flag=1;
		if(i>=MAX_VERTEX_NUM) return ERROR;//超过20判错
		G.vertices[i].data=V[i];
		G.vertices[i].firstarc=NULL;
		i++;
	}//添加头结点
	if(!flag) return ERROR;//输出数据错时 
	G.vexnum=i;
	for(i=0;i<G.vexnum;i++) {
		for(int j=0;j<G.vexnum;j++) {
			if(V[i].key==V[j].key&&i!=j)
				return ERROR;//节点值查重
		}
	}
	i=0;
	ArcNode *p;
    int fir,sec;
	G.arcnum=0;//放在前面，以免后面的都直接跳过了，这个又没有赋值（写报告）
	while(VR[i][0]!=-1){
		G.arcnum++;
		fir=-1;
		for(int j=0;j<G.vexnum;j++)
			if(VR[i][0]==G.vertices[j].data.key){
				fir=j;
				break;
			}//找节点编号
		if(fir==-1) return ERROR;//节点不存在
        sec=-1;
		for(int j=0;j<G.vexnum;j++)
			if (VR[i][1]==G.vertices[j].data.key){
				sec=j;
				break;
			}
        if(sec==-1) return ERROR;

		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=sec;
		p->nextarc=G.vertices[fir].firstarc;//首接
		G.vertices[fir].firstarc=p;

        p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=fir;
		p->nextarc=G.vertices[sec].firstarc;
		G.vertices[sec].firstarc=p;//无向图对称存储

		i++;
	}//添加边结点
    return OK;
    /********** End **********/
}


status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<G.vexnum;i++){
        ArcNode*p=G.vertices[i].firstarc,*q;//q是记录位置的名，q前记得加*（进报告）
        while(p){
            q=p->nextarc;
            free(p);
            p=q;
        }
    }
    G.vexnum = 0;//边点置零
	G.arcnum = 0;//不用回收头节点数组
    return OK;
    /********** End **********/
}


int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
        int fir=-1;
    	for(int j=0;j<G.vexnum;j++)
			if(u==G.vertices[j].data.key){
				fir=j;
				break;
			}//找节点编号
		return fir;
    /********** End **********/
}


status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=LocateVex(G,u);
	if(i!=-1) {
        if(G.vertices[i].firstarc)return G.vertices[i].firstarc->adjvex;//编号
        else return -1;
	} else return -1;

    /********** End **********/
}


int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
	if(i!=-1&&j!=-1) {
        ArcNode*p=G.vertices[i].firstarc;
        while(p){
            if(p->adjvex==j){//adjvex是位序，w是值(写报告)
                if(p->nextarc!=NULL)return p->nextarc->adjvex;//检验有无下一个邻接点（写报告）
                else return -1;
            } 
            p=p->nextarc;
        }
       return -1; 
	} else return -1;
    /********** End **********/
}


status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i=0;i<G.vexnum;i++){
        if(v.key==G.vertices[i].data.key) return ERROR;//结构体比较不可以直接
    }
    G.vexnum++;
    if(G.vexnum>20) return ERROR;
    G.vertices[G.vexnum-1].data=v;//结构体赋值可以直接
    return OK;

    /********** End **********/
}



status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vertices[0].data.key != -1 && G.vertices[1].data.key == -1) return ERROR;//不能删成空表

    int  x;
	x=LocateVex(G, v);
	if(x==-1) return ERROR;//没找到

    ArcNode *p,*q;
	p=G.vertices[x].firstarc;
	while(p){
		q=p;
		p=p->nextarc;
		free(q);
		G.arcnum--;
	}
	

	for(int i=x;i<G.vexnum;i++)//删头节点
		G.vertices[i]=G.vertices[i+1];
    G.vexnum--;

	for(int i=0;i<G.vexnum;i++){
		p=G.vertices[i].firstarc;
		while(p) {
			if(p->adjvex==x){
				if(p==G.vertices[i].firstarc){//删首个节点特殊情况
					G.vertices[i].firstarc=p->nextarc;
					free(p);
					p = G.vertices[i].firstarc;//不能break,因为要使序号大的节点序号减一
				}else{
					q->nextarc=p->nextarc;
					free(p);
					p=q->nextarc;
				}
			}else{
				if(p->adjvex>x)//大的节点序号要减1
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
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
    if(i==-1||j==-1) return ERROR;//不存在该点
    ArcNode *p,*q;
    p=G.vertices[i].firstarc;
    while(p){
		if(p->adjvex==j)return ERROR;
		p=p->nextarc;
	}//已经存在该弧
    G.arcnum++;
    q=G.vertices[i].firstarc;
    p=(ArcNode*)malloc(sizeof(ArcNode));//记得分配空间
    p->adjvex=j;
    p->nextarc=q;
    G.vertices[i].firstarc=p;
    q=G.vertices[j].firstarc;
    p=(ArcNode*)malloc(sizeof(ArcNode));//记得分配空间
    p->adjvex=i;
    p->nextarc=q;
    G.vertices[j].firstarc=p;
    return OK;
    
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
    if(i==-1||j==-1) return ERROR;//不存在该点
    int flag=0;
    ArcNode *p,*q=NULL,*t;
    p=G.vertices[i].firstarc;
    while(p){
		if(p->adjvex==j){
            if(p==G.vertices[i].firstarc){
                G.vertices[i].firstarc=p->nextarc;//删除首个，特殊情况（写报告）
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
                G.vertices[j].firstarc=p->nextarc;//删除首个，特殊情况（写报告）
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
    }else return ERROR;//没找到该边

    /********** End **********/
}

void DFS(ALGraph G, int v) {
	visited[v]=1;
	VisitFunc(G.vertices[v].data);
	for(int w=FirstAdjVex(G,G.vertices[v].data.key);w>= 0;w=NextAdjVex(G,G.vertices[v].data.key,w))
		if(!visited[w]) DFS(G,w);
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	VisitFunc=visit;
	for(int i=0;i<G.vexnum;i++) visited[i]=0;
	for(int i=0;i<G.vexnum;i++)
		if(!visited[i]) DFS(G,i);
    /********** End **********/
}


status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    VisitFunc=visit;
    for(int i=0;i<G.vexnum;i++){
       if(!visited[i]){
        visited[i]=1;
        q.push(G.vertices[i].data);//从0开始
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
	for(int i=0;i<G.vexnum;i++) visited[i]=0;//要重新初始化 
}

//访问节点
void visit(VertexType v) {
	printf("               key = %d,others = %s\n",v.key,v.others);
}


 //将图中关系保存在VR数组中
 
void WArc(int VR[][2], ArcNode *p, int &cnt, int i) {
	if(p==NULL) return;
	if(p->nextarc) WArc(VR, p->nextarc, cnt, i);
	for(int j=0;j<cnt;j++)//无向边不计对称重复信息
		if(VR[j][1]==i&&VR[j][0]==p->adjvex) 
			return;
	VR[cnt][0]=i;
	VR[cnt++][1]=p->adjvex;
}



status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    int VR[100][2]= {0};
    FILE* fp=fopen(FileName,"w");
	int cnt=0;//记录边条数
	for(int i=0;i<G.vexnum;i++){
		fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
	}
	fprintf(fp,"-1 nil ");//写入顶点信息

	for(int i=0; i<G.vexnum; i++) {//边信息存入数组
		WArc(VR, G.vertices[i].firstarc, cnt, i);
	}
	int x,y;
	for(int i=0;i<cnt;i++) {//写入边信息
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
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE* fp=fopen(FileName,"r");
	int i, j, k;
	char str[20];
	VertexType V[20];
	KeyType VR[100][2];
	i=0;
	do{
        fscanf(fp,"%d %s ",&V[i].key,V[i].others);
    }while(!(V[i++].key<0));//读取顶点信息，
	i=0;
	while(fscanf(fp,"%d %d ", &VR[i++][0], &VR[i][1])!=EOF);
	fclose(fp);//读取边信息

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
			printf("\t\t\t%d到%d\n",G.vertices[x].data.key,G.vertices[i].data.key);
		}
	}
	return cnt;
}
