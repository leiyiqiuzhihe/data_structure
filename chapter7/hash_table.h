#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define SIZE 20
#define NULLVAL 0

typedef struct HashTalbe
{
    int ht[SIZE];
    int keynum;
}HashTable;

void HashInit(HashTable *ht)
{
    memset(ht,0,sizeof(HashTable));
}
static int HashFuc(int key)         //计算h0
{
    int ret_val = 0;
    int mode = (SIZE/2 - 1) * 2 + 1;         //小于表长的最大质数

    if (mode > 2)
        ret_val = key % mode;
    else
    {
        printf("表长要大于等于4\n");
        exit(EXIT_FAILURE);                          //使用的时候检查返回值
    }
    return ret_val;
}

int HashInsert(HashTable *ht, int key)
{
    int success = 0;
    int i;
    int n = 0;
    int h0 = HashFuc(key);
    int mode = (SIZE/2 - 1) * 2 + 1;         //小于表长的最大质数

    if (h0 >= 0 && h0 < SIZE)
    {
        if (ht->ht[h0] == NULLVAL)
        {
            ht->ht[h0] = key;
            ht->keynum += 1;
            success = 1;

            return h0;
        }
        i = 1;
        while(!success && i < SIZE)     //h0,是i 为0的n
        {
            n = (h0 + i) % mode;
            if (ht->ht[n] == NULLVAL)
            {
                ht->ht[n] = key;
                ht->keynum += 1;
                success = 1;
                
                return n;            //返回插入的位置
            }
            i++;
        }
        if (!success)
        {
            printf("表已经满了\n");
            return -1;
        }
    }
    else
    {
        printf("h0越界\n");
        exit(EXIT_FAILURE);
    }
}

int HashSearch(HashTable *ht, int key)
{
    int find = 0;
    int i = 0;
    //int hn = 0;
    int h0 = HashFuc(key);
    int mode = (SIZE/2 - 1) * 2 + 1;
    int n = 0;

    if (h0 >= 0 && h0 < mode)
    {
        for (i = 0; i < SIZE && !find; i++)
        {
            n = (h0 + i) % mode;   //这里最开始n处是 h0，与插入不匹配，会查找失败
            if (ht->ht[n] == NULLVAL)
            {
                printf("key %d 不在此表中\n",key);
                return (i + 1);       //返回比较次数
            }
            else if (ht->ht[n] == key)
            {
                printf("key %d 是第 %d个元素\n", key,n+1);
                return (i + 1);
            }
        }
        if (i == SIZE)
        {
            printf("已经遍历整个表，%d 不在表中",key);
            return i;
        }
    }
    else
    {
        printf("h0越界\n");
        exit(EXIT_FAILURE);
    }
}

void ShowTable(HashTable *ht)
{
    int i = 0;

    printf("\n");
    for (i = 0; i < SIZE; i++)
        printf("%d  ",ht->ht[i]);
    printf("\n");
}
#endif

