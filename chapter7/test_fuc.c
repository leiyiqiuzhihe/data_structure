#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"commonhead.h"

#define SIZE 80
int main(void)
{
    //char *temp = "hell";
    //char *temp = NULL;
    char temp[SIZE];              //这样不会出错

    printf("请输入一句话:\n");
    s_gets(temp,SIZE);             //fgets改变的是指针指向的内存上的数据，不会改变指针
    printf("%s\n",temp);

    return 0;
}
