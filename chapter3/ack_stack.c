#include<stdio.h>
#include<stdlib.h>
#include"ack_stack.h"


int main(int argc, char *argv[])
{
    LStack ack_stack;
    LAckNode * newnode, *current;
    int result = 0;

    if (argc != 3)
    {
        printf("usage:name int int\n");
        exit(0);
    }
    
    init_link_stack(&ack_stack);
    newnode = create_ack_node();
    newnode->m = atoi(argv[1]);
    newnode->n = atoi(argv[2]);

    push(&ack_stack, newnode);

    while (ack_stack)
    {
            current = ack_stack;

            if (current->m == 0)
            {
                if (current->next == NULL)
                {
                    result = current->n+1;
                    break;
                }
                else
                {
                     current->next->n = current->n + 1;
                     pop(&ack_stack);
                }
            }
            else if (current->n == 0)
            {
                current->m = current->m - 1;
                current->n = 1;
            }
            else
            {
                newnode = create_ack_node();
                newnode->m = current->m;
                newnode->n = current->n - 1;
                current->m = current->m - 1;      //新节点入栈时，current->m 要变小
                push(&ack_stack,newnode);
            }
    }
    printf("结果是：%d\n",result);

    free(ack_stack);
    return 0;
}
