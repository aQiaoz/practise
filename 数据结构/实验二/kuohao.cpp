#include <stdio.h>
#include <stdlib.h>

#define MaxSize 50

typedef char ElemType;
typedef struct
{
    ElemType data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S)
{
    S.top = -1;
}

bool StackEmpty(SqStack S)
{
    if (S.top == -1)
            return true;
    else
            return false;
}

bool Push(SqStack &S, ElemType e)
{
    if (S.top == MaxSize - 1)
            return false;
    S.data[++S.top] = e;
    return true;
}

bool Pop(SqStack &S, ElemType &e)
{
    if (S.top == -1)
            return false;
    e = S.data[S.top--];
    return true;
}

bool kuohaoCheck(ElemType str[], int lenth)
{
    SqStack S;
    InitStack(S);
    for (int i = 0; i < lenth; ++i)
    {
        if (str[i] == '(')
        {
            Push(S, str[i]);
        }
        if (str[i] == ')')
        {
            if (StackEmpty(S))
                    return false;
            ElemType e;
            Pop(S, e);
        }
    }
    return StackEmpty(S);
}
void clear(ElemType str[],int lenth)
{
    for (int i = 0; i < lenth; ++i)
        str[i]='\0';
}
int main()
{
    ElemType x='y';
    ElemType str[MaxSize];
    while(x=='y')
    {
        printf("please enter parentheses:");
        gets(str);
        if(kuohaoCheck(str,MaxSize)) 
            printf("Match");
        else 
            printf("Not match");
        printf("\n");
        printf("Do you want to test again(y or n):");
        scanf("%c",&x);
        clear(str,MaxSize);
        getchar();
    }
}
