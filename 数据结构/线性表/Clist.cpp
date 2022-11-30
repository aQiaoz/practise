#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct Clist
{
	int data; //������   �������
	struct Clist* next;
//ָ��������һ���ڵ�ĵ�ַ��β����next����ͷ���ĵ�ַ��
}Clist, * PClist;

void InitClist(Clist* plist)
{
	//assert

	//plist->data; // �����򲻴���
	plist->next = plist;
}

//ͷ�巨
bool Insert_head(PClist plist, int val)
{
	//assert
	//1.�����½ڵ�
	Clist* pnewnode = (Clist*)malloc(1 * sizeof(Clist));
	assert(pnewnode != NULL); //assert�ж�ʽ���Ƿ�Ϊ1
	pnewnode->data = val;//������½ڵ�  �������

	//2.�ҵ�����λ��  ��ͷ��  �����ң�
	//3.����
	pnewnode->next = plist->next;
	plist->next = pnewnode;

	return true;
}

//β�巨
bool Insert_tail(PClist plist, int val)
{
	//assert
	//1.�����½ڵ�
	struct Clist* pnewnode = (struct Clist*)malloc(1 * sizeof(struct Clist));
	assert(pnewnode != NULL);
	pnewnode->data = val;//������½ڵ�  �������


	//2.�ҵ�����λ��(ͨ����ǰ����forѭ��)
	struct Clist* p = plist;
	for (p; p->next != plist; p = p->next);
	//��ʱ forѭ��ִ�н���   pָ��β���

	//3.����
	pnewnode->next = p->next;
	p->next = pnewnode;

	return true;
}
int Get_length(PClist plist)
{
	//����ǰ����forѭ�� ��һ��ͺ�
	int count = 0;

	for (struct Clist* p = plist->next; p != plist; p = p->next)
	{
		count++;
	}

	return count;
}

//�м����
bool Insert_pos(PClist plist, int pos, int val)
{
	assert(plist != NULL);
	assert(pos >= 0 && pos <= Get_length(plist));


	//1.�����½ڵ�
	struct Clist* pnewnode = (struct Clist*)malloc(1 * sizeof(struct Clist));
	assert(pnewnode != NULL);
	pnewnode->data = val;//������½ڵ�  �������


	//2.�ҵ�����λ��(ͨ����ǰ����forѭ��)
	struct Clist* p = plist;
	for (int i = 0; i < pos; i++)
	{
		p = p->next;
	}
	//��ʱ forѭ��ִ�н���   pָ�������ĺ���λ��

	//3.����
	pnewnode->next = p->next;
	p->next = pnewnode;

	return true;
}

//δ�����

