//Floyd 算法有向网中任意两点间的最短路径，图用邻接矩阵表示
//      理解dijkstra算法有助于理解这个算法，我的理解是：试 试的同时更新
//      试：对任意两个顶点（vi，vj）加入一个顶点（vn），看看经过这个点是否会让这两个顶点之间的路
//      经更短   对任意顶点对，试完一个顶点，再试另一个
//      更新： 在试的过程中，如果经过被测试的顶点有更短的路径，就更新当前顶点对
//      的权重，同时更新头节点的前驱节点为Path[n][j]的值
//      
//      如果两个顶点之间有多个最短路径，这里只能算出1条


#include<stdio.h>
#include<stdlib.h>
#include"adjacencymatrixgraph.h"
#include"commonhead.h"

void showresult(AMGraph *amg, int *ar);  //显示运算结果，数组大小用amg中的订单数
                                         //运算得出

int main(void)
{
    AMGraph amg;
    int *path = NULL, *weight = NULL;
    int n = 0;
    int i = 0, j = 0;
    int vexnum = 0;
    char input_v1, input_v2;
    int  v1_index, v2_index;
    int tail_index, head_index;       //用于显示路径时的下标

    printf("\033[31m请输选择3，有向网\n\033[0m");
    AMGraphInit(&amg);
    showmatrix(&amg);

    vexnum = amg.vexnum;
    if (!(path = (int *)malloc(vexnum * vexnum  *sizeof(int))))
    {
        perror("path 分配空间失败");
        exit(EXIT_FAILURE);
    }
    if (!(weight = (int *)malloc(vexnum * vexnum * sizeof(int))))
    {
        perror("weight 分配空间失败");
        exit(EXIT_FAILURE);
    }

    puts("初始化辅助空间\n");
    for (i = 0; i < vexnum; i++)
        for (j = 0; j < vexnum; j++)
        {
            weight[i * vexnum +j] = amg.arcs[i * vexnum + j];
            if (amg.arcs[i * vexnum + j] < MAXINT && amg.arcs[i * vexnum + j] > 0)
                path[i * vexnum + j] = i;
            else
                path[i * vexnum + j] = -1;
        }
    printf("开始Floyd算法\n");
    for (n = 0; n < vexnum; n++)
        for (i = 0; i < vexnum; i++)
            for (j = 0; j < vexnum; j++)
                if ((weight[i*vexnum + n] + weight[n * vexnum + j] < weight[i * vexnum + j]))
                    {
                        weight[i * vexnum + j] = weight[i*vexnum + n] + weight[n * vexnum + j];
                        path[i * vexnum + j] =  path[n * vexnum + j];

                    }
    printf("显示路径结果\n");
    showresult(&amg,path);
    printf("显示最短路径结果\n");
    showresult(&amg,weight);

    //算法是书上的，想办法显示路径，给任意两个点显示它们之间的路径
    printf("请输入两个顶点，我们会显示它们之间的最短路径(v1 v2)\n");
    scanf("%c %c", &input_v1, &input_v2);
    eatline();
    v1_index = getindex(amg.vexs, input_v1, vexnum);
    v2_index = getindex(amg.vexs, input_v2, vexnum);
    if (v1_index != -1 && v2_index != -1)
    {
        tail_index = path[v1_index * vexnum + v2_index];
        head_index = v2_index;
        while (tail_index != v1_index)
        {
            printf("%c ----> %c   weight:%d\n",amg.vexs[tail_index],
                   amg.vexs[head_index], weight[tail_index * vexnum + head_index]);
            head_index = tail_index;
            tail_index = path[v1_index * vexnum + head_index];
        }
        printf("%c ----> %c   weight:%d\n",amg.vexs[v1_index],
                   amg.vexs[head_index], weight[v1_index * vexnum + head_index]);
    }
    
    printf("Done!!!!\n");
    return 0;
}



void showresult(AMGraph *amg, int *ar)
{
    int n = amg->vexnum;
    int i = 0, j = 0;
    char *vertex_list = amg->vexs;
    //int matrix_size = n * n;

    printf("\t");
    for (i = 0; i < n; i++)
    {
        printf("%8c", vertex_list[i]);
    }
    putchar('\n');

    for (i = 0; i < n; i++)
    {
        printf("%8c", vertex_list[i]);
        for (j = 0; j < n; j++)
            printf("%8d",ar[i*n+j]);
        putchar('\n');
    }
}
