//顺序表
#include <stdio.h>
#include <malloc.h>

typedef struct list
{
    int *data;
    int len;
}list;
//初始化
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
//从线性表LA中删除第i 个元素
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

//将元素e插入到线性表LB中的第i个元素之后
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
//判断list里有没有e这个元素
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
//合并
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
//输出
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

    printf("请输入L1的元素个数:");
    scanf("%d",&n);
    begin(L1,n);
    print(L1);

    printf("请输入L2的元素个数:");
    scanf("%d",&n);
    begin(L2,n);
    print(L2);

    printf("你想删除L1中第几个元素:");
    scanf("%d",&x);
    Delete(L1,x);
    print(L1);

    printf("你想在L2中第几个位置插入3:");
    scanf("%d",&y);
    insert(L2,3,x);
    print(L2);

    printf("合并L1和L2后的数组:");
    hb(L1,L2);
    print(L1);
}

