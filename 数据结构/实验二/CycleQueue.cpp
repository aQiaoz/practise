#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
typedef int ElemType;

typedef struct
{
    ElemType *data;
    int front;
    int rear;
} SqQueue;

int InitQueue(SqQueue &Q)
{
    Q.data = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    if (!Q.data)
        exit(0);
    Q.front = 0;
    Q.rear = 0;
    return 1;
}

int QueueLength(SqQueue &Q)
{
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}


int EnQueue(SqQueue &Q, ElemType e)
{
    if ((Q.rear + 1) % MAXSIZE == Q.front)
    {
        return 0;
    }
    Q.data[Q.rear] = e;              
    Q.rear = (Q.rear + 1) % MAXSIZE;
    return 1;
}

bool isEmpty(SqQueue &Q)
{
    if (Q.rear == Q.front)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int DeQueue(SqQueue &Q, ElemType &e)
{
    if (isEmpty(Q))
    {
        return 0; 
    }
    e = Q.data[Q.front];               
    Q.front = (Q.front + 1) % MAXSIZE; 
    return 1;
}

int main()
{
    ElemType arr[MAXSIZE * 10];
    ElemType length;
    ElemType e;
    SqQueue queue;

    InitQueue(queue);
    printf("Please enter some numbers, end with 0:");

    for (int i = 0; i < MAXSIZE * 10; i++)
    {
        scanf("%d", &arr[i]);
        if (arr[i] == 0)
        {
            length = i;
            break;
        }
    }
    printf("Now, the MAXQISIZE of queue is %d\n", MAXSIZE);
    for (int i = 0; i < length; i++)
    {
        if (arr[i] > 0)
        {
            if (EnQueue(queue, arr[i]))
                printf("%d enqueue\n", arr[i]);
            else
                printf("queue full! %d can't enqueue\n", arr[i]);
        }

        if (arr[i] < 0)
        {
            if (DeQueue(queue, e))
                printf("%d dequeue\n", e);
            else
                printf("queue empty! Can't dequeue\n");
        }
    }
}