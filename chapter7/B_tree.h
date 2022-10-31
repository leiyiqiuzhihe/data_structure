//插入时搜索返回的i值，要插入的位置是i+1

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"commonhead.h"

#ifndef  B_TREE_H
#define  B_TREE_H

#define  M   3     //B-树的阶
int floor_trees = ((M%2) == 0)?(M/2) : (M/2 + 1);   //一个节点中子树数的下限

typedef  struct  BTNode
{
    int  keynum;                //结点中关键字的个数，结点的大小
    struct BTNode *parent;        //指向双亲结点
    int  k[M+1];                //关键字向量， 0号单元未用
    struct BTNode  *ptr[M+1];   //子树指针向量
    char *recptr[M+1];        //记录 指针向量，0号单元未用 记录的类型不确定，这里是字符串
}BTNode, *BTree;

typedef  struct
{
    BTNode *pt;          //指向找到的结点
    int   i;             //1..m,在结点中的关键字序号
    int   tag;           //1: 查找成功， 0：查找失败
}Result;


Result BTreeSearch(BTree *bt, int e);
static BTNode * NewNodeAndInit();
static char *GetRecord();
static void SplitNode(BTNode *p, BTNode **ap, char **recptr, int *e);
static int SearchNode(BTNode *p, int e);
static void InsertMoveDatas(BTNode *p, int i);
int InsertBTree(BTree *bt,BTNode *p, int i,int e);
static void MergeNode(BTNode *dest, BTNode* sourcefirst, int i, BTNode *source2);
void RemoveKeyInNode(BTNode *brother,int k_i);
static Result  SearchMin(BTNode *rchild);
static Result  SearchMax (BTNode *lchild);
static void DeleteMoveDatas(BTNode *p, int i);
int BTreeDeleteKey(BTree *bt,BTNode *p, int i,int e);     //开始时p，i是BTreeSearch的返回值，
void Show_Bt(BTree bt, int depth);
void Free_Bt(BTree *bt);



Result  BTreeSearch(BTree *bt, int e)         //需要一个Result结构接收返回值
{                                 //如果bt中没有e，就返回可以插入e的结点（只能是最下面的非终端结点
    int i = 0;                    //没考虑到bt是空树怎么办
    int n = 0;
    BTNode *q = *bt, *p = 0;
    Result temp;
    _Bool find = false;

    if (!(*bt))
        {
            printf("树已空！！！\n");
        }
    memset(&temp,0,sizeof(Result));
    while (q && !find)
    {
        n = q->keynum;
        for (i = 1;i <= n;i++)
        {
            if (e == q->k[i])
            {
                find = true;
                break;
            }
            else if (i == 1 && e < q->k[1])          //返回的i不会小于1
            {
                p = q;
                q = q->ptr[0];       //lchild
                break;         //跳出for 保持i为当前值用于返回
            }
            else if (i < n && e > q->k[i] && e < q->k[i+1])      //key 是有序的
            {
                p = q;
                q = q->ptr[i];       //lchild
                break;         //跳出for
            }
            else if (i == n && (e > q->k[i]))
            {
                p = q;
                q = q->ptr[i];          //rchild
                break;         //跳出for
            }
        }
    }
    if (find)
    {
        temp.pt = q;
        temp.i = i;
        temp.tag = 1;

        return temp;
    }
    else
    {
        if (i == 1 && e < p->k[1])
            temp.i = 1;
        else
            temp.i = i+1;
        temp.pt = p;          //当q不指向根结点，p指向q的父结点
        temp.tag = 0;

        return temp;
    }
}
/*
 * 插入时确定插入位置的值要特别小心处理，有根据这里返回值移动数据的函数
 * 这里是开始如果这里错了下面就不能对
 * 要对关键字数组的第一个元素和最后一个元素特别留心
 * 第一个元素时，if (e < k[1]), e就要插入到第一个元素的位置
 * 剩下的如果e第一次大于某个k[i],e就插入到 i+1 处
 */




static BTNode * NewNodeAndInit()
{
    BTNode * temp = NULL;
    
    if (!(temp = (BTNode *)malloc(sizeof(BTNode))))
    {
        perror("NewNode malloc failed");
        exit(EXIT_FAILURE);
    }
    memset(temp,0,sizeof(BTNode));

    return temp;
}


static char * GetRecord()
{
    char *temp = NULL;

    if((temp = (char *)malloc(80*sizeof(char))))
    {
        printf("请输入要插入的新记录( 不超过80字符 )：\n");
        s_gets(temp,80);
    }
    else
    {
        perror("获取记录时malloc failed");
        exit(EXIT_FAILURE);
    }

    return temp;
}

static void SplitNode(BTNode *p, BTNode **ap, char **recptr, int *e)
{
    int n = p->keynum;
    int i = 1;
    int copy_start = floor_trees+1;

    if (n != M)
    {
        printf("当前结点的关键字数小余M-1，还不用split\n");
        return;
    }

    (*e) = p->k[floor_trees];
    (*recptr) = p->recptr[floor_trees];
    (*ap) = NewNodeAndInit();
    if ((*ap))             /* 移动数据到*ap， 并清理p中的相关数据 */
    {
        printf("split 新结点分配空间成功\n");
        (*ap)->parent = p->parent;
        (*ap)->ptr[0] = p->ptr[floor_trees];
        i = 1;
        while(copy_start <= n)
        {
            (*ap)->k[i] = p->k[copy_start];
            p->k[copy_start] = 0;
            (*ap)->ptr[i] = p->ptr[copy_start];
            p->ptr[copy_start] = 0;
            (*ap)->recptr[i] = p->recptr[copy_start];
            p->recptr[copy_start] = 0;
            (*ap)->keynum++;
            p->keynum--;              /* 别忘了keynum */
            copy_start++;
            i++;
        }
    }
    p->k[floor_trees] = 0;
    p->recptr[floor_trees] = 0;
    p->keynum--;
    printf("结点分裂成功\n");
}


static int SearchNode(BTNode *p, int e)        //after split检查分离出的key，插入父结点哪里
{                                               //返回值的后面
    int i = 1;
    int n = p->keynum;

    if (!p)
    {
        printf("新key要插入的结点不存在\n");
        return 0;
    }
    for (i = 1;i <= n; i++)
    {
        if (e < p->k[i])                //没有<= 或 >= 相等就是有重复的key
            return i;
    }

    return i;          //这时的i是n+1，for循环到最后了
}

static void InsertMoveDatas(BTNode *p, int i)       //插入时移动数据 把i+1空出来
{                                                  //上面是不对的，插入到i 就要把i空出来所以 n>=i
    int n = p->keynum;

    if (n < M)
    {
        while(n >= i)
        {
            p->k[n+1] = p->k[n];
            p->ptr[n+1] = p->ptr[n]; 
            p->recptr[n+1] = p->recptr[n];
            n--;
        }
    }
    else
    {
        printf("intsert 时keynum出错\n");
        exit(EXIT_FAILURE);
    }
}

//如果查找失败，插入时i分2中情况，i<keynum,需要移动数据，i=keynum时在最后插入

int InsertBTree(BTree *bt,BTNode *p, int i,int e)     //开始时p，i是BTreeSearch的返回值，
{
    //BTNode *parent = p->parent;        //指向被插入结点的父结点
    BTNode *ap = NULL;                 //指向新插入的子树，
    BTNode *new_root = NULL;
    int n = p->keynum;
    int m = 0;
    _Bool tag_new = true;               //插入新的key时，要从输入获取记录，分裂后不用新记录
    char *temprecord = NULL;          //分裂结点时临时保存记录信息
    _Bool finished = false;

    while (p && !finished)
    {
        if (i > (n+1))
        {
            printf("要插入的位置不对 i > keynum+1");
            return 0;      //插入失败
        }
        if (i <= (n+1))
        {
            InsertMoveDatas(p,i);
            p->k[i] = e;
            if (tag_new)
            {
                p->recptr[i] = GetRecord();       //从输入获取记录内容
                tag_new = false;
            }
            else
                p->recptr[i] = temprecord;
            p->ptr[i] = ap;
            p->keynum += 1;
        }
/*        else
        {
            InsertMoveDatas(p,i);
            p->k[i] = e;
            if (tag_new)
            {
                p->recptr[i] = GetRecord();
                tag_new = false;
            }
            else
                p->recptr[i] = temprecord;
            p->ptr[i] = ap;
            p->keynum += 1;
        }                         //插入完成
*/

        n = p->keynum;

        if (n == M)        //关键字多于M-1 要分裂节点
        {
            SplitNode(p,&ap,&temprecord,&e);   //分裂结点, 更新这几个参数的值，在定义函数时注意变与不变
            p = p->parent;
            if (p)
                i = SearchNode(p,e);        //p,e是更新后的， e要插入到p的哪个位置
            else
                break;
        }
        else
            finished = true;
    }

    if (!finished)     //如果一直分裂节点到根节点, 根节点也分裂了，或者是空树
    {
        new_root  = NewNodeAndInit();
        if (new_root)
        {
            new_root->parent = NULL;
            //p->parent = ap->parent = (*bt);    //如果分裂到根结点， 此时p的值是 NULL
            (*bt)->parent = ap->parent = new_root;    //如果分裂到根结点， 此时p的值是 NULL
            new_root->ptr[0] = (*bt);
            (*bt) = new_root;
            (*bt)->recptr[1] = temprecord;
            (*bt)->ptr[1] = ap;
            (*bt)->k[1] = e;
            (*bt)->keynum =1;
        }
        else
        {
            printf("新根结点空间分配失败\n");
            exit(EXIT_FAILURE);
        } 
    }

    return 1;
}


static void MergeNode(BTNode *dest, BTNode* sourcefirst, int i, BTNode *source2)
{                                          //只是合并，释放在删除父结点数据时执行
    int d_knum = dest->keynum;
    int s2_knum = source2->keynum;
    int s2_n = 0;

    if (dest && sourcefirst && source2)
    {
        dest->k[++d_knum] = sourcefirst->k[i];
        dest->recptr[d_knum] = sourcefirst->recptr[i];
        dest->ptr[d_knum] = source2->ptr[0];

        for (s2_n = 1; s2_n <= s2_knum && d_knum < M; s2_n++)
        {
            dest->k[++d_knum] = source2->k[s2_n];
            dest->recptr[d_knum] = source2->recptr[s2_n];
            dest->ptr[d_knum] = source2->ptr[s2_n];
        }

        if (d_knum < M)
            dest->keynum = d_knum;
        else
            printf("合并时dest->keynum出错\n");
        free(source2);      //释放被合并结点的空间
        printf("已释放被合并的结点\n");
    }
}

void RemoveKeyInNode(BTNode *brother,int k_i)
{
    int n = brother->keynum;
    int i = k_i;

    if (k_i > n)
    {
        printf("要删除的位置大于当前结点的k_num\n");
        exit(EXIT_FAILURE);
    }
    while (i < n)
    {
        brother->k[i] = brother->k[i+1];
        brother->ptr[i] = brother->ptr[i+1];
        brother->recptr[i] = brother->recptr[i+1];
        i++;
    }
    if (i == n)
    {
        brother->k[i] = 0;
        brother->ptr[i] = 0;
        brother->recptr[i] = 0;
    }
    brother->keynum -= 1;
}


static Result  SearchMin(BTNode *rchild)
{
    Result  ret_val;
    BTNode *ptr_0 = NULL;
    BTNode *pre_ptr = rchild;
    //int i = 0;

    memset(&ret_val, 0, sizeof(Result));
    if (!rchild)
    {
        printf("要查找的右孩子不存在\n");
        exit(EXIT_FAILURE);
    }

    //i = rchild->k[1];
    ptr_0 = rchild->ptr[0];
    while((ptr_0))
    {
        //i = ptr_0->ptr[0];
        pre_ptr = ptr_0;
        ptr_0 = ptr_0->ptr[0];
    }
    ret_val.pt = pre_ptr;
    ret_val.i = 1;
    ret_val.tag = 1;

    return ret_val;
}


static Result  SearchMax (BTNode *lchild)
{
    Result  ret_val;
    BTNode *ptr_kn = NULL;
    BTNode *pre_ptr = lchild;
    int n = 0;

    memset(&ret_val, 0, sizeof(Result));
    if (!lchild)
    {
        printf("要查找的左孩子不存在\n");
        exit(EXIT_FAILURE);
    }

    n = lchild->keynum;
    ptr_kn = lchild->ptr[n];
    while((ptr_kn))
    {
        n = pre_ptr->keynum;
        pre_ptr = ptr_kn;
        ptr_kn = ptr_kn->ptr[n];
    }
    ret_val.pt = pre_ptr;
    ret_val.i = pre_ptr->keynum;
    ret_val.tag = 1;

    return ret_val;
}


static void DeleteMoveDatas(BTNode *p, int i)       //插入时移动数据 把i+1空出来
{
    int n = p->keynum;

    if (n < M)
    {
        while(n >= i)
        {
            p->k[n+1] = p->k[n];
            p->ptr[n+1] = p->ptr[n]; 
            p->recptr[n+1] = p->recptr[n];
            n--;
        }
    }
    else
    {
        printf("Delete 时keynum出错\n");
        exit(EXIT_FAILURE);
    }
}

static int Position(BTNode *p, BTNode *child)
{
    int i = 0;
    int n = p->keynum;
    int find = 0;

    for (i = 0;i <= n && !find;i++)
    {
        if (p->ptr[i] == child)
        {
            find = 1;
            break;
        }
    }
    if (find)
        return i;
    else
    {
        printf("child 不在父结点中（删除时确定左右兄弟）\n");
        exit(EXIT_FAILURE);
    }
}

//为了与InsertBTree的接口保持一致，先用查找函数，查找给定的key，如果
//查找失败就删除失败，如果查找成功就把找到的p与key一起作为delete函数的参数
//对p不是最下层非终端结点的处理在delete内部处理

int BTreeDeleteKey(BTree *bt,BTNode *p, int i,int e)     //开始时p，i是BTreeSearch的返回值，
{
    Result min, max;
    BTNode *parent = NULL;
    int position = 0;
    BTNode *rbrother = NULL, *lbrother = NULL;
    int knum = 0;

    if (p->ptr[i])
    {
        min = SearchMin(p->ptr[i]);
        p->k[i] = (min.pt)->k[min.i];
        p->recptr[i] = (min.pt)->recptr[min.i];
        p = min.pt;
        i = min.i;
    }
    else if (p->ptr[i-1])    //似乎这个永远 不会执行
    {
        max = SearchMax(p->ptr[i-1]);
        p->k[i] = (max.pt)->k[max.i];
        p->recptr[i] = (max.pt)->recptr[max.i];
        p = max.pt;
        i = max.i;
    }
    //经过上面的判断或替换p当前已是最下层的非终端结点可直接删除其中的关键字
    RemoveKeyInNode(p,i);              //删除数据要整理数据在Remove内部整理吧 Don't forget keynum

    //判断p->keynum
    if (p->keynum >= floor_trees-1)
    {
        printf("删除成功\n");
        return 1;
    }
    else
    {
        while ((parent = p->parent) && p->keynum < floor_trees-1)
        {
            position = Position(parent, p);     //确定p在其parent中的位置
            //if (position >= 0 && position < parent->keynum)
            rbrother = parent->ptr[position+1];
            if (position == 0)
                lbrother = NULL;
            else
                lbrother = parent->ptr[position-1];
            knum = p->keynum;

            //借值成功即可返回 用p与其brother的中间数作为 中转站
            if ((rbrother) && rbrother->keynum > floor_trees-1)
            {
                //min = SesrchMin(rbrother);
                p->k[knum+1] = parent->k[position+1];
                p->recptr[knum+1] = parent->recptr[position+1];
                p->keynum++;

                parent->k[position+1] = rbrother->k[1];
                parent->recptr[position+1] = rbrother->recptr[1];
                
                RemoveKeyInNode(rbrother,1);    //删除数据时把被删数据后面的数据，向前移动

            }
            else if ((lbrother) && lbrother->keynum > floor_trees-1)
            {
                DeleteMoveDatas(p, 1);       //把位置1空出来
                p->k[1] = parent->k[position];
                p->recptr[1] = parent->recptr[position];
                p->keynum++;
                parent->k[position] = lbrother->k[lbrother->keynum];
                parent->recptr[position] = lbrother->recptr[lbrother->keynum];
                RemoveKeyInNode(lbrother,lbrother->keynum);
            }
            //借值失败，合并后要进入while
            else
            {
                if (rbrother && rbrother->keynum == floor_trees-1)
                {
                    //temp = NewNodeAndInit();
                    MergeNode(p,parent,position+1,rbrother);
                    RemoveKeyInNode(parent,position+1);
                    p = parent;
                    printf("实际删除数据的结点与其rbrother合并\n");
                }
                else if (lbrother && lbrother->keynum == floor_trees-1)
                {
                    MergeNode(lbrother,parent,position,p);
                    RemoveKeyInNode(parent,position);
                    p = parent;
                    printf("实际删除数据的结点并入其lbrother合并\n");
                }
                else
                {
                    printf("出错了！！！！删除时出错，被删key所在结点左右兄弟的keynum出错\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    if (!(p->parent))             //处理合并到根结点的情况，根结点keynum可能是0
    {                             //对只有根结点，删除key后根结点变空的情况也适用
        if (p->keynum == 0)
        {
            (*bt) = p->ptr[0];
            if (*bt)
                (*bt)->parent = NULL;
            free(p);
            return 1;
        }
    }
}


void Show_Bt(BTree bt, int depth)
{
    int n = 0;
    int i = 0;

    if (bt)
    {
        printf("\n这是树的第%d层\n",depth);
        n = bt->keynum;
        for (i = 1; i <= n;i++)
        {
            printf("\t\t第%d个关键字：%d,记录：%s\n",i,bt->k[i],bt->recptr[i]);
        }
        for (i = 0; i <= n; i++)
        {
            Show_Bt(bt->ptr[i],depth+1);
        }
    }
}

void Free_Bt(BTree *bt)
{
    int n = 0;
    int i = 0;

    if (*bt)    //这里也要回收空间
    {
        n = (*bt)->keynum;
        for (i = 0; i <= n; i++)
        {
            if ((*bt)->recptr[1])
                free((*bt)->recptr[i]);
            if ((*bt)->ptr[i])
                Free_Bt(&((*bt)->ptr[i]));
        }
        free(*bt);
    }
}
#endif
