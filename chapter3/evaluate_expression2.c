/*遇到的问题，读取数字时忘了ASCii与实际的数字不一样，操作栈函数，要传入栈*/
/*指针的地址，而不是传入栈指针，比如pop是会修改栈指针；运算的顺序，怎样知道程序运行时发生了什么以便于调试;  没有前面失败的总结，不会有这个结果；想法的漏洞不可避免*/

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
    int input = 0;      //读取的运算符

    create_init_stack(&oprt_stack);
    create_init_stack(&oprd_stack);

    printf("请输入要计算的表达式，（表达式以#开始，以#结束）\n");
    if ((input = getchar()) == '#')
    {
        push(&oprt_stack,input);
        
        while ((input = getchar()) != '#')
        {
            if (isdigit(input))
            {
                temp = input - '0';
                while (isdigit(input = getchar()))
                {
                    temp = temp * 10 + input - '0';
                }
                ungetc((char)input, stdin);
                push(&oprd_stack, temp);
                printf("%d\n",oprd_stack->element);
            }
            else
            {
                get_head(&oprt_stack, &oprt_head);

                if (input == ')')
                {
                    while (oprt_head != '(')
                    {
                        pop(&oprt_stack);
                        get_head(&oprd_stack, &a);
                        pop(&oprd_stack);
                        get_head(&oprd_stack, &b);
                        pop(&oprd_stack);
                        temp = evaluate(b,(char)oprt_head, a);
                        printf("b %d %c a %d = %d\n", b, oprt_head,a,temp);
                        push(&oprd_stack, temp);
                        
                        get_head(&oprt_stack, &oprt_head);
                    }
                    pop(&oprt_stack);
                    continue;
                }
                prece = precede(oprt_head, input);
                if (prece < 0)
                {
                    pop(&oprt_stack);
                    get_head(&oprd_stack, &a);
                    pop(&oprd_stack);
                    get_head(&oprd_stack, &b);
                    pop(&oprd_stack);
                    temp = evaluate(b,(char)oprt_head, a);
                    printf("b %d %c a %d = %d\n", b, oprt_head,a,temp);
                    push(&oprd_stack, temp);
                }
                push(&oprt_stack, input);
            }
        }
        get_head(&oprt_stack, &oprt_head);
        while (oprt_head != '#')
        {
             pop(&oprt_stack);
             get_head(&oprd_stack, &a);
             pop(&oprd_stack);
             get_head(&oprd_stack, &b);
             pop(&oprd_stack);
             temp = evaluate(b,(char)oprt_head, a);
             printf("b %d %c a %d = %d\n", b, oprt_head,a,temp);
             push(&oprd_stack, temp);
            get_head(&oprt_stack, &oprt_head);
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
