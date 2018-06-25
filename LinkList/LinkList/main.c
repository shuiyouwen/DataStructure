//
//  main.c
//  LinkList 动态单链表
//
//  Created by Shuiyouwen on 2018/6/21.
//  Copyright © 2018年 Shuiyouwen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode ,LinkList;


LinkList createList_L(int n);
void printList_L(LinkList L);
ElemType getElem(LinkList L,int i);
Status listInsert(LinkList L,int i,ElemType e);
Status listDelete(LinkList l,int i);
LinkList mergeList(LinkList l1,LinkList l2);


/**
 已知单链表l1和l2的元素值增排列，归并l1和l2
 !!!!tmd数据咋不对

 @param l1 <#l1 description#>
 @param l2 <#l2 description#>
 @return <#return value description#>
 */
LinkList mergeList(LinkList l1,LinkList l2){
    //用l1作为头结点
    LinkList result = l1;
    LNode *p0 = &result;
    LNode *p1 = l1.next;
    LNode *p2 = l2.next;
    while (p1&&p2) {
        if (p1->data<p2->data) {
            p0->next = p1;
            p0 = p1;
            p1 = p1->next;
        }else {
            p0->next = p2;
            p0 = p2;
            p2 = p2->next;
        }
    }
    p0->next = p1?p1:p2;
//    free(&l2);
    return result;
}

Status listDelete(LinkList l,int i){
    int j = 0;
    LNode *p = &l;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p||j> i - 1) {
        return ERROR;
    }
    LNode *q = p->next;
    p->next = q->next;
    free(q);
    return OK;
}


/**
 在带头结点的单链表L中的第i个位置之前插入元素e

 @param L <#L description#>
 @param i <#i description#>
 @param e <#e description#>
 @return <#return value description#>
 */
Status listInsert(LinkList L,int i,ElemType e){
    LNode *p = &L;
    int j = 0;
    //寻找第i-1个结点
    while (p && j< i - 1) {
        p = p->next;
        j++;
    }
    if (!p||j>i-1) {
        return ERROR;
    }
    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->data = e;
    newNode->next = p->next;
    p->next = newNode;
    return OK;
}

ElemType getElem(LinkList L,int i){
    LNode *p = L.next;
    int j = 1;
    while (p&&j<i) {
        p = p->next;
        j++;
    }
    if (!p||j>i) {
        printf("第i个元素不存在");
        exit(-1);
    }
    return p->data;
}

/**
 头插法（L->3->2->1->NULL）

 @param n n个元素
 */
LinkList createList_L(int n) {
    LNode *L;
    L = (LNode *)malloc(sizeof(LNode));
    if (!L) {
        printf("分配头结点内存失败！");
    }
    L->next = NULL;
    
    ElemType elem;
    for (int i = n; i>0; i--) {
        struct LNode *p = (struct LNode *)malloc(sizeof(struct LNode));
        if (!p) {
            printf("分配数据节点内存失败！");
        }
        printf("请输入数字：\n");
        scanf("%d",&elem);
        p->data = elem;
        
        p->next = L->next;
        L->next = p;
    }
    
    printf("第一个元素是：%d\n",L->next->data);
    return *L;
}


/**
 打印链表

 @param L 链表L
 */
void printList_L(LinkList L) {
    struct LNode *p = &L;
    while ((p = p->next)) {
        printf("%d ",p->data);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
//    LinkList L = createList_L(3);
//    printList_L(L);
//    printf("第二个元素是：%d\n",getElem(L, 2));
//    listInsert(L, 2, 13);
//    printList_L(L);
//    listDelete(L, 3);
//    printList_L(L);
    
    LinkList la = createList_L(3);
    LinkList lb = createList_L(3);
    printList_L(la);
    printList_L(lb);
    mergeList(la, lb);
    printList_L(la);
    return 0;
}
