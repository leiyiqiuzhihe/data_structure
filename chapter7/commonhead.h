//一些简单常用的自定义函数


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#ifndef  COMMONHEAD_H
#define  COMMONHEAD_H

void eatline()
{
    while (getchar() != '\n')
            ;
}

char * s_gets(char *str,int n)      //str最好是数组名，fgets不会改变指针指向，
{
     char *ret_val = NULL;
     char *find = NULL;

     if ((ret_val = fgets(str,n,stdin)))
     {
         if ((find = strchr(str,'\n')))
             *find = '\0';
         else
            eatline();
     }

     return ret_val;
}
#endif
