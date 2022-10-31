#include<stdio.h>
#include<stdlib.h>

#ifndef BINARYTREE_H
#define BINARYTREE_H

#define DEBUG 1


typedef struct BTNode{
    char elem;
    struct BTNode *lchild, *rchild;
}BTNode, *BinaryTree;

//从输入构建二叉树先序递归遍历
void CreateBinaryTree(BinaryTree * bt)
{
    char ch = 0;

    ch = getchar();
    if (ch == '#')
    {
        *bt = NULL;
        return;
    }
    else
    {
        if ((*bt = (BTNode *)malloc(sizeof(BTNode))))
        {
            (*bt)->elem = ch;
            CreateBinaryTree(&((*bt)->lchild));
            CreateBinaryTree(&((*bt)->rchild));
        }
        else
        {
            printf("分配空间失败\n");
            exit(1);
        }
    }
}

//判断两颗树是否相等，相等返回1，不想等返回0
int IsEqual(BinaryTree bt1, BinaryTree bt2)
{
    //int m = 0;
    //int n = 0;

    if (bt1 && bt2)
    {
        if (bt1->elem != bt2->elem)
            return 0;
        else
        {
            if (IsEqual(bt1->lchild, bt2->lchild) && IsEqual(bt1->rchild, bt2->rchild))
            //if (m == 1 && n==1)    用逻辑方法
                return 1;
            else
                return 0;
        }
    }
    else if (!bt1 && !bt2)      //bt1 bt2同时为空
    {
        return 1;
    }
    else            //bt1 bt2 一个为空一个非空
        return 0;

}

//统计树中叶节点的数量
int CountLeaves(BinaryTree  bt)
{
    if (!bt)
        return 0;
    else
    {
        if (!bt->lchild && !bt->rchild)
            return 1;
        else
            return (CountLeaves(bt->lchild) + CountLeaves(bt->rchild));
    }
}

//交换树中的左右孩子
void ExchangeChild(BinaryTree bt)
{
    BTNode *temp;

    if (!bt)
        return;
    else
    {
        temp = bt->lchild;
        bt->lchild = bt->rchild;
        bt->rchild = temp;
        ExchangeChild(bt->lchild);
        ExchangeChild(bt->rchild);
    }
}


//双序遍历
void AccessRootTwice(BinaryTree bt)
{
    if (bt != NULL)
    {
        printf("%c",bt->elem);
        AccessRootTwice(bt->lchild);
        printf(" %c",bt->elem);
        AccessRootTwice(bt->rchild);
    }
}

//计算二叉树高度
int GetDepth(BinaryTree bt)
{
    int m = 0;
    int n = 0;

    if (!bt)
        return 0;
    else
    {
        m = GetDepth(bt->lchild);
        n = GetDepth(bt->rchild);
        if (m > n)
        {
            return m+1;
        }
        else
            return n+1;
    }
}

//计算二叉树的最大宽度
//要在函数外创建一个整型数组n+1个元素， i初始为1
void GetWidest(BinaryTree bt, int *ar, int i)
{
    if(bt)
    {
        ar[i]++;
        GetWidest(bt->lchild, ar, i+1);
        GetWidest(bt->rchild, ar, i+1);
    }
}



//释放空间
void FreeTree(BinaryTree *bt)
{
    if (NULL == (*bt))
        return;
    else
    {
        FreeTree(&((*bt)->lchild));
        FreeTree(&((*bt)->rchild));
        free((*bt));
    }
}

void LeafToRoot(BinaryTree bt, char *ch_ar, int i)     //读取输入到一颗完整的二叉树
                                                      //就会停止，换行符也会被读取
{
    if (bt)
    {
        ch_ar[i] = bt->elem;
        if (!bt->lchild && !bt->rchild)
        {
            while (i >= 1)
            {
                printf(" %c ",ch_ar[i--]);
            }
            putchar('\n');
        }
        else
        {
            LeafToRoot(bt->lchild, ch_ar, i+1);
            LeafToRoot(bt->rchild, ch_ar, i+1);
        }
    }
}

#endif
