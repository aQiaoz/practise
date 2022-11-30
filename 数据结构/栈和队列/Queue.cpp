#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*��ʽ���н��*/
typedef int ElemType;
typedef int Status;

typedef struct Node{
	ElemType data;
	struct Node *next;
}LinkNode;

/*��ʽ����*/
typedef struct{
	LinkNode *front, *rear;	//���еĶ�ͷ�Ͷ�βָ��
}LinkQueue;

void InitQueue(LinkQueue *Q){
	Q->front = Q->rear = (LinkNode* )malloc(sizeof(LinkNode));	//����ͷ���
	Q->front->next = NULL;	//��ʼΪ��
}

Status EnQueue(LinkQueue *Q, ElemType e){
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;	//��ӵ��Ԫ��e�½��s��ֵ��ԭ��β���ĺ��
	Q->rear = s;	//�ѵ�ǰ��s����Ϊ�µĶ�β���
	return 1;
}

/*�����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR*/
Status DeQueue(LinkQueue *Q, ElemType *e){
	LinkNode *p;
	if(Q->front == Q->rear){
		return 0;
	}
	p = Q->front->next;	//����ɾ���Ķ�ͷ����ݴ��p
	*e = p->data;	//����ɾ���Ķ�ͷ����ֵ��ֵ��e
	Q->front->next = p->next;	//��ԭ��ͷ���ĺ�̸�ֵ��ͷ�����
	//��ɾ���Ķ�ͷ�Ƕ�β����ɾ����rearָ��ͷ���
	if(Q->rear == p){	
		Q->rear = Q->front;
	}
	free(p);
	return 1;
}

/* 
ѭ������
 */

#define MAXSIZE 50  //����Ԫ�ص�������
/*ѭ�����е�˳��洢�ṹ*/
typedef struct{
    ElemType *data;
    int front;  //ͷָ��
    int rear;   //βָ��,�����в��գ�ָ�����βԪ�ص���һ��λ��
}SqQueue;

/*��ʼ��һ���ն���Q*/
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

/*������δ���������Ԫ��eΪQ�µĶ�βԪ��*/
Status EnQueue(SqQueue &Q, ElemType e){
    if((Q.rear + 1) % MAXSIZE == Q.front){
        return 0;   //����
    }
    Q.data[Q.rear] = e;   //��Ԫ��e��ֵ����β
    Q.rear = (Q.rear + 1) % MAXSIZE;  //rearָ�������һλ�ã����������ת������ͷ��
    return 1;
}
/*�жӿ�*/
bool isEmpty(SqQueue &Q){
    if(Q.rear == Q.front){
        return true;
    }else{
        return false;
    }
}
/*�����в��գ���ɾ��Q�ж�ͷԪ�أ���e������ֵ*/
Status DeQueue(SqQueue &Q, ElemType *e){
    if(isEmpty(Q)){
        return 0;   //���пյ��ж�
    }
    *e = Q.data[Q.front]; //����ͷԪ�ظ�ֵ��e
    Q.front = (Q.front + 1) % MAXSIZE;    //frontָ�������һλ�ã����������ת������ͷ��
	return 1;
}


