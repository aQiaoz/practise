/* 
����������
ǰ�᣺���ö��������еĿ�ָ����
�C>���ĳ����������Ϊ�գ��򽫿յ�����ָ�����Ϊָ����ǰ����
���ĳ�����Һ���Ϊ�գ��򽫿յ��Һ���ָ�����Ϊָ������
�C���ָı�ָ���ָ���Ϊ"����"
 */
#include <stdio.h>
#include <stdlib.h>

typedef int TElemType; 

typedef struct BiTNode
{
    TElemType data;         /* �ڵ����� */
    struct BiTNode *lchild; /* ���� */
    struct BiTNode *rchild; /* �Һ��� */
    int lTag;				/* ����-������ʶ */
    int rTag;				/* �Һ���-������ʶ */
} BiTNode;

