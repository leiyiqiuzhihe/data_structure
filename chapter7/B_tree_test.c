#include<stdio.h>
#include<stdlib.h>
#include"commonhead.h"
#include"B_tree.h"

#define BUG_PRINT 1


int main(void)
{
    int key = 0;
    BTree bt = NULL;
    Result result;
    BTNode *start_root;

    if (!(start_root = (BTNode *)malloc(sizeof(BTNode))))    //最开始是直接声明一个node，使用free时报错
    {                                                        //free只能用于molloc申请的空间
        perror("初始根结点空间分配失败\n");
        exit(EXIT_FAILURE);
    }
    memset(start_root,0,sizeof(BTNode));
    start_root->k[1] = 5;
    start_root->keynum = 1;

    printf("请输入“开始”初始化第一个记录\n");
    start_root->recptr[1] = (char*)malloc(20*sizeof(char));
    if (start_root->recptr[1])
        s_gets(start_root->recptr[1], 19);
    else
    {
        perror("分配空间失败\n");
        exit(EXIT_FAILURE);
    }
    bt = start_root;             //不要一下子写完再调试，写完一个功能就调试
    memset(&result,0,sizeof(Result));
    printf("Please enter one key(int type) you want to insert(500 to quit):");
    while(scanf("%d",&key) == 1 && key != 500)
    {
        eatline();
#ifdef BUG_PRINT
        printf("已读取key：%d\n",key);
#endif
        result = BTreeSearch(&bt,key);
        if (!(result.tag) )       //被搜索的树是空树的情况要考虑到
        {
            InsertBTree(&bt,result.pt,result.i,key);
        }
        else
        {
            printf("key %d 已在树中\n",key);
        }
        printf("Please enter one key(int type) you want to insert(500 to quit):");
    }

    printf("\033[31m 请输入要删除的关键字，（整型，502 to quit）：\033[0m");
    while (scanf("%d",&key) == 1 && key != 502)
    {
        eatline();
        printf("已读取要删除的key： %d\n",key);
        result = BTreeSearch(&bt,key);
        if (result.tag)
        {
            BTreeDeleteKey(&bt,result.pt,result.i,key);
#ifdef BUG_PRINT
            printf("Delete key:%d, Done\n",key);
#endif
        }
        else
        {
            printf("\033[33m key:%d不在树中\n\033[0m",key);
        }
        printf("\033[31m 请输入要删除的关键字，（整型，502 to quit）：\033[0m");
    }

    Show_Bt(bt,1);
#ifdef BUG_PRINT
        printf("已读取显示完成\n");
#endif
    Free_Bt(&bt);
#ifdef BUG_PRINT
        printf("已成释放空间\n");
#endif
    return 0;
}
