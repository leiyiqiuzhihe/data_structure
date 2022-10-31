#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#define NAMELEN 50


typedef struct HFNode{
        char elem;
        int value;
        int parent;
        int lchild, rchild;
}HFNode;

typedef struct CodeNode{
        char elem;
        char *ptcd;
}CodeNode;
char *s_gets(char *str, int n)
{
    char *ret_val = NULL;
    char *find = NULL;

    if ((ret_val = fgets(str,n,stdin)))
    {
        if ((find = strchr(str,'\n')))
            *find = '\0';
        else
            while (getchar() != '\n')
                    ;
    }

    return ret_val;
}

void OpenSourceFile(FILE **fp)
{
    char sourcename[NAMELEN];

    while (!*fp)
    {
        printf("请输入要打开的文件(只读):\n");
        s_gets(sourcename,NAMELEN);
        if ((*fp = fopen(sourcename, "r")))
        {
            printf("%s 已打开\n",sourcename);
            break;
        }
        else
            perror("文件打开失败\n");
    }
}

void OpenCode(FILE **fp)
{
    char sourcename[NAMELEN];

    while (!*fp)
    {
        printf("请输入保存编码的文件:\n");
        s_gets(sourcename,NAMELEN);
        if ((*fp = fopen(sourcename, "a+")))
        {
            printf("%s 已打开\n",sourcename);
        }
        else
            perror("文件打开失败\n");
    }
}


void OpenDecode(FILE **fp)
{
    char sourcename[NAMELEN];

    while (!*fp)
    {
        printf("请输入保存解码的文件:\n");
        s_gets(sourcename,NAMELEN);
        if ((*fp = fopen(sourcename, "a")))
        {
            printf("%s 已打开\n",sourcename);
        }
        else
            perror("文件打开失败\n");
    }
}

//分析源文件字符出现概率ASCII
void AnalysisSource(FILE *fp, int *ar)
{
    char ch;

    ch = getc(fp);
    while (!feof(fp))
    {
        ar[ch-'\0']++;
        ch = getc(fp);
    }
}

//用分析的结果计算源文件中出现的ASCII字符次数
//统计的数量也是叶节点的数量
int CountChar(int *ar)
{
    int i = 0;
    int n = 128;
    int ret_val = 0;

    while (i < n)
    {
        if (ar[i])
            ret_val++;
        i++;
    }

    return ret_val;
}

//填充哈夫曼树的叶节点
void InitHuffTree(HFNode **hft, int *ar, int m)
{
    int i = 0;
    int n = 1;
    int size = 2*m;

   if (!((*hft) = (HFNode *)malloc(size*sizeof(HFNode))))
   {
       printf("hufftree分配空间失败\n");
       exit(0);
   }
    for (i = 0; i < size; i++)
    {
        (*hft+i)->value = 0;
        (*hft+i)->parent = 0;
        (*hft+i)->lchild = 0;
        (*hft+i)->rchild = 0;
    }
    for (i = 0; i < 128; i++)
    {
        if (ar[i])
        {
            (*hft+n)->elem = (char)i;
            (*hft+n++)->value = ar[i];
        }
    }
}


//从树中找到父节点为零，权值最小的两个子树s1,s2是下标
//注意 m的取值
void Select(HFNode *hft, int *s1, int *s2, int m)
{
    int i = 0;
    int min = 0;

    for (i = 1; i < m; i++)
    {
        if ((hft+i)->parent == 0)
        {
            min = (hft+i)->value;
            *s1 = i;
            break;
        }
    }
    for (i = 1; i < m; i++)
    {
        if ((hft+i)->parent == 0 && min > (hft+i)->value)
        {
            min = (hft+i)->value;
            *s1 = i;
        }
    }
    (hft+(*s1))->parent = m;

    for (i = 1; i < m; i++)
    {
        if ((hft+i)->parent == 0)
        {
            min = (hft+i)->value;
            *s2 = i;
            break;
        }
    }
    for (i = 1; i < m; i++)
    {
        if ((hft+i)->parent == 0 && min > (hft+i)->value)
        {
            min = (hft+i)->value;
            *s2 = i;
        }
    }
    (hft+(*s2))->parent = m;
}

void CreateHuffTree(HFNode *hft, int s1, int s2, int m)
{
    (hft+m)->lchild = s1;
    (hft+m)->rchild = s2;
    (hft+m)->value = (hft+s1)->value + (hft+s2)->value;
}

void ShowHft(HFNode *hft, int m)   //m是叶节点的2倍
{
    printf("\telem\t\tparent\t\tlchild\t\trchile\n");
    m--;
    while (m > 0)
    {
        printf("%d\t%5c\t\t%6d\t\t%6d\t\t%6d\n",m,
                        (hft+m)->elem,(hft+m)->parent,(hft+m)->lchild,(hft+m)->rchild);
        m--;
    }
}

//m的值是叶节点的数量
void CreateHfCode(HFNode *hft,CodeNode *hfc,int m)
{
    int i = 0;
    int parent = 0;
    //char temp[m] = {0};
    char *temp;
    int index = m-1;
    int child = 0;

    if (!(temp = (char *)malloc(m)))
    {
        printf("临时字符串空间分配失败\n");
        exit(0);
    }
    temp[index] = '\0';
    for (i = 1; i <= m; i++)
    {
        printf("第%d次循环 \n",i);
        (hfc+i)->elem = (hft+i)->elem;
        parent = (hft+i)->parent;
        printf("第%d次循环复制元素成功 \n",i);

        child = i;
        index = m-1;
        while (parent)
        {
            if ((hft+parent)->lchild == child)
            {
                temp[--index] = '0';
            }
            else
                temp[--index] = '1';
            child = parent;
            parent = (hft+parent)->parent;
        }
        printf("第%d次循环生成编码成功 \n",i);

        (hfc+i)->ptcd = (char*)malloc(m-index);
        printf("%d 分配空间成功\n",i);
        strcpy((hfc+i)->ptcd, temp+index);
        printf("%d 复制字符串成功\n",i);
    }
    free(temp);
}

void ShowHfc(CodeNode * hfc, int m)
{
    printf("\telem\t\tcode\n");
    while (m > 0)
    {
        printf("\t%4c\t\t%s\n",(hfc+m)->elem, (hfc+m)->ptcd);
        m--;
    }
}

void Coder(FILE *source, FILE *destination, CodeNode *hfc, int m)
{
    char ch;
    int i = 0;
    int index = 0;
    int count = 0;

    rewind(source);
    ch = getc(source);
    while (!feof(source))
    {
        for (i = 1; i <= m; i++)
        {
            if (hfc[i].elem == ch)
                break;
        }
        //printf("第%d个字符 已 匹配%c 的编码\n",++count,ch);
        index = 0;
        //ch等于 \0 会怎样
        while ((ch = (hfc[i].ptcd)[index++]) != '\0')
        {
            putc(ch,destination);
        }
        //printf("一个字符编码成功\n");
        ch = getc(source);
    }
}

void Decoder(FILE *source, FILE *destination, HFNode *hft,int m)
{
    char ch;
    int child = 0;
    int i = 0;
    int size = 2*m-1;
    int count = 0;
    
    //rewind(source);
    ch = getc(source);                     //source的打开模式要可以读
    //printf("解码前的ch是%c\n",ch);
    while (!(feof(source)))
    {
        if (ch == 48)
            child = hft[size].lchild;
        else
            child = hft[size].rchild;
        while (child)
        {
            //printf("解码前的ch是%c",ch);
            if ((hft[child].lchild == 0) && (hft[child].rchild) == 0)     
            {
                i = child;
                break;
            }                     //leaf node
            ch = getc(source);
            if (ch == 48)
                child = hft[child].lchild;
            else
                child = hft[child].rchild;
        }
        putc(hft[i].elem, destination);
        //printf("已解码%d 个字符\n",++count);
        ch = getc(source);
        if (count == 10000)
        {
                //printf("现在的ch是%c\n",ch);
                break;
        }
    }
}
#endif
