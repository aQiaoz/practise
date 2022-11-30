//�õݹ�ʵ�ֵ���������
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

//�õݹ麯��ʵ��ʱ����������ͷ���

//�ݹ�ʵ�����������
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

void Print_Twd(LinkList &L) //�ݹ��������
{
    if (L == NULL)
        return;
    printf("%d\n", L->data);
    Print_Twd(L->next);
}
//�ݹ�ʵ�������������������
void Print_Bk(LinkList &L)
{
    if (L == NULL)
        return;
    Print_Bk(L->next);
    printf("%d\n", L->data);
}
//�ݹ�ʵ�ֵ������ת��
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
    printf("����������ĳ��ȣ�\n");
    scanf("%d", &length);
    printf("����������������������\n");
    Creatlist(L, length);
    printf("������������\n");
    Print_Twd(L);
    printf("������������\n");
    Print_Bk(L);
    printf("ת��֮��\n");
    L=reverse(L);
    Print_Twd(L);
    return 0;
}