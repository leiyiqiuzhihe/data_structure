//breadth first search     广度优先搜索算法
//先定义一个队列 先进先出
//BFS是在WFS一个星期后写的，对orthogonallistgraph的定义记不清了，
//自己写的都这样，何况维护别人的代码
//应该可以优化
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"orthogonallistgraph.h"

#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

typedef struct{
    char *ar;
    int head;
    int tail;
    int size;
}SQList;

void InitSQList(SQList *sq, int n)
{
    if (!(sq->ar = (char *)malloc(n*sizeof(char))))
    {
        perror("队空间分配失败");
        exit(EXIT_FAILURE);
    }
    sq->head = sq->tail = 0;
    sq->size = n;
}

void popSQL(SQList *sq)
{
    if (sq->head == sq->tail)
    {
        printf("Pop 错误，队列是空的\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        sq->head += 1;        
    }
}

void pushSQL(SQList *sq, char e)
{
    if (sq->tail < sq->size)
    {
        sq->ar[sq->tail++] = e;
    }
    else
    {
        printf("队列已满\n");
        exit(EXIT_FAILURE);
    }
}

char getSQLhead(SQList *sq)
{
    if (sq->head != sq->tail)
        return (sq->ar[sq->head]);
    else
    {
        printf("队列是空的gethead failed\n");
        exit(EXIT_FAILURE);
    }

}

void FreeSQL(SQList *sq)
{
    free(sq->ar);
}

void BFS(OLGraph *olg, SQList *sq, _Bool *visited,char ver)   //从给定顶点开始BFS
{
    ArcBox *temp = NULL;
    int v = GetIndex(olg,ver);
    char  head;

    if (!visited[v])
    {
        visited[v] = true;
        printf("%4c",ver);
        pushSQL(sq,ver);
        temp = olg->vexlist[v].firstout;
        while (temp)
        {
            pushSQL(sq,olg->vexlist[temp->headvex].vertex);
            temp = temp->tlink;
        }
    }
    while (sq->head != sq->tail)       //队列非空
    {

        head = getSQLhead(sq);
        //printf("%c \n",head);
        v = GetIndex(olg,head);
        //printf("%d %c \n", v,head);
        if (!visited[v])
        {
            visited[v] = true;
            printf("%4c",olg->vexlist[v].vertex);
            temp = olg->vexlist[v].firstout;
            while (temp)
            {
                //pushSQL(sq,temp->headvex);
                pushSQL(sq,olg->vexlist[temp->headvex].vertex);
                temp = temp->tlink;
            }
        }
        popSQL(sq);
    }
}

void BFSTraverse(OLGraph *olg)
{
    SQList sq;
    _Bool *visited = (_Bool *)malloc(olg->vexnum * sizeof(_Bool));
    int i = 0;
    int n = olg->vexnum;

    printf("初始化队列\n");
    InitSQList(&sq,olg->vexnum);
    for (i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    printf("\nBreadth first search\n");
    for (i = 0; i < n; i++)        //如果是 非连通图
    {
        if (!visited[i])
        {
            BFS(olg,&sq,visited,olg->vexlist[i].vertex);
        }
    }
    
    FreeSQL(&sq);
}



#endif
