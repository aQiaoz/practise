#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

typedef int TElemType;
typedef int Status;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

Status CreateBiTree(BiTree &T)
{
    TElemType n;
    scanf("%d", &n);
    if (n == '#')
        T = NULL;
    else
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        T->data = n;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return 1;
}

//先序遍历--递归
Status PreOrderTraverse(BiTree T)
{
    if (T == NULL)
        return 1;
    else
    {
        printf("%d ", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

//中序遍历--递归
Status InOrderTraverse(BiTree T)
{
    if (T == NULL)
        return 1;
    else
    {
        PreOrderTraverse(T->lchild);
        printf("%d ", T->data);
        PreOrderTraverse(T->rchild);
    }
}
//后续遍历--递归
Status PostOrderTraverse(BiTree T)
{
    if (T == NULL)
        return 1;
    else
    {
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
        printf("%d ", T->data);
    }
}

//先序遍历--非递归
Status PrOrder(BiTree T)
{
    //空指针进栈方法
    BiTree p, q;
    stack<BiTree> tem;
    tem.push(T);
    while (!tem.empty())
    {
        while (tem.top() && p)
        {
            p = tem.top();
            printf("%d", &p->data);
            tem.push(p->lchild);
        }
        p = tem.top();
        tem.pop();
        if (!tem.empty())
        {
            p = tem.top();
            tem.pop();
            tem.push(p->rchild);
        }
    }

    //空指针不进栈方法
    p = T;
    while (p || !tem.empty())
    {
        if (p)
        {
            printf("%d", p->data);
            tem.push(p);
            p = p->lchild;
        }
        else
        {
            q = tem.top();
            tem.pop();
            p = q->rchild;
        }
    }
    return 1;
}

//中序遍历--非递归
Status InOrder(BiTree T)
{
    //空指针不进栈方法
    BiTree p, q;
    stack<BiTree> tem;
    p = T;
    while (p || !tem.empty())
    {
        if (p)
        {
            tem.push(p);
            p = p->lchild;
        }
        else
        {
            q = tem.top();
            tem.pop();
            printf("%d", q->data);
            p = q->rchild;
        }
    }
    return 1;

    //空指针进栈方法
    tem.push(T);
    while (!tem.empty())
    {
        while (tem.top() && p)
        {
            p = tem.top();
            tem.push(p->lchild);
        }
        p = tem.top();
        tem.pop();
        if (!tem.empty())
        {
            p = tem.top();
            printf("%d", &p->data);
            tem.pop();
            tem.push(p->rchild);
        }
    }
}

//后序遍历--非递归
Status PostOrder(BiTree T)
{
    BiTree p, q;
    stack<BiTree> tem;
    p = T;
    q = NULL; // q指向上次访问的节点
    while (p || tem.empty())
    {
        while (p)
        {
            tem.push(p);
            p = p->lchild;
        }
        p = tem.top();
        if (p->rchild == NULL || q == p->rchild)
        {
            printf("%d", &p->data);
            q = tem.top();
            tem.pop();
            p = NULL; //避免下次重新进入p的左子树
        }
        else
            p = p->rchild;
    }
}

//无论哪种时间复杂度和空间复杂度都是O(n)

//统计叶子节点数
void leaf1(BiTree T)
{
    int LeafCount;
    if (T != NULL)
    {
        leaf1(T->lchild);
        leaf1(T->rchild);
        if (T->lchild == NULL && T->rchild == NULL)
            LeafCount++;
    }
}
int leaf2(BiTree T)
{
    int LeafCount;
    if (T == NULL)
        LeafCount = 0;
    else if ((T->lchild == NULL) && (T->rchild == NULL))
        LeafCount = 1;
    else
        LeafCount = leaf2(T->lchild) + leaf2(T->rchild);
    return LeafCount;
}

//求二叉树深度
int PostTreeDepth(BiTree T)
{
    int hl, hr, max;
    if (T != NULL)
    {
        hl = PostTreeDepth(T->lchild);
        hr = PostTreeDepth(T->rchild);
        max = hl > hr ? hl : hr;
        return (max + 1);
    }
    else
        return 0;
}

//层次遍历
void LayerOrder(BiTree T)
{
    queue<BiTree> Q;
    BiTree p;
    Q.push(T);
    while (!Q.empty())
    {
        p = Q.front();
        Q.pop();
        printf("%d", p->data);
        if (p->lchild)
            Q.push(p->lchild);
        if (p->rchild)
            Q.push(p->rchild);
    }
}
