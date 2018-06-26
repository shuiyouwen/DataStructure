//
//  main.c
//  Polynomial
//  一元多项式
//  Created by Shuiyouwen on 2018/6/25.
//  Copyright © 2018年 Shuiyouwen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000

typedef int Status;
typedef struct ElemType {
    float coef;//系数
    int expn;//指数
} Term, ElemType;
typedef struct Node {
    ElemType elem;
    struct Node *next;
} Node, LinkList, Polynomial;

Polynomial * createPolyn(int m);
Status initPolyn(Polynomial *p);
void printPolyn(Polynomial *p);
void addPolyn(Polynomial *pa, Polynomial *pb);

//多项式相加
void addPolyn(Polynomial *pa, Polynomial *pb){
    
}

//打印一元多项式
void printPolyn(Polynomial *p){
    printf("P(x) = ");
    
    Node *q = p;
    while (q->next) {
        q = q->next;
        if (q) {
            if (q!=p->next) {
                printf("+ ");
            }
            printf("%fx^%d ",q->elem.coef, q->elem.expn);
        }
    }
    printf("\n");
}

//初始化一个一元多项式
Status initPolyn(Polynomial *p){
    p = (Polynomial *)malloc(sizeof(Node));
    if (p) {
        return OK;
    }else{
        return ERROR;
    }
}

//根据输入创建一元多项式
Polynomial * createPolyn(int m){
    Polynomial *p = (Polynomial *)malloc(sizeof(Node));
    Node *q = p;//首次指向头结点
    //依次输入m个非0项
    for (int i = 0; i < m; i++) {
        //动态申请新的节点
        Node *node = (Node *)malloc(sizeof(Node));
        q->next = node;
        q = node;
        
        printf("请输入第%d个元素的系数\n",i+1);
        scanf("%f",&(node->elem.coef));
        printf("请输入第%d个元素的指数\n",i+1);
        scanf("%d",&(node->elem.expn));
    }
    return p;
}

int main(int argc, const char * argv[]) {
    Polynomial *p = createPolyn(3);
    printPolyn(p);
    return 0;
}
