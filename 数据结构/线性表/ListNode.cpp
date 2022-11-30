#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Linklist
{
	int data;
	Linklist *next;
} Linklist;

Linklist *creat()
{
	//尾插法
	Linklist *head = (Linklist *)malloc(sizeof(Linklist)); //创建头结点，并分配内存，需要的内存大小就是结构体的大小。别忘了在malloc前进行强制类型转换。（struct LinkList*）
	head->next = NULL;									   //头结点指针初始化
	Linklist *p;										   //创建p结点 p结点在尾插法中用于记录链表尾结点，将来插入结点的时候只需要向p结点后插入即可。
	p = head;											   // p结点指针赋值为头结点
	int n;												   //保存链表长度，即结点的个数。
	printf("请输入链表长度:\n");
	scanf("%d", &n);
	printf("输入数据:\n");
	for (int i = 0; i < n; i++) //循环创建结点
	{
		Linklist *s = (Linklist *)malloc(sizeof(Linklist)); //创建s结点，并分配内存
		scanf("%d", &s->data);								//给s结点赋值。
		//尾插法建立链表
		p->next = s;	//因为插完第一个结点后用p保存了上一个结点，所以再插结点时应该插在p节点后面，这就是尾插。
		s->next = NULL; //别忘了让插在尾部的s结点的指针指向NULL。
		p = s;			// p结点保存刚才的s结点；以保证p始终为链表的最后一个节点
	}
	//头插法
	// Linklist *head = (Linklist *)malloc(sizeof(Linklist)); //创建头结点，并分配内存，需要的内存大小就是结构体的大小。别忘了在malloc前进行强制类型转换。（struct LinkList*）
	// head->next = NULL;									   //头结点指针初始化										   //创建p结点 p结点在尾插法中用于记录链表尾结点，将来插入结点的时候只需要向p结点后插入即可。
	// int n;												   //保存链表长度，即结点的个数。
	// printf("请输入链表长度：\n");
	// scanf("%d", &n);
	// printf("输入数据：\n");
	// for (int i = 0; i < n; i++) //循环创建结点
	// {
	// 	Linklist *s = (Linklist *)malloc(sizeof(Linklist)); //创建s结点，并分配内存
	// 	scanf("%d", &s->data);//给s结点赋值。
	// 	//头插法建立链表
	// 	s->next=head->next;//将链表除链表头的所有节点连接在新建节点之后
	// 	head->next=s;//在让头结点指向新节点 注意：和上一语句顺序不能颠倒
	// }
	return head;
}
//打印输出
void print(Linklist *head)
{
	Linklist *p;
	p = head->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}

//按位序删除（带头结点）
bool ListDelete(Linklist *head, int i)
{
	int j = 0;
	if (i < 1)
		return false;
	Linklist *p = head;
	while (p != NULL && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if(p -> next == NULL)		//第i-1个结点之后已没有其他结点
		return false;
	Linklist *q = p->next;
	p->next = q->next;
	free(q);
	return true;
}
//按位序插入（带头结点）
bool ListInsert(Linklist *head,int i,int e)
{
    int j = 0;
	if (i < 1)
		return false;
	Linklist *p = head;
	while (p != NULL && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if(p -> next == NULL)		//第i-1个结点之后已没有其他结点
		return false;
	Linklist *s = (Linklist *)malloc(sizeof(Linklist));
    s->data=e;
	s->next=p->next;
	p->next=s;
	return true;
}
Linklist *reverse1(Linklist *head)
{
    Linklist *p,*q,*pr;
    p=head->next;
	q=NULL;
	head->next=NULL;
	while(p)
	{
		pr=p->next;
		p->next=q;
		q=p;
		p=pr;
	}
	head->next=q;
	return head;
}
Linklist *reverse2(Linklist *head)
{
    if(head==NULL||head->next==NULL){
		return head;
	}else{
		Linklist *pre=NULL;
		Linklist *mid=head;
		Linklist *end=head->next;
		while(true){
			mid->next=pre;
			if(end==NULL){
				break;
			}
			//整体右移 
			pre=mid;
			mid=end;
			end=end->next;
		}
		head=mid;//原来的头指针指向mid（因为此时mid为首元节点）
		return head; 
	}
}
Linklist *reverse3(Linklist *head)
{
    Linklist* newhead=(Linklist *)malloc(sizeof(Linklist));

	newhead->next=NULL;
	Linklist *p=head->next;
	while(p)
	{
	    Linklist* q=p->next;
		p->next = newhead->next;
		newhead->next=p;
		p=q;
	}
	return newhead;
}
int main()
{
	int m,n,x;
	Linklist *head = creat();
	print(head);
	printf("\n请输入你想删除的数的位置");
	scanf("%d",&m);
	ListDelete(head,m);
	print(head);
	printf("\n请输入你想插入的数的位置和值");
	scanf("%d %d",&n,&x);
	ListInsert(head,n,x);
	print(head);
	printf("\n倒置后的数组");
	head=reverse1(head);
	print(head);
    return 0;
}


//双向链表

typedef int LTType;
typedef struct ListNode
{
	struct ListNode* prev;
	LTType data;
	struct ListNode* next;
}LTNode;

//创建一个结点
LTNode* BuyListNode(LTType x)
{
	LTNode* node = (LTNode*)malloc(sizeof(LTNode));
	node->prev = NULL;
	node->data = x;
	node->next = NULL;
	return node;
}

//初始化链表
LTNode* ListInit()
{
	LTNode* phead = BuyListNode(-1);
	phead->prev = phead;
	phead->next = phead;

	return phead;
}

//在pos位置之前插入
void LTInsert(LTNode* pos, LTType x)
{
	assert(pos);

	LTNode* prev = pos->prev;
	LTNode* newnode = BuyListNode(x);
	prev->next = newnode;
	newnode->prev = prev;
	newnode->next = pos;
	pos->prev = newnode;
}

//无头单链表
typedef struct node {
	int data;
	struct node* next;
}NhNode;

NhNode* creatnode(int data) {
	NhNode* newnode = (NhNode*)malloc(sizeof(NhNode));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}
void insertbyhead(NhNode** list, int data) {
	NhNode* newnode = creatnode(data);
	newnode->next = (*list);
	(*list) = newnode;
}
void insertbytail(NhNode** list, int data) {
	NhNode* newnode = creatnode(data);
	NhNode* ptail = (*list);
	while (ptail->next) {
		ptail = ptail->next;
	}
	ptail -> next = newnode;
}



