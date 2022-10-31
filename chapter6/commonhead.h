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


#endif
