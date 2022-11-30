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
	//β�巨
	Linklist *head = (Linklist *)malloc(sizeof(Linklist)); //����ͷ��㣬�������ڴ棬��Ҫ���ڴ��С���ǽṹ��Ĵ�С����������mallocǰ����ǿ������ת������struct LinkList*��
	head->next = NULL;									   //ͷ���ָ���ʼ��
	Linklist *p;										   //����p��� p�����β�巨�����ڼ�¼����β��㣬�����������ʱ��ֻ��Ҫ��p������뼴�ɡ�
	p = head;											   // p���ָ�븳ֵΪͷ���
	int n;												   //���������ȣ������ĸ�����
	printf("������������:\n");
	scanf("%d", &n);
	printf("��������:\n");
	for (int i = 0; i < n; i++) //ѭ���������
	{
		Linklist *s = (Linklist *)malloc(sizeof(Linklist)); //����s��㣬�������ڴ�
		scanf("%d", &s->data);								//��s��㸳ֵ��
		//β�巨��������
		p->next = s;	//��Ϊ�����һ��������p��������һ����㣬�����ٲ���ʱӦ�ò���p�ڵ���棬�����β�塣
		s->next = NULL; //�������ò���β����s����ָ��ָ��NULL��
		p = s;			// p��㱣��ղŵ�s��㣻�Ա�֤pʼ��Ϊ��������һ���ڵ�
	}
	//ͷ�巨
	// Linklist *head = (Linklist *)malloc(sizeof(Linklist)); //����ͷ��㣬�������ڴ棬��Ҫ���ڴ��С���ǽṹ��Ĵ�С����������mallocǰ����ǿ������ת������struct LinkList*��
	// head->next = NULL;									   //ͷ���ָ���ʼ��										   //����p��� p�����β�巨�����ڼ�¼����β��㣬�����������ʱ��ֻ��Ҫ��p������뼴�ɡ�
	// int n;												   //���������ȣ������ĸ�����
	// printf("�����������ȣ�\n");
	// scanf("%d", &n);
	// printf("�������ݣ�\n");
	// for (int i = 0; i < n; i++) //ѭ���������
	// {
	// 	Linklist *s = (Linklist *)malloc(sizeof(Linklist)); //����s��㣬�������ڴ�
	// 	scanf("%d", &s->data);//��s��㸳ֵ��
	// 	//ͷ�巨��������
	// 	s->next=head->next;//�����������ͷ�����нڵ��������½��ڵ�֮��
	// 	head->next=s;//����ͷ���ָ���½ڵ� ע�⣺����һ���˳���ܵߵ�
	// }
	return head;
}
//��ӡ���
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

//��λ��ɾ������ͷ��㣩
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
	if(p -> next == NULL)		//��i-1�����֮����û���������
		return false;
	Linklist *q = p->next;
	p->next = q->next;
	free(q);
	return true;
}
//��λ����루��ͷ��㣩
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
	if(p -> next == NULL)		//��i-1�����֮����û���������
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
			//�������� 
			pre=mid;
			mid=end;
			end=end->next;
		}
		head=mid;//ԭ����ͷָ��ָ��mid����Ϊ��ʱmidΪ��Ԫ�ڵ㣩
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
	printf("\n����������ɾ��������λ��");
	scanf("%d",&m);
	ListDelete(head,m);
	print(head);
	printf("\n������������������λ�ú�ֵ");
	scanf("%d %d",&n,&x);
	ListInsert(head,n,x);
	print(head);
	printf("\n���ú������");
	head=reverse1(head);
	print(head);
    return 0;
}


//˫������

typedef int LTType;
typedef struct ListNode
{
	struct ListNode* prev;
	LTType data;
	struct ListNode* next;
}LTNode;

//����һ�����
LTNode* BuyListNode(LTType x)
{
	LTNode* node = (LTNode*)malloc(sizeof(LTNode));
	node->prev = NULL;
	node->data = x;
	node->next = NULL;
	return node;
}

//��ʼ������
LTNode* ListInit()
{
	LTNode* phead = BuyListNode(-1);
	phead->prev = phead;
	phead->next = phead;

	return phead;
}

//��posλ��֮ǰ����
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

//��ͷ������
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



