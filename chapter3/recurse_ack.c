#include<stdio.h>
#include<stdlib.h>

int ack(int m,int n);

int main(int argc, char *argv[])
{
    int a = 0;
    int b = 0;
    int test;
    
    if (argc == 3)
    {
        a = atoi(argv[1]);
        b = atoi(argv[2]);

        test = ack(a,b);
        printf("test is :%d\n",test);
    }
    else
        printf("请输入2个参数\n");

    return 0;
}



int ack(int m,int n)
{
    if (m == 0)
        return (n+1);
    else if (n == 0)
        return (ack(m-1, 1));
    else
        return (ack(m-1,ack(m,n-1)));
}
