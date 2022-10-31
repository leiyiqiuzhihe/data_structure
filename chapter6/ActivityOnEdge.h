//想要做的事，最好用函数实现，方便复用
#include<stdio.h>
#include<stdlib.h>
#include"orthogonallistgraph.h"       //十字链表表示图
#include"intstack.h"                  //一个简单的栈
#include"activityonvertex.h"           //拓扑排序，并验证图是否是无环图


#ifndef ACTIVITYONEDGE_H
#define ACTIVITYONEDGE_H



void ShowArray(int *ar, int n)
{
    int i = 0;

    for (i = 0; i < n; i++)
        printf("%4d",i);
    printf("\n");
    
    for (i = 0; i < n; i++)
        printf("%4d",ar[i]);
    printf("\n");
}


void CriticalPath(OLGraph *olg)
{
    int vexnum = olg->vexnum;
    int *toposq = NULL;
    int *ve = NULL;      //事件的最早发送时间
    int *vl = NULL;      //事件的最迟发生时间
    int i = 0;
    int current_vertex = 0;
    ArcBox *temp = NULL;

    if (!(toposq = (int *)malloc(vexnum * sizeof(int))) ||
                    !(ve = (int *)malloc(vexnum * sizeof(int))) ||
                    !(vl = (int *)malloc(vexnum * sizeof(int))))
    {
         perror("辅助空间分配失败");
         exit(EXIT_FAILURE);
    }                          //是否会有内存泄漏的问题？？？？
    memset(ve,0,vexnum * sizeof(int));
    //memset(vl,0,vexnum * sizeof(int));  在下面初始化

    TopoSeq(olg,toposq);
    
    for (i = 1; i < vexnum; i++)      //计算ve要依topo序，怎么才是依拓扑序？？？？
    {
        current_vertex = toposq[i];
        temp = olg->vexlist[current_vertex].firstin;
        while (temp)
        {
            if (temp->weight + ve[temp->tailvex] > ve[current_vertex])
            {
                ve[current_vertex] = temp->weight + ve[temp->tailvex];
            }
            temp = temp->hlink;
        }
    }

    printf("ve的结果\n");
    ShowArray(ve,vexnum);

    //初始化vl
    for (i = 1; i < vexnum; i++)
        vl[i] = ve[vexnum-1];
    vl[0] = 0;


    for (i = vexnum - 2; i > 0; i--)     //vl的定义，min{vl[headvex] - <tail,head>}
    {
        current_vertex = toposq[i];              //i
        temp = olg->vexlist[current_vertex].firstout;
        while (temp)
        {
            if (vl[temp->headvex] - temp->weight < vl[current_vertex])
                vl[current_vertex] = vl[temp->headvex] - temp->weight;
            temp = temp->tlink;
        }
    }

    printf("vl的结果\n");
    ShowArray(vl,vexnum);

    //从源点开始，不用到汇点
    printf("Edges on Critical Path:\n");
    for (i = 0; i < vexnum -1; i++)
    {
        //if (ve[i] == vl[i])
            temp = olg->vexlist[i].firstout;
            while (temp)
            {
                if (ve[i] == vl[temp->headvex] - temp->weight)
                {
                    printf("%c ---> %c\n", olg->vexlist[i].vertex,
                                    olg->vexlist[temp->headvex].vertex);
                }
                temp = temp->tlink;
            }
    }


    free(toposq);
    free(ve);
    free(vl);
}





#endif
