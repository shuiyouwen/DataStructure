//
//  main.c
//  DuLinkList
//  双向链表
//  Created by Shuiyouwen on 2018/6/24.
//  Copyright © 2018年 Shuiyouwen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000

typedef int ElemType;
typedef int Status;
typedef struct DuLNode {
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, DuLinkList;

Status listInsert(DuLinkList *l,int i,ElemType e);
void printList(DuLinkList l);
Status listDelete(DuLinkList *l,int i);
DuLNode* getElem(DuLinkList *l,int i);
Status listInit(DuLinkList *l);

//初始化双向链表
Status listInit(DuLinkList *l){
    l = (DuLinkList *)malloc(sizeof(DuLNode));
    if (l) {
        return OK;
    }else{
        return ERROR;
    }
}

//获取插入位置，返回i的前一个结点
DuLNode* getElem(DuLinkList *l,int i){
    int j = 1;
    DuLinkList *p = l;
    while (j < i) {
        p = p->next;
        j++;
        
        if (!p) {
            printf("输入不合法！\n");
            exit(-1);
        }
    }
    return p;
}

Status listDelete(DuLinkList *l,int i){
    DuLNode *p = getElem(l, i);
    DuLNode *deleteNode = p->next;//待删除结点
    DuLNode *nextNode = deleteNode->next;//待删除结点的下一个结点
    p->next = nextNode;
    nextNode->prior = p;
    
    free(deleteNode);
    return OK;
}

Status listInsert(DuLinkList *l,int i,ElemType e){
    DuLNode *p = getElem(l, i);
    //申请一个结点
    DuLNode *s = (DuLNode *)malloc(sizeof(DuLNode));
    if (!s) {
        printf("申请结点内存失败！");
        return ERROR;
    }
    s->data = e;
    s->prior = p;
    s->next = p->next;
    
    p->next = s;
    return OK;
}

void printList(DuLinkList l){
    DuLNode *p = &l;
    while (p) {
        p = p->next;
        if (p) {
            printf("%d ",p->data);
        }
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    DuLinkList list;
    listInit(&list);
    listInsert(&list, 1, 11);
    listInsert(&list, 2, 3);
    listInsert(&list, 1, 1993);
    printList(list);
    listDelete(&list, 2);
    printList(list);
    return 0;
}
