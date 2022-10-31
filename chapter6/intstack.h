#include<stdio.h>
#include<stdlib.h>

#ifndef INTSTACK_H
#define INTSTACK_H


typedef struct IntLinkNode{
        int operand;
        struct IntLinkNode *next;
}IntLinkNode, *IntLinkStack;

void int_push(IntLinkStack *ilstack, int ch)
{
    IntLinkNode *newnode;

    if ((newnode = (IntLinkNode *)malloc(sizeof(IntLinkNode))))
    {
        newnode->operand = ch;
        newnode->next = (*ilstack);
        *ilstack = newnode;
    }
    else
        perror("IntLinkStack malloc failed");
}


void int_pop(IntLinkStack *ilstack)      //栈顶出栈，要释放空间
{
    IntLinkNode *temp;

    if (*ilstack)
    {
        temp = *ilstack;
        *ilstack = (*ilstack)->next;
        free(temp);
    }
    else
        printf("Stack is empty, pop faided\n");
}

void intgethead(IntLinkStack *ilstack, int *ch)     //栈顶元素赋给ch
{
    if (*ilstack)
        *ch = (*ilstack)->operand;
    else
        printf("empty stack, intgethead failed\n");
}



#endif
