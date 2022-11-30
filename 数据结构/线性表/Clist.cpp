#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct Clist
{
	int data; //数据域   存放数据
	struct Clist* next;
//指针域存放下一个节点的地址（尾结点的next保存头结点的地址）
}Clist, * PClist;

void InitClist(Clist* plist)
{
	//assert

	//plist->data; // 数据域不处理
	plist->next = plist;
}

//头插法
bool Insert_head(PClist plist, int val)
{
	//assert
	//1.购买新节点
	Clist* pnewnode = (Clist*)malloc(1 * sizeof(Clist));
	assert(pnewnode != NULL); //assert判断式子是否为1
	pnewnode->data = val;//购买的新节点  处理完毕

	//2.找到插入位置  （头插  不用找）
	//3.插入
	pnewnode->next = plist->next;
	plist->next = pnewnode;

	return true;
}

//尾插法
bool Insert_tail(PClist plist, int val)
{
	//assert
	//1.购买新节点
	struct Clist* pnewnode = (struct Clist*)malloc(1 * sizeof(struct Clist));
	assert(pnewnode != NULL);
	pnewnode->data = val;//购买的新节点  处理完毕


	//2.找到插入位置(通过带前驱的for循环)
	struct Clist* p = plist;
	for (p; p->next != plist; p = p->next);
	//此时 for循环执行结束   p指向尾结点

	//3.插入
	pnewnode->next = p->next;
	p->next = pnewnode;

	return true;
}
int Get_length(PClist plist)
{
	//不带前驱的for循环 跑一遍就好
	int count = 0;

	for (struct Clist* p = plist->next; p != plist; p = p->next)
	{
		count++;
	}

	return count;
}

//中间插入
bool Insert_pos(PClist plist, int pos, int val)
{
	assert(plist != NULL);
	assert(pos >= 0 && pos <= Get_length(plist));


	//1.购买新节点
	struct Clist* pnewnode = (struct Clist*)malloc(1 * sizeof(struct Clist));
	assert(pnewnode != NULL);
	pnewnode->data = val;//购买的新节点  处理完毕


	//2.找到插入位置(通过带前驱的for循环)
	struct Clist* p = plist;
	for (int i = 0; i < pos; i++)
	{
		p = p->next;
	}
	//此时 for循环执行结束   p指向待插入的合适位置

	//3.插入
	pnewnode->next = p->next;
	p->next = pnewnode;

	return true;
}

//未完待续

