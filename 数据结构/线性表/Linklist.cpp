//˳���
#include <stdio.h>
#include <malloc.h>

typedef struct list
{
    int *data;
    int len;
}list;
//��ʼ��
void begin(list & l,int n)
{
    int x;
    l.data=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&x);
        l.data[i]=x;
    }
    l.len=n;
}
//�����Ա�LA��ɾ����i ��Ԫ��
void Delete(list &x,int i)
{
    int j;
    if(i<1||i>x.len) return ;
    for(j=i;j<x.len;j++)
    {
        x.data[j-1]=x.data[j];
    }
    x.len--;
}

//��Ԫ��e���뵽���Ա�LB�еĵ�i��Ԫ��֮��
void insert(list &x,int e,int i)
{
    int j;
    if(i<1||i>x.len) return ;
    x.data=(int*)realloc(x.data,(x.len+1)*sizeof(int));
    for(j=x.len;j>i;j--)
    {
        x.data[j]=x.data[j-1];
    }
    x.len++;
    x.data[i]=e;
}
//�ж�list����û��e���Ԫ��
bool pd(list &x,int &e)
{
	int i;
	for(i=0;i<x.len;i++)
	{
		if(e==x.data[i])
		  return true; 
		else
		  return false;
	}
	
} 
//�ϲ�
void hb(list &l1,list &l2)
{
    for(int i=0;i<l2.len;i++)
    {
        if(!pd(l1,l2.data[i]))
        {
            l1.data=(int*)realloc(l1.data,(l1.len+1)*sizeof(int));
            l1.data[l1.len]=l2.data[i];
            l1.len++;
        }
    }
}
//���
void print(list &l)
{
    int i;
	for(i=0;i<l.len;i++)
	{
		printf("%d",l.data[i]);
        printf(" ");
	}
    printf("\n");
}

int main()
{
    list L1,L2;
    int n,m,x,y;

    printf("������L1��Ԫ�ظ���:");
    scanf("%d",&n);
    begin(L1,n);
    print(L1);

    printf("������L2��Ԫ�ظ���:");
    scanf("%d",&n);
    begin(L2,n);
    print(L2);

    printf("����ɾ��L1�еڼ���Ԫ��:");
    scanf("%d",&x);
    Delete(L1,x);
    print(L1);

    printf("������L2�еڼ���λ�ò���3:");
    scanf("%d",&y);
    insert(L2,3,x);
    print(L2);

    printf("�ϲ�L1��L2�������:");
    hb(L1,L2);
    print(L1);
}

