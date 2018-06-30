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
int cmp(ElemType a,ElemType b);

//比较两个元素的指数，-1：a<b 0：a=b 1：a>b
int cmp(ElemType a,ElemType b){
    if (a.expn<b.expn) {
        return -1;
    }else if(a.expn>b.expn){
        return 1;
    }else{
        return 0;
    }
}

//多项式相加
void addPolyn(Polynomial *pa, Polynomial *pb){
    Node *ha = pa;
    Node *hb = pb;
    Node *qa = pa->next;
    Node *qb = pb->next;
    while (qa&&qb) {
        ElemType a = qa->elem;
        ElemType b = qb->elem;
        float sum;
        switch (cmp(a, b)) {
            case -1:
                ha = qa;
                qa = qa->next;
                break;
            case 0:
                sum = a.coef+b.coef;
                if (sum!=0.0) {
                    qa->elem.coef = sum;
                    ha = qa;
                }else{
                    //系数为0，这一项消除掉，删除多项式pa中的当前节点
                    ha->next = qa->next;
                    free(qa);
                }
                //删除pb中的第一项
                hb->next = qb->next;
                qb = qb->next;
                free(qb);
                break;
            case 1:
                //pa中的当前节点的指数大,pa中插入pb
                ha->next = pb;
                pb->next = pa;
                pa = pb;
                //删除b节点第一个数据
                hb->next = pb->next;
                pb = pb->next;
                free(pb);
                break;
        }
    }
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
