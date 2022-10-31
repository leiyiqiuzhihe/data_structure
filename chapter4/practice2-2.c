//下标的混乱  求nextval的函数，nextval的0 下标被跳过了




#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define SLEN  100
#define TLEN  30

char* s_gets(char *st, int n);
void next_val(char *st, size_t tlen, int **pnext);

int main(void)
{
    int i = 1;
    int j = 1;
    size_t tlength = 0;
    size_t slength = 0;
    char s[SLEN];       //s指向主串
    char t[TLEN];       //t指向子串
    int *nextval;

    printf("请输入主串：\n");
    s_gets(s+1,SLEN-1);
    printf("请输入子串：\n");
    s_gets(t+1,TLEN-1);
    slength = strlen(s+1);
    tlength = strlen(t+1);
    next_val(t,tlength,&nextval);

    while (i <= slength && j <= tlength)
    {
        if (j == 0 || s[i] == t[j])
        {
            i++;
            j++;
        }
        else
            j = nextval[j];
    }

    if (i <= slength)
        printf("第%zd个字符%c\n",i-tlength,s[i-tlength]);
    printf("nextval:\n");
    for (i = 1; i <= tlength; i++)
    {
        printf("%4d",*(nextval+i));
    }
    putc('\n',stdout);

    return 0;
}

char* s_gets(char *st, int n)
{
    char *ret_val = NULL;
    char *find = NULL;

    if ((ret_val = fgets(st,n,stdin)))
    {
        if ((find = strchr(st,'\n')))
            *find = '\0';
        else
            while ((getchar() != '\n'))
                continue;
    }

    return ret_val;
}



void next_val(char *st, size_t tlen, int **pnext)
{
    int i = 1;
    int j = 0;

    if (!(*pnext = (int *)malloc(tlen * sizeof(int))))
    {
        perror("pnext malloc failed");
        return;
    }
    *(*pnext + 1) = 0;

    while (i < tlen)
    {
        if (j == 0 || *(st + i) == *(st + j))
        {
            printf("       %d *(st+i): %c\n",i,*(st+i));
            j++;
            i++;
            if (*(st+i) != *(st+j))
                (*pnext)[i] = j;
            else
                (*pnext)[i]  = (*pnext)[j];
        }
        else
            j = *(*pnext + j);
        printf("%d *(st+i): %c\n",j,*(st+i));
    }

}
