#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
#include"evaluate_expression.h"


int main(void)
{
    LStack oprd_stack = NULL, oprt_stack = NULL;
    int oprt_head;
    //int oprd_head;
    int a = 0, b = 0;
    int temp = 0, total = 0;
    int prece = 0;
    int inp_oprt;      //读取的运算符
    int inp_oprd;      //读取的数字

    create_init_stack(&oprt_stack);
    create_init_stack(&oprd_stack);

    printf("请输入要计算的表达式，（表达式以#开始，以#结束）\n");
    if ((inp_oprt = getchar()) == '#')
    {
        push(&oprt_stack,inp_oprt);
        scanf("%d",&inp_oprd);
        push(&oprd_stack,inp_oprd);
        inp_oprt = getchar();
        push(&oprt_stack,inp_oprt);
        scanf("%d",&inp_oprd);
        push(&oprd_stack,inp_oprd);
        printf("%c\n", oprt_stack->element);
        printf("%d %d\n",oprd_stack->element,oprd_stack->next->element);

        while ((inp_oprt = getchar()) != '#')
        {
            get_head(&oprt_stack, &oprt_head);
            printf("%c %c\n", oprt_head, inp_oprt);
            prece = precede(oprt_head,inp_oprt);
            if (prece < 0)
            {
                pop(&oprt_stack);
                get_head(&oprd_stack, &a);
                pop(&oprd_stack);
                get_head(&oprd_stack, &b);
                pop(&oprd_stack);
                temp = evaluate(a, oprt_head,b);
                push(&oprd_stack,temp);
                printf("1a\n");
                //sleep(10);
            }
            push(&oprt_stack, inp_oprt);

            //scanf("%d", &inp_oprd);

            if ((inp_oprt = getchar()) == '(')
            {
                push(&oprt_stack,inp_oprt);
                scanf("%d",&inp_oprd);
                push(&oprd_stack,inp_oprd);
                inp_oprt = getchar();
                push(&oprt_stack,inp_oprt);
                scanf("%d",&inp_oprd);
                push(&oprd_stack,inp_oprd);

                while ((inp_oprt = getchar()) != ')')           //读到圆括号时
                {
                    get_head(&oprt_stack, &oprt_head);
                    prece = precede(oprt_head,inp_oprt);
                    if (prece < 0)
                    {
                        get_head(&oprt_stack, &oprt_head);
                        pop(&oprt_stack);
                        get_head(&oprd_stack, &a);
                        pop(&oprd_stack);
                        get_head(&oprd_stack, &b);
                        pop(&oprd_stack);
                        temp = evaluate(a, oprt_head,b);
                        push(&oprd_stack,temp);
                        printf("2a\n");
                        //sleep(10);
                    }
                    push(&oprt_stack, inp_oprt);
                    scanf("%d", &inp_oprd);
                }
                
                get_head(&oprt_stack,&oprt_head);
                while (oprt_head != '(')
                {
                        pop(&oprt_stack);
                        get_head(&oprd_stack, &a);
                        pop(&oprd_stack);
                        get_head(&oprd_stack, &b);
                        pop(&oprd_stack);
                        temp = evaluate(a, oprt_head,b);
                        push(&oprd_stack,temp);

                        get_head(&oprt_stack,&oprt_head);
                        printf("3a\n");
                        //sleep(10);
                }
                pop(&oprt_stack);
            }
            else
            {
                ungetc(inp_oprt,stdin);
            }
            scanf("%d", &inp_oprd);
            push(&oprd_stack,inp_oprd);
        }

        get_head(&oprt_stack,&oprt_head);      //读到结尾的#时
        while (oprt_head != '#')
        {
            pop(&oprt_stack);
            get_head(&oprd_stack, &a);
            pop(&oprd_stack);
            get_head(&oprd_stack, &b);
            pop(&oprd_stack);
            temp = evaluate(a, oprt_head,b);
            push(&oprd_stack,temp);

            get_head(&oprt_stack,&oprt_head);
            printf("4a\n");
            //sleep(10);
        }
        pop(&oprt_stack);
        
        get_head(&oprd_stack, &total);
        printf("表达式的值是：%d\n",total);
    }
    else
    {
        printf("输入的表达式格式不对\n");
    }

    return 0;
}
