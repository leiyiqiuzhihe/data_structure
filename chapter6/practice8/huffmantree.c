#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"huffmantree.h"


#define SIZE 128

int main(void)
{
    FILE *fs = NULL, *fcode = NULL, *fdecode = NULL;
    CodeNode *hfc = NULL;      //用于指向malloc的哈夫曼编码数据
    HFNode   *hft = NULL;      //哈夫曼树
    int leaves = 0;
    int count[SIZE] = {0};
    int index_root = 0;
    int s1 = 0;
    int s2 = 0;          //s1，s2左右子树
    int i = 0;

    OpenSourceFile(&fs);
    AnalysisSource(fs, count);
    printf("已分析文件\n");
    leaves = CountChar(count);
    printf("有%d个叶节点\n",leaves);
    /*if (!(hft = (HFNode *)malloc(leaves * sizeof(HFNode))))
    {
        printf("分配hft空间失败\n");
        exit(0);
    }*/
    InitHuffTree(&hft, count, leaves);
    i = 1;
    while (!hft[index_root].lchild && !hft[index_root].rchild && i < leaves)
    {
        Select(hft, &s1, &s2, leaves+i);
        CreateHuffTree(hft,s1,s2,leaves+i);
        i++;
    }

    ShowHft(hft,2*leaves);
    printf("已显示hft\n");

    if (!(hfc = (CodeNode*)malloc((leaves+1)*sizeof(CodeNode))))
    {
        printf("分配hfc空间失败\n");
        exit(0);
    }
    CreateHfCode(hft,hfc,leaves);
    printf("显示哈夫曼码：\n");
    ShowHfc(hfc, leaves);
    system("pause");
    OpenCode(&fcode);
    Coder(fs, fcode, hfc, leaves);
    printf("编码完成\n");
    //fclose(fcode);
    /*fcode = NULL;
    OpenCode(&fcode);*/      //这里要重复打开文件，是文件打开模式的问题暂时解决不了
    putc(EOF,fcode);
    rewind(fcode);

    OpenDecode(&fdecode);
    Decoder(fcode, fdecode,hft,leaves);
    printf("解码完成\n");

    for (i = 1; i <= leaves; i++)
         free(hfc[i].ptcd);
    free(hfc);
    free(hft);
    fclose(fs);
    fclose(fcode);
    fclose(fdecode);

    return 0;
}
