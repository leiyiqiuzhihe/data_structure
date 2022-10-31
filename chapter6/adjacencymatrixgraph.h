#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"commonhead.h"

#ifndef ADJACENCYMATRIXGRAPH_H
#define ADJACENCYMATRIXGRAPH_H


#define MAXINT  255       //表示网的极大值  使用memset（）初始化矩阵时出错了
                          //memset的操作大小是byte  255是错的
                          //想了又想还是别用memset了

typedef int ArcType;        //假设边的权值类型为整型

typedef struct{
        char *vexs;         //顶点表 动态分配空间；
        ArcType *arcs;      //邻接矩阵， 动态分配空间
        int vexnum, arcnum;  //图的当前顶点数和边数
}AMGraph;


int getindex(char *ar,char ch,int n)
{
    int i = 0;
    int flag = 0;

    for (i = 0;i < n; i++)
    {
        if (ar[i] == ch)
        {
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        printf("%c 不在顶点表中\n",ch);
        return -1;
    }
    else
        return i;
}

void showmatrix(AMGraph *graph)
{
    int n = graph->vexnum;
    int i = 0;
    int j = 0;
    char *ar = graph->vexs;
    int *matrix = graph->arcs;

    printf("\t");
    for (i = 0; i < n; i++)
    {
        printf("%8c",ar[i]);
    }
    putchar('\n');

    for (i = 0;i < n; i++)
    {
        printf("%8c",ar[i]);
        for (j = 0; j < n; j++)
            printf("%8d",matrix[i*n+j]);
        putchar('\n');
    }
}



void AMGraphInit(AMGraph *graph)
{          //从输入获取图信息，要先取得顶点数，初始化矩阵后，获取边信息
           //提示有几条边
    int v1 = 0, v2 = 0;        //记录顶点编号
    int countedge = 0;
    int edgeweight = 0;
    int flag = -1;
    int maxedges = 0;
    int i = 0, j = 0;
    int vertexes = 0;
    char vertex1, vertex2;
    char ch;
    unsigned int matrixsize = 0;

    printf("\033[31m请按照提示的格式输入信息！！！！！\n\033[0m");
    do
    {
        printf("How many vertexes in your graph?\n");
        scanf("%d",&(graph->vexnum));
    } while (graph->vexnum <= 0);
    vertexes = graph->vexnum;

    matrixsize = graph->vexnum * graph->vexnum;
    
    //分配空间
    if (!(graph->arcs = (int *)malloc(matrixsize*sizeof(int))))
    {
        perror("分配空间失败\n");
        exit(EXIT_FAILURE);
    }

    if (!(graph->vexs = (char *)malloc(graph->vexnum*sizeof(char))))
    {
        perror("顶点表空间分配失败\n");
        exit(EXIT_FAILURE);
    }

checkflag:
    printf("你的图是一下那种类型的？\n");
    printf("0、无向无权图\n1.无向有权图\n2、有向无权图\n3、有向有权图\n");
    printf("请选择：");
    scanf("%d",&flag);
    printf("你的选择是%d\n",flag);
    while (getchar() != '\n')
        ;

    if (flag == 1 || flag ==3)
        //memset(graph->arcs, MAXINT,matrixsize*sizeof(int));
    {
        for (i = 0; i < vertexes; i++)
        {
             //*(graph->arcs + i) = MAXINT;  //初始化时有问题
            for (j = 0; j < vertexes; j++)
            {
                if (j != i)
                    graph->arcs[i * vertexes + j] = MAXINT;

                else
                    graph->arcs[i * vertexes + j] = 0;
                
            }
        }
    }
    else if(flag == 0 || flag == 2)
        memset(graph->arcs, 0,matrixsize*sizeof(int));
    else
    {
        printf("请在下面的选项中选择\n");
        goto checkflag;            //这里有goto
    }

    //从输入获取图的点，边信息
    if (0 == flag)      
    {
        maxedges = vertexes * (vertexes - 1) / 2;

        for (i = 0; i < vertexes; i++)
        {
             printf("请输入第%d个点：", i+1);
             ch = getchar();
             //printf("ch is %c\n",ch);
             //putchar('\n');
             graph->vexs[i] = ch;
             //putchar(graph->vexs[i]);
             //putchar('\n');
             while (getchar() != '\n')
                 ;
        }
        countedge = 0;
        printf("请输入第%d条边的信息：vertex1 vertex2\n",countedge+1);
        while ((vertex1 = getchar()) != '#' && countedge < maxedges)
        {
            //printf("请输入第%d条边的信息：vertex1 vertex2\n",countedge+1);
            scanf(" %c",&vertex2);
            while (getchar() != '\n')
                ;
            v1 = getindex(graph->vexs,vertex1,graph->vexnum);
            v2 = getindex(graph->vexs,vertex2,graph->vexnum);
            graph->arcs[v1 * vertexes + v2] = 1;
            graph->arcs[v2 * vertexes + v1] = 1;
            countedge++;
            printf("请输入第%d条边的信息：vertex1 vertex2\n",countedge+1);
        }
        printf("There are %d edges in this graph.\n",countedge);
    }

    else if (1 == flag)   //无向有权图
    {
        maxedges = vertexes * (vertexes - 1) / 2;

        for (i = 0; i < vertexes; i++)
        {
             printf("请输入第%d点：", i+1);
             graph->vexs[i] = getchar();
             while (getchar() != '\n')
                 ;
        }
        countedge = 0;
        printf("请输入第%d条边的信息：vertex1 vertex2 edgeweight\n",countedge+1);
        while ((vertex1 = getchar()) != '#' && countedge < maxedges)
        {
            //printf("请输入第%d条边的信息：vertex1 vertex2\n",countedge+1);
            scanf(" %c %d",&vertex2,&edgeweight);
            while (getchar() != '\n')
                ;
            v1 = getindex(graph->vexs,vertex1,graph->vexnum);
            v2 = getindex(graph->vexs,vertex2,graph->vexnum);
            if (graph->arcs[v1 * vertexes + v2] ==  255 && graph->arcs[v2 * vertexes + v1] == -1)
            {
                graph->arcs[v1 * vertexes + v2] = edgeweight;
                graph->arcs[v2 * vertexes + v1] = edgeweight;
                countedge++;
                printf("请输入第%d条边的信息：vertex1 vertex2 edgeweight\n",countedge+1);
            }
            else
            {
                printf("这条边已经有了，请从新输入\n\n");
                printf("请输入第%d条边的信息：vertex1 vertex2 edgeweight\n",countedge+1);
            }
        }
        printf("There are %d edges in this graph.\n",countedge);
    }

    else if (2 == flag)       //有向无权图 只有边的数量与无向无权图不一样
    {
        maxedges = vertexes * (vertexes - 1);

        for (i = 0; i < vertexes; i++)
        {
             printf("请输入第%d点：", i+1);
             graph->vexs[i] = getchar();
             while (getchar() != '\n')
                 ;
        }
        countedge = 0;
        printf("请输入第%d条边的信息：vertex1 vertex2\n",countedge+1);
        while ((vertex1 = getchar()) != '#' && countedge < maxedges)
        {
            //printf("请输入第%d条边的信息：vertex1 vertex2\n",countedge+1);
            scanf(" %c",&vertex2);
            while (getchar() != '\n')
                ;
            v1 = getindex(graph->vexs,vertex1,graph->vexnum);
            v2 = getindex(graph->vexs,vertex2,graph->vexnum);
            graph->arcs[v1 * vertexes + v2] = 1;
            countedge++;
            printf("请输入第%d条边的信息：vertex1 vertex2\n",countedge+1);
        }
        printf("There are %d edges in this graph.\n",countedge);
    }
    
    else          //有向有权图，只有边的数量与无向有权图不一样
    {
        maxedges = vertexes * (vertexes - 1);

        for (i = 0; i < vertexes; i++)
        {
             printf("请输入第%d点：", i+1);
             graph->vexs[i] = getchar();
             while (getchar() != '\n')
                 ;
        }
        countedge = 0;
        printf("请输入第%d条边的信息：vertex1 vertex2 edgeweight\n",countedge+1);
        while ((vertex1 = getchar()) != '#' && countedge < maxedges)
        {
            //printf("请输入第%d条边的信息：vertex1 vertex2\n",countedge+1);
            scanf(" %c %d",&vertex2,&edgeweight);
            while (getchar() != '\n')
                ;
            v1 = getindex(graph->vexs,vertex1,graph->vexnum);
            v2 = getindex(graph->vexs,vertex2,graph->vexnum);
            if (graph->arcs[v1 * vertexes + v2] == 255)
            {
                graph->arcs[v1 * vertexes + v2] = edgeweight;
                countedge++;
                printf("请输入第%d条边的信息：vertex1 vertex2 edgeweight\n",countedge+1);
            }
            else
            {
                printf("这条边已经有了，请从新输入\n\n");
                printf("请输入第%d条边的信息：vertex1 vertex2 edgeweight\n",countedge+1);
            }
        }
        eatline();
        printf("There are %d edges in this graph.\n",countedge);
    }
    graph->arcnum = countedge;
}


#endif
