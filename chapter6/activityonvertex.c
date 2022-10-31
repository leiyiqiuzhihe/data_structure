//拓扑排序 用十字链表计算入度（indegree[head]++）
#include<stdio.h>
#include<stdlib.h>
#include"orthogonallistgraph.h"
#include"intstack.h"

void CountIndegree(OLGraph *olg, int *indegree);    //统计各顶点的入度
void ShowIndegree(int *indegree, int n);
void EvalueTopo(OLGraph *olg, int *indegree, int *top); //栈在函数内创建

int main(void)
{
    OLGraph olg;
   // IntLinkStack zero_degree_stack = NULL;
    int *indegree = NULL;
    int *topo = NULL;
    int vexnum = 0;
    int i = 0;

    OLGraphInit(&olg);
    InsertEdges(&olg);
    vexnum = olg.vexnum;
    if (!(indegree = (int *)malloc(vexnum * sizeof(int))))
    {
        perror("indegree 空间分配失败");
        exit(EXIT_FAILURE);
    }
    if (!(topo = (int *)malloc(vexnum * sizeof(int))))
    {
        perror("topo 空间分配失败");
        exit(EXIT_FAILURE);
    }

    for (i = 0;i < vexnum; i++)
    {
        indegree[i] = 0;
        topo[i] = 0;
    }

    CountIndegree(&olg,indegree);
    ShowIndegree(indegree,vexnum);
    putchar('\n');

    EvalueTopo(&olg, indegree, topo);
    printf("topo序列如下\n");
    ShowIndegree(topo,vexnum);            //显示topo数组内容

    return 0;
}



void CountIndegree(OLGraph *olg, int *indegree)
{
    int vexnum = olg->vexnum;
    int i = 0;
    ArcBox * temp = NULL;

    for (i = 0; i < vexnum; i++)
    {
        temp = olg->vexlist[i].firstout;
        while (temp)
        {
            indegree[temp->headvex]++;
            temp = temp->tlink;
        }
    }
    printf("indegree统计完成\n");
}


void ShowIndegree(int *indegree, int n)
{
    int i = 0;

    for (i = 0; i < n; i++)
    {
        printf("%8d",i);
    }
    putchar('\n');
    for (i = 0; i < n; i++)
    {
        printf("%8d",indegree[i]);
    }
    putchar('\n');
}




void EvalueTopo(OLGraph *olg, int *indegree, int *topo)
{
    IntLinkStack zero_degree_stack = NULL;
    ArcBox *temp = NULL;
    int i = 0;
    int vexnum = olg->vexnum;
    int head = 0;
    int topo_index = 0;

    for (i = 0; i < vexnum; i++)
    {
        if (indegree[i] == 0)
            int_push(&zero_degree_stack, i);
    }
    
    topo_index = 0;
    while (zero_degree_stack)
    {
        intgethead(&zero_degree_stack, &head);
        int_pop(&zero_degree_stack);
        topo[topo_index++] = head;

        temp = olg->vexlist[head].firstout;
        while (temp)
        {
            indegree[temp->headvex]--;
            if (indegree[temp->headvex] == 0)
            {
                int_push(&zero_degree_stack,temp->headvex);
            }
            temp = temp->tlink;
        }
    }

}
