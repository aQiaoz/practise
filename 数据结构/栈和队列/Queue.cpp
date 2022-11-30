#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*链式队列结点*/
typedef int ElemType;
typedef int Status;

typedef struct Node{
	ElemType data;
	struct Node *next;
}LinkNode;

/*链式队列*/
typedef struct{
	LinkNode *front, *rear;	//队列的队头和队尾指针
}LinkQueue;

void InitQueue(LinkQueue *Q){
	Q->front = Q->rear = (LinkNode* )malloc(sizeof(LinkNode));	//建立头结点
	Q->front->next = NULL;	//初始为空
}

Status EnQueue(LinkQueue *Q, ElemType e){
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;	//把拥有元素e新结点s赋值给原队尾结点的后继
	Q->rear = s;	//把当前的s设置为新的队尾结点
	return 1;
}

/*若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR*/
Status DeQueue(LinkQueue *Q, ElemType *e){
	LinkNode *p;
	if(Q->front == Q->rear){
		return 0;
	}
	p = Q->front->next;	//将欲删除的队头结点暂存给p
	*e = p->data;	//将欲删除的队头结点的值赋值给e
	Q->front->next = p->next;	//将原队头结点的后继赋值给头结点后继
	//若删除的队头是队尾，则删除后将rear指向头结点
	if(Q->rear == p){	
		Q->rear = Q->front;
	}
	free(p);
	return 1;
}

/* 
循环队列
 */

#define MAXSIZE 50  //定义元素的最大个数
/*循环队列的顺序存储结构*/
typedef struct{
    ElemType *data;
    int front;  //头指针
    int rear;   //尾指针,若队列不空，指向队列尾元素的下一个位置
}SqQueue;

/*初始化一个空队列Q*/
Status InitQueue(SqQueue &Q){
    Q.data = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
	if(!Q.data) exit(0);
    Q.front = 0;
    Q.rear = 0;
    return 1;
}

int QueueLength(SqQueue &Q){
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/*若队列未满，则插入元素e为Q新的队尾元素*/
Status EnQueue(SqQueue &Q, ElemType e){
    if((Q.rear + 1) % MAXSIZE == Q.front){
        return 0;   //队满
    }
    Q.data[Q.rear] = e;   //将元素e赋值给队尾
    Q.rear = (Q.rear + 1) % MAXSIZE;  //rear指针向后移一位置，若到最后则转到数组头部
    return 1;
}
/*判队空*/
bool isEmpty(SqQueue &Q){
    if(Q.rear == Q.front){
        return true;
    }else{
        return false;
    }
}
/*若队列不空，则删除Q中队头元素，用e返回其值*/
Status DeQueue(SqQueue &Q, ElemType *e){
    if(isEmpty(Q)){
        return 0;   //队列空的判断
    }
    *e = Q.data[Q.front]; //将队头元素赋值给e
    Q.front = (Q.front + 1) % MAXSIZE;    //front指针向后移一位置，若到最后则转到数组头部
	return 1;
}


