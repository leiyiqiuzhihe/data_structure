#include<stdio.h>

typedef struct stru2{
        int * a1;
        char  ch;
        int * b1;
}stru2;

typedef struct stru3{
        int  a2;
        int  ch;
        int  b2;
}stru3;


typedef struct stru4{
        char ch;
        int * a3;
        int * a4;
}stru4;



int main()
{
    printf("stru2 %zd byte, stru3 %zd byte, stru4 %zd byte\n",sizeof(stru2),sizeof(stru3),sizeof(stru4));
    printf("int %zd bytes, void* %zd bytes\n",sizeof(int),sizeof(void *));
    return 0;
}
