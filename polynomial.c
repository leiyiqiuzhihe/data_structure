//polynomial.c -- 链表保存多项式，多项式的四则运算
//这里的链表是有头节点的，头节点不是首元结点
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"polynomial.h"

int main(void)
{
    PList poly1,poly2;
    PNode *n1, *n2;
    char ch;

    poly1 = my_create_poly();
    if (poly1)
    {
        printf("poly1:\n");
        printf("请输入节点信息，q to quit\n");
        while ((ch = getchar()) != 'q')
        {
            ungetc(ch,stdin);
            n1 = create_init_node();
            get_input(n1);
            insert_node(poly1,n1);
            printf("请输入下一个节点信息，q to quit\n");
        }
        printf("Done poly1\n\n");
    }

    while (getchar() != '\n')
         continue;

    poly2 = my_create_poly();
    if (poly2)
    {
        printf("poly2:\n");
        printf("请输入节点信息，q to quit\n");
        while ((ch = getchar()) != 'q')
        {
            ungetc(ch,stdin);
            n2 = create_init_node();
            get_input(n2);
            insert_node(poly2,n2);
            printf("请输入下一个节点信息，q to quit\n");
        }
        printf("Done poly2\n\n");
    }

    add_poly(poly1, poly2);
    printf("\nDone add\n\n");
    show(poly1);

    free(poly1);

	return 0;
}


PNode *create_init_node(void)            //creat and initialize a PNode
{
    PNode *ptn = NULL;
	ptn = malloc(sizeof(PNode));
    if (!ptn)
    {
        printf("malloc error.\n");
        exit(1);
    }
	ptn->coef = 0;
	ptn->x_expo = 0;
	ptn->y_expo = 0;
	ptn->next = NULL;
	
	return ptn;
}

PList my_create_poly(void)                   //新建一个链表，有头结点
{
    PList poly = NULL;
    PNode *head_node = NULL;

    head_node = create_init_node();
    if (head_node)
        poly = head_node;

    return poly;
}


void get_input(PNode *ptn)
{
    const double EPS = 1e-6;

    printf("请输入该项的系数（非零double） x的指数  y的指数：\n");
    while ((scanf("%lf",&ptn->coef)) == 1)
    {
         if (fabs(ptn->coef-0) < EPS)
         {
             printf("系数不能为零\n");
             while (getchar() != '\n')
                 continue;
             printf("请输入该项的系数（非零double） x的指数  y的指数：\n");
             continue;
         }
         if (scanf("%d %d",&ptn->x_expo, &ptn->y_expo) == 2)
         {
             while (getchar() != '\n')
                 continue;
             break;                  //读取成功跳出循环
         }
         else
         {
             printf("请输入正确地数据格式\n");
             printf("请输入该项的系数（非零double） x的指数  y的指数：\n");
             continue;
         }
    }
}

int insert_node(PList poly, PNode *ptn)
{
	PNode *current = poly->next;
	PNode *prior = current;

	if (ptn->coef == 0)
    {
        printf("系数不能为零\n");
        return 0;
    }
    if (poly->next == NULL)      //如果是空链，把节点直接插入
    {
        poly->next = ptn;
        return 1;
    }

    while (1)           //如果不是空链逐个节点比较，分三种情况寻找
    {
/*        if (current->next == NULL)     //到达链尾
        {
            current->next = ptn;
            break;
        }
*/        
        if (ptn->x_expo < current->x_expo)
        {
            prior->next = ptn;
            ptn->next = current;
            break;
        }
        else if (ptn->x_expo > current->x_expo)
        {
            if (current->next == NULL)     //到达链尾
            {
                current->next = ptn;
                break;
            }
            else
            {
                prior = current;
                current = current->next;
                continue;
            }
        }
        else         //ptn->x_expo == current->expo
        {
             if (ptn->y_expo > current->y_expo)   //不能用while
             {
                 if (current->next == NULL)     //到达链尾
                 {
                     current->next = ptn;
                     break;
                 }
                 else
                 {
                    prior = current;
                    current = current->next;
                    continue;
                 }
             }
             else if (ptn->y_expo < current->y_expo)
             {
                prior->next = ptn;         //如果ptn->y_expo < current->y_expo
                ptn->next = current;
                break;
             }
             else                     //如果ptn->y_expo == current->y_expo则合并多项式free
             {
                current->coef += ptn->coef;
                free(ptn);
                break;
             }
        }
    }

	return 1;
}


size_t get_length(PList poly)
{
	PNode *p;
	size_t len = 0;

	p = poly->next;
	while((p = p->next))
	   len++;
	return len;
}


PList add_poly(PList poly1, PList poly2)
{
    //PNode *current_node_p1;
    PNode *current_node_p2;

    if (poly2->next == NULL)
    {
        printf("Poly2 is empty\n");
        return poly1;
    }
    current_node_p2 = poly2->next;
    while (current_node_p2)
    {
        insert_node(poly1,current_node_p2);
        current_node_p2 = current_node_p2->next;
    }

    if (!current_node_p2)
    {
        free(poly2);
    }

    return poly1;
}



void show(PList poly)
{
    PNode * current;

    if (poly->next == NULL)
    {
        printf("an empty polynomial you want to show\n");
        return;
    }

    current = poly->next;
    while (current)
    {
        printf("%.2fx^%dy^%d",current->coef, current->x_expo, current->y_expo);
        if (current->next)
        {
            printf(" + ");
        }
        else
        {
            printf("\n");
        }
        current = current->next;
    }
}
