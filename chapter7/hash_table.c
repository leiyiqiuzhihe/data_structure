#include<stdio.h>
#include<stdlib.h>
#include"hash_table.h"


int main(void)
{
    int search_times = 0;
    int insert_pos = 0;
    int input_key = 0;
    HashTable ht;

    HashInit(&ht);
    printf("Insert:\n");
    printf("请输入1个要插入的key(int 500 to quit):\n");
    while ((scanf("%d",&input_key) == 1) && (input_key != 500))
    {
        insert_pos = HashInsert(&ht, input_key);
        if (insert_pos != -1)
            printf("newkey 插入到表的第%d个位置\n",insert_pos+1);
        else
        {
            printf("表已满\n");
            break;
        }
        printf("请输入1个要插入的key(int 500 to quit):\n");
    }

    printf("\n\nSearch\n");
    printf("请输入要查找的key(int 500 to quit):\n");
    while ((scanf("%d",&input_key) == 1) && (input_key != 500))
    {
        search_times = HashSearch(&ht, input_key);
        printf("\n查找%d,比较了%d次\n\n",input_key,search_times);
        printf("请输入1个要查找的key(int 500 to quit):\n");
    }

    printf("\nShow hashtable:\n");
    ShowTable(&ht);

    printf("\nDone!!!\n");
    return 0;
}
