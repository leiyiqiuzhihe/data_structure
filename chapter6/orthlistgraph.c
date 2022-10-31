//测试十字链表
#include<stdio.h>
#include<stdlib.h>
#include"orthogonallistgraph.h"
#include"breadthfirstsearch.h"

int main(void)
{
    OLGraph olg;


    OLGraphInit(&olg);
    InsertEdges(&olg);
    ShowOlg(&olg);
    DFSTraverse(&olg);
    BFSTraverse(&olg);

    FreeGraph(&olg);

    return 0;
}
