/* 
线索二叉树
前提：利用二叉链表中的空指针域
–>如果某个结点的左孩子为空，则将空的左孩子指针域改为指向其前驱；
如果某结点的右孩子为空，则将空的右孩子指针域改为指向其后继
–这种改变指向的指针称为"线索"
 */
#include <stdio.h>
#include <stdlib.h>

typedef int TElemType; 

typedef struct BiTNode
{
    TElemType data;         /* 节点数据 */
    struct BiTNode *lchild; /* 左孩子 */
    struct BiTNode *rchild; /* 右孩子 */
    int lTag;				/* 左孩子-线索标识 */
    int rTag;				/* 右孩子-线索标识 */
} BiTNode;

