#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* ͼ���ڽӱ��ʾ�� */

#define MaxVertexNum 100 /* ��󶥵�����Ϊ100 */
typedef int Vertex;		 /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;	 /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;	 /* ����洢������������Ϊ�ַ��� */

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode
{
	Vertex V1, V2;	   /* �����<V1, V2> */
	WeightType Weight; /* Ȩ�� */
};
typedef PtrToENode Edge;

/* �ڽӵ�Ķ��� */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
	Vertex AdjV;		/* �ڽӵ��±� */
	WeightType Weight;	/* ��Ȩ�� */
	PtrToAdjVNode Next; /* ָ����һ���ڽӵ��ָ�� */
};

/* �����ͷ���Ķ��� */
typedef struct Vnode
{
	PtrToAdjVNode FirstEdge; /* �߱�ͷָ�� */
	DataType Data;			 /* �涥������� */
							 /* ע�⣺�ܶ�����£����������ݣ���ʱData���Բ��ó��� */
} AdjList[MaxVertexNum];	 /* AdjList���ڽӱ����� */

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;	   /* ������ */
	int Ne;	   /* ����   */
	AdjList G; /* �ڽӱ� */
};
typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */

LGraph CreateGraph(int VertexNum)
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӱ�ͷָ�� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	/* ����� <V1, V2> */
	/* ΪV2�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* ��V2����V1�ı�ͷ */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* ��������ͼ����Ҫ����� <V2, V1> */
	/* ΪV1�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	/* ��V1����V2�ı�ͷ */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	printf("�����붥������\n");
	scanf("%d", &Nv);		 /* ���붥����� */
	Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	printf("�����������\n");
	scanf("%d", &(Graph->Ne)); /* ������� */
	if (Graph->Ne != 0)
	{											/* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		printf("��������ض����Լ�Ȩ�أ�\n");
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge(Graph, E);
		}
	}

	/* ������������ݵĻ����������� */
	printf("��������صĶ������ݣ�\n");
	for (V = 0; V < Graph->Nv; V++)
		scanf(" %c", &(Graph->G[V].Data));

	return Graph;
}

/* DFS */
void Visit(Vertex V)
{
	printf("���ڷ��ʶ���:%d\n", V);
}
bool Visited[MaxVertexNum];
/* Visited[]Ϊȫ�ֱ������Ѿ���ʼ��Ϊfalse */
void DFS(LGraph Graph, Vertex V)
{ /* ��VΪ��������ڽӱ�洢��ͼGraph����DFS���� */
	PtrToAdjVNode W;
	if (Visited[V])
		return;
	Visit(V);		   /* ���ʵ�V������ */
	Visited[V] = true; /* ���V�ѷ��� */

	for (W = Graph->G[V].FirstEdge; W; W = W->Next) /* ��V��ÿ���ڽӵ�W->AdjV */
		if (!Visited[W->AdjV])						/* ��W->AdjVδ������ */
			DFS(Graph, W->AdjV);					/* ��ݹ����֮ */
}

void DFS_Main(LGraph Graph, Vertex V)
{
	for (int i = 0; i < MaxVertexNum; i++)
		Visited[i] = false;
	for (V; V < Graph->Nv; V++) /* ��V��ÿ���ڽӵ�W->AdjV */
		if (!Visited[V])		/* ��W->AdjVδ������ */
			DFS(Graph, V);		/* ��ݹ����֮ */
}

/* BFS */
typedef int ElemType;
typedef int Status;

typedef struct Node
{
	ElemType data;
	struct Node *next;
} LinkNode;

/*��ʽ����*/
typedef struct
{
	LinkNode *front, *rear; //���еĶ�ͷ�Ͷ�βָ��
} LinkQueue;

void InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (LinkNode *)malloc(sizeof(LinkNode)); //����ͷ���
	Q->front->next = NULL;									   //��ʼΪ��
}

void EnQueue(LinkQueue *Q, ElemType e)
{
	LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
	s->data = e;
	s->next = NULL;
	Q->rear->next = s; //��ӵ��Ԫ��e�½��s��ֵ��ԭ��β���ĺ��
	Q->rear = s;	   //�ѵ�ǰ��s����Ϊ�µĶ�β���
}

/*�����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR*/
void DeQueue(LinkQueue *Q, ElemType e)
{
	LinkNode *p;
	if (Q->front == Q->rear)
	{
		return;
	}
	p = Q->front->next;		  //����ɾ���Ķ�ͷ����ݴ��p
	e = p->data;			  //����ɾ���Ķ�ͷ����ֵ��ֵ��e
	Q->front->next = p->next; //��ԭ��ͷ���ĺ�̸�ֵ��ͷ�����
	//��ɾ���Ķ�ͷ�Ƕ�β����ɾ����rearָ��ͷ���
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
{ /* ��VΪ��������ڽӱ�洢��ͼGraph����BFS���� */
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
				for (W = Graph->G[u].FirstEdge; W; W = W->Next) /* ��V��ÿ���ڽӵ�W->AdjV */
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
	// printf("������DFS�ĳ�����:\n");
	// scanf("%d", &v);
	// DFS_Main(graph, v);
	// printf("------------------------------------------\n");
	printf("������BFS�ĳ�����:\n");
	scanf("%d", &v);
	BFS(graph, v);

	return 0;
}

// void BFS(LGraph Graph, Vertex V)
// { /* ��VΪ��������ڽӱ�洢��ͼGraph����BFS���� */
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
// 				for (W = Graph->G[u].FirstEdge; W; W = W->Next) /* ��V��ÿ���ڽӵ�W->AdjV */
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