#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#ifndef EVALUATE_EXPRESSION
#define EVALUATE_EXPRESSION

typedef struct LNode{
        int element;
        struct LNode *next;
}LNode, *LStack;


/*
int get_input_oprd(void)        //读取数字项
{
    int ret_val;
    int ch;

    ret_val = 0;
    while (isdigit(ch = getchar()))
    {
        ret_val = ret_val * 10 + ch;
    }

    return ret_val;
}
*/

int precede(int stack_top, int ch_oprt)
{                                //栈顶优先级底，返回正数，ch_oprt入栈
                                 //栈顶优先级高，返回负数，栈顶出栈
                                 //圆括号，井号要考虑 
    if (stack_top == '#')
    {
            return 1;
    }
    if (stack_top == '(')
    {
            return 1;
    }
    if (stack_top == '+' || stack_top == '-')
    {
        if (ch_oprt == '(')
            return 1;
        else if (ch_oprt == '*' || ch_oprt == '/')
            return 1;
        else
            return -1;
    }
    if (stack_top == '*' || stack_top == '/')
    {
        if (ch_oprt == '(')
            return 1;
        else
            return -1;
    }
}

int  create_init_stack(LStack *lstack)        //创建并初始化一个栈，成功返回指向它的指针
{
    *lstack = NULL;
    
    return 1;    
}

int push(LStack *lstack, int e)      //把e的值入栈 ，成功返回1，失败返回0
{
    LNode * temp;

    if ((temp = (LNode *)malloc(sizeof(LNode))))
    {
        temp->element = e;
        temp->next = *lstack;
        *lstack = temp;

        return 1;
    }
    else
        return 0;
}


int pop(LStack *lstack)           //弹出栈顶元素 释放空间
{
    LNode * temp;

    if (lstack)
    {
        temp = *lstack;
        *lstack = (*lstack)->next;
        free(temp);

        return 1;
    }
    else
    {
        printf("栈已空\n");
        return 0;
    }
}


int get_head(LStack *lstack,int *pi)     //取栈顶元素的值，注意第二个参数
{
    if (*lstack)
    {
        *pi = (*lstack)->element;

        return 1;
    }
    else
    {
        printf("empty stack\n");
        return 0;
    }
}

int evaluate(int a, char operater, int b)
{
     if (operater == '+')
         return (a+b);
     else if (operater == '-')
         return (a-b);
     else if (operater == '*')
         return (a*b);
     else if (operater == '/')
         return (a/b);
}
#endif
