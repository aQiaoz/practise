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
        if (p)/* 走到最左边 */
        {
            stack[++top] = p;
            p = p->lchild;        
        }
        else
        {
            p = stack[top]; /* 获取栈顶元素 */
            if (p->rchild && p->rchild != r)/* 如果右子树存在，且没有被访问过，是新鲜的结点 */
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
                p = NULL; //避免下次进入p左子树
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
		if (!p->lchild)   //左指针域为空则线索化 
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
	//创建头结点Thrt 
	if (!((Thrt) = (BitTree)malloc(sizeof(Tree)))) 
	{
		exit(0);
	}
	Thrt->LTag = Link;			//头结点的左标志位为0，指针 
	Thrt->RTag = Thead;			//头结点的右标志位为1，线索 
	Thrt->rchild = Thrt;  		//右指针回指本身
	if (!T) 
	{
		Thrt->lchild = Thrt;  //二叉树为空时，指向为无，回指本身 
	}
	else
	{
		//若二叉树存在，将头结点与二叉树进行相应的链接
		Thrt->lchild = T;       //让头指针指向二叉树T(T中存放的是之前输入的二叉树)
		pre = Thrt;				//头结点为前驱 
		TheadBinaryTree(T);		    //中序遍历进行中序线索化
		pre->rchild = Thrt;		//右指针回指本身 
		pre->RTag = Thead;		//右标记位设置为线索
		Thrt->rchild = pre;	
	}
}


void InOrderTraverse(BitTree Thrt)
{
	BitTree p;
	//T指向头结点，p指向根结点 
	p = Thrt->lchild;
	while (p != Thrt)   //若p==T，则遍历完成，再次回到头结点 
	{
		while (p->LTag == Link) //找到左节点
		{
			p = p->lchild;		//直到找到根结点的最左子树的最左结点 
		}
		printf("%c",p->data);        //找到了最左边的结点，输出
		while (p->RTag == Thead && p->rchild != Thrt)//线索化完成 此时左节点的右节点应该是后驱结点
		{ 
			p = p->rchild;		 //指向后驱结点
			printf("%c",p->data); 	 //输出后驱结点
		}
		p = p->rchild;			 //访问该结点的右结点
	}
}

int main()
{
    BitTree Thrt,T;
    CreateLink(T);
    PostOrder(T);
    printf("\n------中序线索化后------\n"); 
    InOrderTheadBTree(Thrt,T);
    InOrderTraverse(Thrt);
    return 0;
}