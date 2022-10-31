//平衡二叉搜索树main函数

#include<stdio.h>
#include<stdlib.h>
#include"BBST.h"
#include"commonhead.h"

int main(void)
{
    BBSTree bbst = NULL;
    int e = 0;

    printf("请输入要插入的节点，-20 退出\n");
    while (scanf("%d",&e) == 1 && e != -20)
    {
        InsertBBSTree(&bbst, e);
        printf("请输入下一个要插入的节点， -20 退出\n");
    }
    
    printf("输入完成\n\n显示树的内容:\n");
    InorderShowBBST(&bbst);

    return 0;
}
