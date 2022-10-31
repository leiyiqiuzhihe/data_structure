//测试头文件是否正确
#include<stdio.h>
#include<stdlib.h>
#include"adjacencymatrixgraph.h"

int main(void)
{
    AMGraph  graph;


    AMGraphInit(&graph);
    showmatrix(&graph);

    return 0;
}
