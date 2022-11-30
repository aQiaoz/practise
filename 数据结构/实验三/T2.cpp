//寻找马鞍点，即行最小，列最大
#include <stdio.h>


int main()
{
    int m,n;
    scanf("%d %d",&m,&n);

    int arr[100][100];
    int maxc[100]={0};
    int minr[100]={0};
    for (int i = 0; i < m; i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&arr[i][j]);
            if(arr[i][j]>maxc[j])
            {
                maxc[j]=arr[i][j];
            }
            if(arr[i][j]<minr[i])
            {
                minr[i]=arr[i][j];
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==minr[i]&&arr[i][j]==maxc[j])
            {
                printf("(%d,%d)的%d是马鞍点\n",i,j,arr[i][j]);
            }
        }
    }
    return 0;

}

