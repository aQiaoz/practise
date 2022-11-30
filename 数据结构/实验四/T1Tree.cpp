#include <stdio.h>
#include <stdlib.h>

enum Tag{Link,Thead};
typedef struct Tree
{
    char data;
    struct Tree *lchild;
    struct Tree *rchild;
    int LTag;
    int RTag;
} Tree, *BitTree;

void CreateLink(BitTree &T)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '.')
        T = NULL;
    else
    {
        T = (BitTree)malloc(sizeof(Tree));
        T->data = ch;
        CreateLink(T->lchild);
        CreateLink(T->rchild);
    }
}

void PostOrder(BitTree T)
{
    BitTree stack[100];
    int top = -1;
    BitTree p = T, r = NULL;

    while (p || top > -1)
    {
        if (p)/* �ߵ������ */
        {
            stack[++top] = p;
            p = p->lchild;        
        }
        else
        {
            p = stack[top]; /* ��ȡջ��Ԫ�� */
            if (p->rchild && p->rchild != r)/* ������������ڣ���û�б����ʹ��������ʵĽ�� */
            {
                p = p->rchild;
                stack[++top] = p;
                p = p->lchild;
            }
            else
            {
                p = stack[top--];
                printf("%c", p->data);
                r = p;
                p = NULL; //�����´ν���p������
            }
        }
    }
}
BitTree pre;
void TheadBinaryTree(BitTree p)
{
	if (p)
	{
		TheadBinaryTree(p->lchild);
		if (!p->lchild)   //��ָ����Ϊ���������� 
		{
			p->LTag = Thead;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->RTag = Thead;
			pre->rchild = p;
		}
		pre = p;
		TheadBinaryTree(p->rchild);
	}
}
void InOrderTheadBTree(BitTree &Thrt, BitTree T)
{
	//����ͷ���Thrt 
	if (!((Thrt) = (BitTree)malloc(sizeof(Tree)))) 
	{
		exit(0);
	}
	Thrt->LTag = Link;			//ͷ�������־λΪ0��ָ�� 
	Thrt->RTag = Thead;			//ͷ�����ұ�־λΪ1������ 
	Thrt->rchild = Thrt;  		//��ָ���ָ����
	if (!T) 
	{
		Thrt->lchild = Thrt;  //������Ϊ��ʱ��ָ��Ϊ�ޣ���ָ���� 
	}
	else
	{
		//�����������ڣ���ͷ����������������Ӧ������
		Thrt->lchild = T;       //��ͷָ��ָ�������T(T�д�ŵ���֮ǰ����Ķ�����)
		pre = Thrt;				//ͷ���Ϊǰ�� 
		TheadBinaryTree(T);		    //���������������������
		pre->rchild = Thrt;		//��ָ���ָ���� 
		pre->RTag = Thead;		//�ұ��λ����Ϊ����
		Thrt->rchild = pre;	
	}
}


void InOrderTraverse(BitTree Thrt)
{
	BitTree p;
	//Tָ��ͷ��㣬pָ������ 
	p = Thrt->lchild;
	while (p != Thrt)   //��p==T���������ɣ��ٴλص�ͷ��� 
	{
		while (p->LTag == Link) //�ҵ���ڵ�
		{
			p = p->lchild;		//ֱ���ҵ����������������������� 
		}
		printf("%c",p->data);        //�ҵ�������ߵĽ�㣬���
		while (p->RTag == Thead && p->rchild != Thrt)//��������� ��ʱ��ڵ���ҽڵ�Ӧ���Ǻ������
		{ 
			p = p->rchild;		 //ָ��������
			printf("%c",p->data); 	 //����������
		}
		p = p->rchild;			 //���ʸý����ҽ��
	}
}

int main()
{
    BitTree Thrt,T;
    CreateLink(T);
    PostOrder(T);
    printf("\n------������������------\n"); 
    InOrderTheadBTree(Thrt,T);
    InOrderTraverse(Thrt);
    return 0;
}