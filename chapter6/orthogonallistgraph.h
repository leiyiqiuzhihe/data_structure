//orthogonalistgraph 十字链表的头文件

#include<stdio.h>
#include<stdlib.h>
#include"commonhead.h"
#include<stdbool.h>


#ifndef  ORTHOGONALLISTGRAPH_H
#define  ORTHOGONALLISTGRAPH_H

typedef struct ArcBox
{
    int tailvex, headvex;
    struct ArcBox *hlink, *tlink;
    int weight;
}ArcBox;            //这是有向带权图

typedef struct VexNode
{
    char vertex;
    ArcBox *firstin, *firstout;
}VexNode;

typedef struct
{
    VexNode *vexlist;    //用动态分配空间
    int vexnum, arcnum;
}OLGraph;

void OLGraphInit(OLGraph *olg)
{
    int vertexes = 0;
    char vert;
    int i =  0;

    printf("How many vertexes in your graph?\n");
    scanf("%d",&vertexes);
    eatline();
    olg->vexnum = vertexes;
    olg->arcnum = 0;
    olg->vexlist = (VexNode *)malloc(sizeof(VexNode) * vertexes);
    if (olg->vexlist)
    {
        printf("顶点表分配成功。\n");
    }
    else
    {
        perror("顶点表空间分配失败\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < vertexes; i++)
    {
        printf("请输入第%d 个顶点：\n",i+1);
        vert = getchar();
        eatline();
        olg->vexlist[i].vertex = vert;
        olg->vexlist[i].firstin = NULL;
        olg->vexlist[i].firstout = NULL;
    }
    printf("OLGraph inited.\n");
}

int GetIndex(OLGraph *olg, char vert)
{
    int i = 0;
    int n = olg->vexnum;
    int flag = 0;

    for (i = 0; i < n; i++)
    {
        if (olg->vexlist[i].vertex == vert)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        return i;
    }
    else
    {
        printf("%c 不是这个图的顶点\n",vert);
        return -1;
    }
}


int CheckEdge(OLGraph *olg, int tail, int head)
{
    ArcBox *p = NULL;

    p = olg->vexlist[tail].firstout;
    while (p)
    {
        if (head == p->headvex)
            return 0;
        p = p->tlink;
    }
    if (!p)           //如果这里p仍为NULL 这个边肯定不存在
        return 1;
}

void InsertEdges(OLGraph *olg)
{
    int tail = 0, head = 0;
    char tailver, headver;    //暂存弧尾，弧头
    int weight = 0;
    //int i = 0;
    int n = olg->vexnum;
    int maxedges = n*(n -1);       //这个图最多有多少边
    int countedge = olg->arcnum;
    ArcBox *p = NULL;

    printf("请输入你要插入的边：tail head weight (or '#' to quit)\n");
    while ((tailver = getchar()) != '#' && countedge < maxedges)
    {
        scanf(" %c %d",&headver, &weight);
        eatline();
        if (!(p = (ArcBox *)malloc(sizeof(ArcBox))))
        {
            perror("边节点分配失败");
            exit(EXIT_FAILURE);
        }
        tail = GetIndex(olg, tailver);
        head = GetIndex(olg, headver);
        if (!CheckEdge(olg, tail,head))   //要先检查这个边原来有没有，已经有返回0
        {
            printf("这条边已经存在了，请重新输入\n");
            printf("请输入你要插入的边：tail head weight (or '#' to quit)\n");
            continue;
        }
        p->tailvex = tail;
        p->headvex = head;
        p->weight = weight;
        p->tlink = olg->vexlist[tail].firstout; //这里的插入顺序会影响遍历顺序
        olg->vexlist[tail].firstout = p;

        p->hlink = olg->vexlist[head].firstin;
        olg->vexlist[head].firstin = p;
        countedge++;
        printf("%c -> %c加入成功，请输入下一条\n",tailver,headver);
        printf("请输入你要插入的边：tail head weight (or '#' to quit)\n");
    }
    if (countedge == maxedges)
    {
        printf("这是一个有向完全图\n");
    }

   olg->arcnum = countedge;
}

//这个应该叫FreeArcBox，在十字链表中要删除一条边，如果这条边是存在的，要把它的
//两个前驱节点找到才行
void DelEdge(OLGraph *olg, ArcBox *arc)
{
    olg->vexlist[arc->tailvex].firstout = arc->tlink;
    olg->vexlist[arc->headvex].firstin = arc->hlink;
    free(arc);
}


void ShowOlg(OLGraph *olg)
{
    int i = 0;
    ArcBox *pout = NULL;

    for (i = 0; i < olg->vexnum; i++)
    {
        pout = olg->vexlist[i].firstout;
        printf("%d\t%c\t%p\t%p\n",i, olg->vexlist[i].vertex,
                        olg->vexlist[i].firstin,olg->vexlist[i].firstout);
        while (pout)
        {
            printf("\t\t%p\t%d\t%d\t%p\t%p\t%d\n",pout,pout->tailvex,pout->headvex,
                            pout->hlink,pout->tlink,pout->weight);
            pout = pout->tlink;
        }
    }
}

void DFS(OLGraph *olg, _Bool *visited, int v)
{
    ArcBox *temp = NULL;


    if (!visited[v])
    {
        printf("%4c",olg->vexlist[v].vertex);
        visited[v] = true;
        temp = olg->vexlist[v].firstout;
        while (temp)
        {
            DFS(olg,visited,temp->headvex);
            temp = temp->tlink;
        }
        printf("\n");
    }
}


void DFSTraverse(OLGraph *olg)
{
    int i = 0;
    int n = olg->vexnum;
    _Bool *visited = (_Bool *)malloc(olg->vexnum * sizeof(_Bool));

    for (i = 0; i < n; i++)
    {
        visited[i] = false;
    }
    
    printf("深度优先遍历：\n");
    for (i = 0; i < n; i++)
    {
        DFS(olg,visited, i);
    }
    printf("\n");
}


void FreeGraph(OLGraph *olg)      //这里假设图在main中声明
{
    int i = 0;
    ArcBox  *pout = NULL;

    for (i = 0;i < olg->vexnum; i++)
    {
        pout = olg->vexlist[i].firstout;
        while (pout)
        {
            DelEdge(olg, pout);
            pout = olg->vexlist[i].firstout;
        }
    }
    free(olg->vexlist);
}


#endif

