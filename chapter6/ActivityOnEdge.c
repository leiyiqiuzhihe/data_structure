#include<stdio.h>
#include<stdlib.h>
#include"orthogonallistgraph.h"
#include"ActivityOnEdge.h"

int main(void)
{
    OLGraph olg;
    
    OLGraphInit(&olg);
    InsertEdges(&olg);

    CriticalPath(&olg);

    return 0;
}
