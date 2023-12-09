#include<stdio.h>
#include<stdlib.h>

int* calculate_C_K(int input[],int i);
int* encoding(int arr[],int i);

int main()
{
    int input[30]={0};
    int i=0;
    for(i=0; ;i++)
    {
        scanf("%d",&input[i]);
        char c;
        if(c=getchar()=='\n')
        {
            break;
        }
    }
    int s=0;
    scanf("%d",&s);
    i=i+1;
    int* code=calculate_C_K(input,i);
    i=i+2;
    int* output=encoding(code,i);
    int row=0;

    for(int r=0;r<(i+2)*6-1;r++)
    {
        printf("%d ",(output[r]+1)*s);
        row++;
        if(row==10)
        {
            printf("\n");
            row=0;
        }
    }
    return 0;
}
int* calculate_C_K(int input[],int i)
{

    int c=0,k=0;
    int r=1;
    for(int j=0;j<i;j++)
    {
        c=c+(input[i-1-j]*r);
        //printf("%d ",input[i-1-j]*r);
        r=r+1;
        if(r==11)
        {
            r=1;
        }
    }
    c=c%11;
    input[i]=c;
    r=1;
    i=i+1;
    for(int j=0;j<i;j++)
    {
        k=k+(input[i-1-j]*r);
        r=r+1;
        if(r==10)
        {
            r=1;
        }
    }
    k=k%11;
    input[i]=k;
    return input;
}


int* encoding(int arr[],int i)
{
    int start_end[5]={0,0,1,1,0};
    int table[11][5]={{0,0,0,0,1},
                      {1,0,0,0,1},
                      {0,1,0,0,1},
                      {1,1,0,0,0},
                      {0,0,1,0,1},
                      {1,0,1,0,0},
                      {0,1,1,0,0},
                      {0,0,0,1,1},
                      {1,0,0,1,0},
                      {1,0,0,0,0},
                      {0,0,1,0,0}};
    int x=(i+2)*6-1;
    int *size;
    size=(int*)malloc(x*sizeof(int));
    int index=0;
    for(int n=0;n<i+2;n++)
    {
        for(int j=0;j<5;j++)
        {
            //printf("%d %d\n",n,index);
            if(n==0||n==i+1)
            {
                size[index]=start_end[j];
            }
            else
            {
                //printf("%d %d %d %d\n",n-1,arr[n-1],j,table[arr[n-1]][j]);

               size[index]=table[arr[n-1]][j];
            }
            index=index+1;
        }
        if(n<i+1)
        {
            size[index]=0;
            index=index+1;
        }
    }
    return size;
}