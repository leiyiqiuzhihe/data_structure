#include<stdio.h>
#include<stdlib.h>


#ifndef ACK_STACK_H
#define ACK_STACK_H

typedef struct LAckNode{
        int m;
        int n;
        struct LAckNode *next;
}LAckNode, *LStack;

int init_link_stack(LStack *ack_stack)
{
     *ack_stack = NULL;

     return 1;
}

LAckNode *  create_ack_node(void)
{
    LAckNode * ret_val;

    if ((ret_val = (LAckNode *)malloc(sizeof(LAckNode))))
    {
        return ret_val;
    }
    else
    {
        printf("malloc fail!!!\n");
        exit(0);
    }
}

int push(LStack *ack_stack, LAckNode * acknode)
{
    acknode->next = *ack_stack;
    *ack_stack = acknode;

    return 1;
}

int pop(LStack *ack_stack)
{
    LStack temp;

    if (*ack_stack)
    {
        temp = *ack_stack;
        *ack_stack = (*ack_stack)->next;
        free(temp);

        return 1;
    }
    else
    {
        printf("empty stack, pop failed\n");
        return 0;
    }
}


#endif
