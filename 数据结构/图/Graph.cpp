#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* 图的邻接表表示法 */

#define MaxVertexNum 100 /* 最大顶点数设为100 */
typedef int Vertex;		 /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;	 /* 边的权值设为整型 */
typedef char DataType;	 /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode
{
	Vertex V1, V2;	   /* 有向边<V1, V2> */
	WeightType Weight; /* 权重 */
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
	Vertex AdjV;		/* 邻接点下标 */
	WeightType Weight;	/* 边权重 */
	PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode
{
	PtrToAdjVNode FirstEdge; /* 边表头指针 */
	DataType Data;			 /* 存顶点的数据 */
							 /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum];	 /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;	   /* 顶点数 */
	int Ne;	   /* 边数   */
	AdjList G; /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

LGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接表头指针 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	/* 插入边 <V1, V2> */
	/* 为V2建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* 将V2插入V1的表头 */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* 若是无向图，还要插入边 <V2, V1> */
	/* 为V1建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	/* 将V1插入V2的表头 */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	printf("请输入顶点数：\n");
	scanf("%d", &Nv);		 /* 读入顶点个数 */
	Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

	printf("请输入边数：\n");
	scanf("%d", &(Graph->Ne)); /* 读入边数 */
	if (Graph->Ne != 0)
	{											/* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		printf("请输入相关顶点以及权重：\n");
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdge(Graph, E);
		}
	}

	/* 如果顶点有数据的话，读入数据 */
	printf("请输入相关的顶点数据：\n");
	for (V = 0; V < Graph->Nv; V++)
		scanf(" %c", &(Graph->G[V].Data));

	return Graph;
}

/* DFS */
void Visit(Vertex V)
{
	printf("正在访问顶点:%d\n", V);
}
bool Visited[MaxVertexNum];
/* Visited[]为全局变量，已经初始化为false */
void DFS(LGraph Graph, Vertex V)
{ /* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
	PtrToAdjVNode W;
	if (Visited[V])
		return;
	Visit(V);		   /* 访问第V个顶点 */
	Visited[V] = true; /* 标记V已访问 */

	for (W = Graph->G[V].FirstEdge; W; W = W->Next) /* 对V的每个邻接点W->AdjV */
		if (!Visited[W->AdjV])						/* 若W->AdjV未被访问 */
			DFS(Graph, W->AdjV);					/* 则递归访问之 */
}

void DFS_Main(LGraph Graph, Vertex V)
{
	for (int i = 0; i < MaxVertexNum; i++)
		Visited[i] = false;
	for (V; V < Graph->Nv; V++) /* 对V的每个邻接点W->AdjV */
		if (!Visited[V])		/* 若W->AdjV未被访问 */
			DFS(Graph, V);		/* 则递归访问之 */
}

/* BFS */
typedef int ElemType;
typedef int Status;

typedef struct Node
{
	ElemType data;
	struct Node *next;
} LinkNode;

/*链式队列*/
typedef struct
{
	LinkNode *front, *rear; //队列的队头和队尾指针
} LinkQueue;

void InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (LinkNode *)malloc(sizeof(LinkNode)); //建立头结点
	Q->front->next = NULL;									   //初始为空
}

void EnQueue(LinkQueue *Q, ElemType e)
{
	LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
	s->data = e;
	s->next = NULL;
	Q->rear->next = s; //把拥有元素e新结点s赋值给原队尾结点的后继
	Q->rear = s;	   //把当前的s设置为新的队尾结点
}

/*若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR*/
void DeQueue(LinkQueue *Q, ElemType e)
{
	LinkNode *p;
	if (Q->front == Q->rear)
	{
		return;
	}
	p = Q->front->next;		  //将欲删除的队头结点暂存给p
	e = p->data;			  //将欲删除的队头结点的值赋值给e
	Q->front->next = p->next; //将原队头结点的后继赋值给头结点后继
	//若删除的队头是队尾，则删除后将rear指向头结点
	if (Q->rear == p)
	{
		Q->rear = Q->front;
	}
	free(p);
}
bool QueueEmpty(LinkQueue *Q)
{
	return Q->front == Q->rear;
}

void BFS(LGraph Graph, Vertex V)
{ /* 以V为出发点对邻接表存储的图Graph进行BFS搜索 */
	for (int i = 0; i < MaxVertexNum; i++)
		Visited[i] = false;
	LinkQueue* queue;
	InitQueue(queue);
	printf("====");
	PtrToAdjVNode W;
	int u;
	for (int i = V; i < Graph->Nv; i++)
	{
		if (!Visited[i])
		{
			Visit(i);
			Visited[i] = true;
			EnQueue(queue, i);
			while (!QueueEmpty(queue))
			{
				DeQueue(queue, u);
				for (W = Graph->G[u].FirstEdge; W; W = W->Next) /* 对V的每个邻接点W->AdjV */
					if (!Visited[W->AdjV])
					{
						Visited[W->AdjV] = true;
						Visit(W->AdjV);
						EnQueue(queue, W->AdjV);
					}
			}
		}
	}
}

int main()
{
	LGraph graph;
	Vertex v;
	graph = BuildGraph();
	// printf("请输入DFS的出发点:\n");
	// scanf("%d", &v);
	// DFS_Main(graph, v);
	// printf("------------------------------------------\n");
	printf("请输入BFS的出发点:\n");
	scanf("%d", &v);
	BFS(graph, v);

	return 0;
}

// void BFS(LGraph Graph, Vertex V)
// { /* 以V为出发点对邻接表存储的图Graph进行BFS搜索 */
// 	for (int i = 0; i < MaxVertexNum; i++)
// 		Visited[i] = false;
// 	queue<int> q;
// 	PtrToAdjVNode W;
// 	int u;
// 	for(int i=V;i<Graph->Nv;i++)
// 	{
// 		if(!Visited[i])
// 		{
// 			Visit(i);
// 			Visited[i]=true;
// 			q.push(i);
// 			while(!q.empty())
// 			{
// 				u=q.front();
// 				q.pop();
// 				for (W = Graph->G[u].FirstEdge; W; W = W->Next) /* 对V的每个邻接点W->AdjV */
// 					if(!Visited[W->AdjV])
// 					{
// 						Visited[W->AdjV]=true;
// 						Visit(W->AdjV);
// 						q.push(W->AdjV);
// 					}

// 			}
// 		}
// 	}

// }