//二分查找递归实现，从stdin获取数据
#include<stdio.h>
#include"../chapter6/commonhead.h"
#define BUFSIZE  50

int ReBinSearch(int key, int low, int high, int *ar);

int main(void)
{
    int ar[BUFSIZE] = {0};
    int length = 0;
    int i = 0;
    int temp = 0;
    int key = 0;
    int low = 0;
    int high = 0;

    while (scanf("%d",&temp) != EOF && length < BUFSIZE)
    {
        printf("%d",temp);
        ar[length++] = temp;

    }
    puts("读取数据成功！");
    eatline();

    printf("请输入key\n");
    scanf("%d",&key);
    eatline();
    low = 0;
    high = length - 1;
    i = ReBinSearch(key, low, high, ar);
    if (i != -1)
        printf("ar 中第%d个是%d与key相等\n",i,ar[i]);
    else
        puts("search failed!!!");

    return 0;

}

int ReBinSearch(int key, int low, int high, int *ar)
{
    int mid = (low + high) / 2;
    if (low <= high)
    {
        if (ar[mid] == key)
            return mid;
        else if (ar[mid] > key)
        {
            high = mid - 1;
            return ReBinSearch(key,low,high,ar);
        }
        else
        {
            low = mid + 1;
            return ReBinSearch(key,low,high,ar);
        }
    }
    else
        return -1;
}         //要设置一个返回值如果搜索失败，供调用它的函数检测
