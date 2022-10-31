#include<stdio.h>
#include<stdlib.h>

#define  BUFSIZE   50



//int RecursionBinSearch


int main(void)
{
    int buf[BUFSIZE] = {0};
    int count = 0;
    int i = 0;
    int ret_val = 0;

    while ((ret_val = scanf("%d",&buf[count])) != EOF && ret_val != 0)
        count++;

    for (i = 0; i < count; i++)
    {
        printf("%4d",buf[i]);
    }

    return 0;
}
