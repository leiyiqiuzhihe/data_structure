//平衡二叉树相关的头文件 balanc biary search tree
//递归实现节点的插入，插入的结点只可能在search这个值所走过的路径终点，
//新插入的结点的父结点的平衡因子会被改变，这个平衡因子的初值要满足这是一个平衡二叉树的
//条件（即它的初值只能是-1,0,1）
//用函数的返回值判断树的高是否改变
//
//
//自己想办法简单测试了一下，解决了一些bug

#include<stdio.h>
#include<stdlib.h>

#ifndef   BBST_H
#define   BBST_H

typedef struct {
        int key;
        void *info;     //这个指针使用前要强制类型转换
}ElemType;

typedef struct BBSTNode{
        ElemType   data;
        int  balance;
        struct BBSTNode *parent;
        struct BBSTNode *lchild, *rchild;
}BBSTNode, *BBSTree;    //平衡二叉树结点的定义


BBSTNode * SearchBBSTree(BBSTree *bbst, int e)  //为什么用*bbst ？？？在插入结点时
                                        //如果是空树，若用bbst,此时传入函数的是空指针
                                        //新节点插入时要改变树的指针，但这时做不到
{
    BBSTNode *ret_val = NULL;

    if (!(*bbst))
    {
        printf("这是一个空树\n");
        return ret_val;
    }
    ret_val = *bbst;
    while (ret_val)
    {
        if (ret_val->data.key == e)
        {
            printf("找到了key等于e的结点\n");
            return ret_val;
        }
        else if (ret_val->data.key > e)
        {
            if (ret_val->lchild)
            {
                ret_val = ret_val->lchild;
            }
            else
                return ret_val;
        }
        else
        {
            if (ret_val->rchild)
            {
                ret_val = ret_val->rchild;
            }
            else
                return ret_val;
        }
    }
}        //如果是空树返回空指针，如果找到了key等于额的结点，返回指向这个结点的指针
         //可用于删除结点，
         //如果e不在树中就返回，指向可以把e插在其孩子结点上的结点的指针


BBSTNode * NewNode(int e)
{
    BBSTNode *temp = NULL;

    if (!(temp = (BBSTNode *)malloc(sizeof(BBSTNode))))
    {
        perror("新结点空间分配失败\n");
        exit(1);
    }
    temp->data.key = e;
    temp->balance = 0;
    temp->parent = NULL;
    temp->lchild = NULL;
    temp->rchild = NULL;

    return temp;
}


int InsertBBSTree(BBSTree *bbst, int e)           //四种可能 找到了可以插入结点的位置，就插入
{                                                 //         树中已有关键字相同的结点
    BBSTNode *new_N = NULL;                       //         插入左子树    或插入右子树 
    int ret_high = 0;     //接收递归调用的返回值            LL    LR       RR    RL
    BBSTNode *tempoldroot = NULL;
    BBSTNode *tempnewroot = NULL;

    if (!(*bbst))
    {
        if ( (new_N = NewNode(e)) )
        {
            *bbst = new_N;
            printf("%d插入成功\n",e);
            return 1;
        }
    }
    else if (e == (*bbst)->data.key)
    {
        printf("树中已经有%d了\n",e);
        return 0;
    }

    else if (e < (*bbst)->data.key)
    {
        tempoldroot = NULL;
        tempnewroot = NULL;

        ret_high = InsertBBSTree( &((*bbst)->lchild), e);
        if ((*bbst)->balance + ret_high == 2)
        {
            if ((*bbst)->lchild->balance == -1)      //LR型 先左转  后右转
            {
                tempoldroot = (*bbst)->lchild;
                tempnewroot = tempoldroot->rchild;

                (*bbst)->lchild = tempnewroot;
                tempoldroot->rchild = tempnewroot->lchild;
                tempnewroot->lchild = tempoldroot;

                tempnewroot->balance = 1;
                (tempoldroot->lchild)?(tempoldroot->balance = 1):(tempoldroot->balance = 0);
            }
            
            tempoldroot = NULL;      //下面的临时变量意义不同了
            tempnewroot = NULL;

            //you转  LR型左转后要右转， LL型直接右转

            tempoldroot = (*bbst);        //这里出过错写成了(*bbst)->lchild  
            tempnewroot = tempoldroot->lchild;

            (*bbst) = tempnewroot;
            tempoldroot->lchild = tempnewroot->rchild;
            tempnewroot->rchild = tempoldroot;

            tempoldroot->balance = 0;
            tempnewroot->balance = 0;

            return 0;
        }
        else if ((*bbst)->balance == 0 &&  ret_high  == 1)
        {
            (*bbst)->balance = 1;
            return 1;
        }
        else if ((*bbst)->balance == -1 && ret_high == 1)
        {
            (*bbst)->balance = 0;
            return 0;
        }
        else
            return 0;
    }
    else       //e > (*bbst)->data.key
    {
        tempoldroot = NULL;
        tempnewroot = NULL;

        ret_high = InsertBBSTree(&((*bbst)->rchild), e);
        if ((*bbst)->balance == -1 && ret_high == 1)
        {
            if (((*bbst)->rchild)->balance == 1)      //RL型 先右转  再左转
            {
                tempoldroot = (*bbst)->rchild;
                tempnewroot = tempoldroot->lchild;

                (*bbst)->rchild = tempnewroot;
                tempoldroot->lchild = tempnewroot->rchild;
                tempnewroot->rchild = tempoldroot;

                tempnewroot->balance = -1;
                (tempoldroot->rchild)? (tempoldroot->balance = -1):(tempoldroot->balance = 0);
            }
            tempoldroot = NULL;
            tempnewroot = NULL;

            //RL型右转后    RR型 左转
            tempoldroot = *bbst;
            tempnewroot = tempoldroot->rchild;

            *bbst = tempnewroot;
            tempoldroot->rchild = tempnewroot->lchild;
            tempnewroot->lchild = tempoldroot;

            tempnewroot->balance = 0;
            tempoldroot->balance = 0;

            return 0;
        }
        else if ((*bbst)->balance == 0 && ret_high == 1 )
        {
            (*bbst)->balance = -1;
            return 1;
        }
        else if ((*bbst)->balance == 1 && ret_high == 1)
        {
            (*bbst)->balance = 0;
            return 0;
        }
        else
            return 0;
    }
}


void InorderShowBBST(BBSTree *bbst)
{
    if (*bbst)
    {
        InorderShowBBST(&((*bbst)->lchild));
        printf("%4d",(*bbst)->data.key);
        printf("  这个结点的平衡因子是%d\n",(*bbst)->balance);
        InorderShowBBST(&((*bbst)->rchild));
    }
}

#endif
