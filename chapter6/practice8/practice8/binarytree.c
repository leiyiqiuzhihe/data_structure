#include<stdio.h>
#include<stdlib.h>
#include"binarytree.h"

int main(void)
{
    BinaryTree bt1, bt2;
    //int tag = 0;
    int leaves = 0;
    int depth = 0;
    int i = 1;       //i表示层数
    int max_width = 0;
    char ch;
    int *ar = NULL;
    char *ch_ar = NULL;

    printf("请输入bt1(以#开头):\n");
    if ((ch = getchar()) == '#')
        CreateBinaryTree(&bt1);
    else
    {
        printf("请以‘#’开头\n");
        exit(0);
    }
    while ((ch = getchar()) != '\n')
           printf("%c\n",ch); 
    printf("请输入bt2(以#开头):\n");
    if ((ch = getchar()) == '#')
        CreateBinaryTree(&bt2);
    else
    {
        printf("请以‘#’开头\n");
        exit(0);
    }
    while ((ch = getchar() != '\n'))
            putchar(ch);

    if (IsEqual(bt1,bt2))
        printf("bt1,bt2是相等的二叉树\n");
    else
        printf("BT1,BT2不相等\n");

    leaves = CountLeaves(bt1);
    printf("bt1 have %d leaves\n",leaves);

    printf("双序遍历bt1:\n");
    AccessRootTwice(bt1);

    printf("交换bt1的左右孩子\n");
    ExchangeChild(bt1);
    printf("交换后的结果是\n");
    AccessRootTwice(bt1);

    depth = GetDepth(bt1);
    printf("bt1的深度是%d\n",depth);

    ar = (int *)malloc((depth+1)*sizeof(int));
    i = 1;
    GetWidest(bt1, ar, i);
    ar[0] = 0;
    max_width = 0;
    for (i = 1; i <= depth; i++)
    {
        if (ar[i] > max_width)
                max_width = ar[i];
    }

    printf("bt1 的最大宽度是%d \n",max_width);

    ch_ar = (char*)malloc((depth+1)*sizeof(char));
    i = 1;
    LeafToRoot(bt1, ch_ar, i);

    free(ch_ar);
    free(ar);
    FreeTree(&bt1);
    FreeTree(&bt2);

    return 0;
}

