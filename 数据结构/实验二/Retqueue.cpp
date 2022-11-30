#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;

//队列
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
void PrintQueue(SqQueue &Q)
{
    printf("The content of queue is\n");
    for (int i = Q.front; i != Q.rear; i = (i + 1) % MAXSIZE)
        printf("%d ", Q.data[i]);
    printf("\n");
}
//栈
typedef struct
{
    ElemType *base; 
    ElemType *top;  
    int StackSize;  
} SqStack;

int InitStack(SqStack &S)
{
    S.base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!S.base)
    {
        return 0;
    }
    S.top = S.base;                
    S.StackSize = STACK_INIT_SIZE; 
    return 1;
}

bool judgeNull(SqStack &s)
{
    if (s.top == s.base)
        return true;
    else
        return false;
}

bool judgeFull(SqStack &s)
{
    if (s.top - s.base == s.StackSize)
        return true;
    else
        return false;
}

int Push(SqStack &s, ElemType e)
{
    ElemType *p;
    if (s.top - s.base == s.StackSize)
    {
        p = (ElemType *)realloc(s.base, (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(ElemType));
        if (!p)
        {
            return 0;
        }
        s.base = p;
        s.top = s.base + s.StackSize;
        s.StackSize += STACKINCREMENT;
    }
    *(s.top) = e;
    s.top++;
    return 1;
}

int Pop(SqStack &s, ElemType &e)
{
    if (s.top != s.base)
    {
        s.top--;
        e = *(s.top);
    }
    else
    {
        return 0;
    }
    return e;
}

int main()
{
    ElemType arr[MAXSIZE * 10];
    ElemType length;
    ElemType e;
    SqQueue queue;
    SqStack stack;

    InitQueue(queue);
    InitStack(stack);
    printf("Now, the MAXQISIZE of queue is %d\n", MAXSIZE);
    printf("Please enter some numbers, end with -1:");
    for (int i = 0; i < MAXSIZE * 10; i++)
    {
        scanf("%d", &arr[i]);
        if (arr[i] == -1)
        {
            length = i;
            break;
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (EnQueue(queue, arr[i]))
            printf("%d enqueue\n", arr[i]);
        else
            printf("queue full! %d can't enQueue.\n", arr[i]);
    }
    PrintQueue(queue);
    for (int i = queue.front; i != queue.rear; i = (i + 1) % MAXSIZE)
    {
        if (DeQueue(queue, e))
        {
            printf("%d dequeue, and push stack.\n",e);
            Push(stack, e);
        }
    }
    while (!judgeNull(stack))
    {
        e = Pop(stack, e);
        EnQueue(queue, e);
        printf("%d pop from stack, and enter the queue\n", e);
    }
    PrintQueue(queue);
}