//#Dijkstra単源最短路径算法
//要求：有向带权图中指定顶点到途中其它顶点的最短路径，
//      图以领接矩阵表示，便于查找边的权值
//
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"adjacencymatrixgraph.h"
#include"commonhead.h"



int main(void)
{
    int i = 0;
    int n = 0;
    int minweight = MAXINT;
    int minindex = -1;
    int surindex = 0;   //源点在图中的序号
    char sur_ver;          //保存输入的源点
    AMGraph amg;
    _Bool *have = NULL;      //源点到这一点是否已确定最短路径，初始值为false
    int *coast = NULL;          //指定源点到某一点的路径值， 初始化时如果源点到该点没有
                                //路径初始为最大值
    int *path = NULL;         //如果该点到源点有路径，记录该点的直接前驱点，初始化时如
                              //果该点到源点有直接路径，初始化为源点，否则初始化为-1，
                              //运算过程这个值是可以改变的

    printf("\033[31m这里请选择有向带权图\033[0m\n");
    AMGraphInit(&amg);
    showmatrix(&amg);

    printf("请输入源点：\n");
    sur_ver = getchar();
    eatline();
    surindex = getindex(amg.vexs, sur_ver, amg.vexnum);

    if (!(have = (_Bool *)malloc(amg.vexnum * sizeof(_Bool))))
    {
        perror("have 空间分配失败");
        exit(EXIT_FAILURE);
    }
    memset(have,false,amg.vexnum);
    have[surindex] = true;

    if (!(coast = (int *)malloc(amg.vexnum * sizeof(int))))
    {
        perror("coast 空间分配失败");
        exit(EXIT_FAILURE);
    }

    if (!(path = (int *)malloc(amg.vexnum * sizeof(int))))
    {
        perror("path 空间分配失败");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < amg.vexnum; i++)
    {
        coast[i] = *(amg.arcs + (amg.vexnum * surindex) + i);
        if (coast[i] < MAXINT)
        {
            path[i] = surindex;
        }
        else
            path[i] = -1;
    }
    coast[surindex] = 0;
    path[surindex] = -1;

    printf("开始计算\n");
    for (i = 0; i < amg.vexnum; i++)
    {
        minweight = MAXINT;
        minindex = -1;
        for (n = 0; n < amg.vexnum; n++)
        {
            if (!have[n] && (minweight > coast[n]))
            {
                minweight = coast[n];
                minindex = n;
            }
        }

        //要防止minindex = -1 的情况
        if (minindex != -1)
        {
        have[minindex] = true;
        printf("当前最小边%4c   %4c\n",amg.vexs[path[minindex]],amg.vexs[minindex]);
        for (n = 0; n <amg.vexnum; n++)
        {
                //所有的一切都是为了这句
            if (!have[n] && ( coast[minindex] + *(amg.arcs + minindex *amg.vexnum + n)) < coast[n])
            {
               coast[n] = (coast[minindex] + *(amg.arcs + minindex *amg.vexnum + n));
                path[n] = minindex;
            }
        }
        }
    }

    //show
    for (i = 0; i < amg.vexnum; i++)
    {
        printf("%4d",(int)have[i]);
    }
    putchar('\n');
    for (i = 0; i < amg.vexnum; i++)
    {
        printf("%4d",coast[i]);
    }
    putchar('\n');
    for (i = 0; i < amg.vexnum; i++)
    {
        printf("%4d",path[i]);
    }
    putchar('\n');
    
    return 0;
}
