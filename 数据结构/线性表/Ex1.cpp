//用递归实现单链表的输出
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

//用递归函数实现时，单链表不带头结点

//递归实现输出单链表
void Creatlist(LinkList &L, int n)
{
    if (n == 0)
        L = NULL;
    else
    {
        L = (LinkList)malloc(sizeof(LNode));
        if (!L)
            exit(0);
        scanf("%d", &(L->data));
        Creatlist(L->next, n - 1);
    }
}

void Print_Twd(LinkList &L) //递归正向遍历
{
    if (L == NULL)
        return;
    printf("%d\n", L->data);
    Print_Twd(L->next);
}
//递归实现逆序输出单链表内容
void Print_Bk(LinkList &L)
{
    if (L == NULL)
        return;
    Print_Bk(L->next);
    printf("%d\n", L->data);
}
//递归实现单链表的转置
LinkList pre=NULL;
LinkList reverse(LinkList &L)
{
    if(L)
    {
        LinkList temp = L->next;
        L->next=pre;
        pre=L;
        reverse(temp);
    }
    else
        return pre;
}

int main()
{
    LinkList L;
    int length;
    printf("请输入链表的长度：\n");
    scanf("%d", &length);
    printf("请输入你想放入链表的数：\n");
    Creatlist(L, length);
    printf("正向遍历输出：\n");
    Print_Twd(L);
    printf("反向遍历输出：\n");
    Print_Bk(L);
    printf("转置之后：\n");
    L=reverse(L);
    Print_Twd(L);
    return 0;
}