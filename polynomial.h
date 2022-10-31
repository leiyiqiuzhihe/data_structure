//polynomial.h -- 结构声明，函数声明

#include<stdio.h>
#ifndef POLYNOMIAL
#define POLYNOMIAL

typedef struct PNode{ 
	double coef;          //系数
	int x_expo;          //指数
	int y_expo;          //y的指数
	struct PNode *next;
}PNode, *PList;

PList my_create_poly(void);           //新建一个多项式

PNode * create_init_node(void);      //新建并初始化一个节点  节点是动态分配的该怎么回收

void get_input(PNode *ptn);      //从输入获取系数、指数

int insert_node(PList poly, PNode *ptn);     //把节点按升序插入链表

size_t get_length(PList poly);      //获取链表的长度

PList add_poly(PList poly1, PList poly2);   //两个多项式相加

void show(PList poly);         //打印多项式

//PList sub_poly(PList poly1, PList poly2);    //poly1 减 poly2


#endif

