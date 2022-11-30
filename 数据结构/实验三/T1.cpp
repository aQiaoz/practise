#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    char c;
    int num;
} Node;

typedef struct
{
    Node *ch;
    int length;
} HString;

void Assign(HString &T,char *chars)
{
    int i;
    char *c;
    if(T.ch) free(T.ch);
    for(i=0,c=chars;*c;++i,++c);
    if(!i) {T.ch=NULL; T.length=0;}
    else
    {
        T.ch=(Node*)malloc(i*sizeof(Node));
        for (int j = 0; j < i; j++)
        {
            for (int m = 0; m<j; m++)
            {
                if(chars[j]==T.ch[m].c)
                {
                    T.ch[m].num++;
                    break;
                }
                if(m=j-1)
                {
                    for(int n=0;n<j;n++)
                    {
                        if(!T.ch[n].c)
                        {
                            T.ch[n].c=chars[j];
                            T.length++;
                            break;
                        }
                    }
                }
            }   
        }  
    }
}


int main()
{
    // int num[128]={0};
    // char str[200];

    // printf("Ç×ÊäÈë×Ö·û´®£º\n");
    // gets(str);
    // for(int i=0;str[i]!='\0';i++)
    //     num[str[i]]++;
    // for(int i=0;i<128;i++)
    //     if(num[i]!=0)
    //         printf("%c:%d\n",i,num[i]);
    // return 0;

    HString str;
    char *chars;
    printf("Ç×ÊäÈë×Ö·û´®£º\n");
    gets(chars);
    Assign(str,chars);
    for(int i=0;i<str.length;i++)
    {
        printf("%c:%d\n",str.ch->c,str.ch->num);
    }
    return 0;
}
