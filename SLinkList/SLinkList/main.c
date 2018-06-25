//
//  main.c
//  静态单链表
//
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
typedef struct Node {
    ElemType data;
    int cur;
} Node;
typedef struct SLinkList {
    Node elem[MAXSIZE];
} SLinkList;

SLinkList initSpaceSL(void);
int mallocSL(SLinkList *l);
void freeSL(SLinkList l, int k);
SLinkList difference(void);
Status listInsert(SLinkList *l,int i,ElemType e);
void printList(SLinkList l);
SLinkList createSlinkList(int num);
Status listDelete(SLinkList *l,int i);
int getPrevFromIndex(SLinkList l,int i);
int getIndexByElem(SLinkList l,ElemType e,int *i);

//通过元素获取数组下标（若有相同的则返回第一个），如果获取不到则返回0
int getIndexByElem(SLinkList l,ElemType e,int *i){
    int index = MAXSIZE - 1;//首次index指向头结点index
    *i = 0;
    do{
        (*i)++;
        index = l.elem[index].cur;
        if (e == l.elem[index].data) {
            printf("k元素的值是：%d\n",*i);
            return index;
        }
    }while (index);
    printf("k元素的值是：%d\n",*i);
    return 0;
}

//获取静态链表第i个元素的前一个元素的数组下标
int getPrevFromIndex(SLinkList l,int i){
    int index = MAXSIZE - 1;
    for (int j = 0; j < i - 1; j++) {
        index = l.elem[index].cur;
    }
    return index;
}

//静态链表删除操作
Status listDelete(SLinkList *l,int i){
    //找到要删除节点的前一个结点
    int prevIndex = getPrevFromIndex(*l, i);
    //要删除的节点
    Node deleteNode = l->elem[prevIndex+1];
    deleteNode.data = 0;//重置删除节点数据
    
    //要删除的节点的前一个结点的下一个指向  指向到删除节点的下一个节点
    l->elem[prevIndex].cur = deleteNode.cur;
    deleteNode.cur = 0;//删除节点的下一个节点重置为0
    return OK;
}

//创建拥有num个元素的静态链表
SLinkList createSlinkList(int num){
    SLinkList list = initSpaceSL();
    int index = MAXSIZE - 1;//index 首次指向头结点，及数组尾部
    for (int i = 0; i < num; i++) {
        //获取空闲分量下标
        int m = mallocSL(&list);
        //给空闲分量赋值
        printf("请输入第%d个元素：\n",i+1);
        scanf("%d",&(list.elem[m].data));
        list.elem[m].cur = 0;//新的节点的下一节点为空
        list.elem[index].cur = m;//尾节点指向新建的节点
        index = m;//尾结点重置一下
    }
    return list;
}

//打印静态链表
void printList(SLinkList l){
    int pos = l.elem[MAXSIZE - 1].cur;
    while (pos) {
        printf("%d ",l.elem[pos].data);
        pos = l.elem[pos].cur;
    }
    printf("\n");
}

//在静态链表l中的第i个元素之前插入元素e
Status listInsert(SLinkList *l,int i,ElemType e){
    if (i<1||i>MAXSIZE+1) {
        printf("输入的i不合法\n");
        return ERROR;
    }
    int h = MAXSIZE - 1; //最后一个元素相当于头结点
    //获取空闲分量
    int j = mallocSL(l);
    if (j) {
        l->elem[j].data = e;
        //找到第i个元素之前的位置
        int pos = h;
        for (int k = 0; k < i - 1; k++) {
            pos = l->elem[pos].cur;
        }
        l->elem[j].cur = l->elem[pos].cur;
        l->elem[pos].cur = j;
        return OK;
    }else{
        printf("静态链表空间不足！\n");
        return ERROR;
    }
}

//以此输入集合A和B的元素，在一维数组中建立表示集合(A-B)U(B-A)的静态链表
SLinkList difference(void){
    //输入A和B的元素个数
    int m,n;
    printf("请输入A集合个数：\n");
    scanf("%d",&m);
    printf("请输入B集合个数：\n");
    scanf("%d",&n);
    //建立集合A的链表
    SLinkList list = createSlinkList(m);
    
    //依次输入B的元素，若不在当前表中，则插入，否则删除
    for (int i = 0; i < n; i++) {
        ElemType e;
        printf("请输入B集合的第%d个元素\n",i+1);
        scanf("%d",&e);
        
        //查找集合中是否有元素e
        int k;
        int index = getIndexByElem(list, e, &k);
        if (index == 0) {
            //集合A中不存在e，插入集合A中(简单起见，插入到第一个位置)
            listInsert(&list, 1, e);
        }else {
            //集合A中存在e，从集合A中删除
            listDelete(&list, k);
        }
        printList(list);
    }
    return list;
}

//将下标为k的空闲结点回收到备用链表
void freeSL(SLinkList l,int k){
    Node *nodes = l.elem;
    nodes[k].cur = nodes[0].cur;
    nodes[0].cur = k;
}

//若备用空间链表非空，则返回分配的节点下标，否则返回0
int mallocSL(SLinkList *l){
    int i = l->elem[0].cur;
    if (i) {
        l->elem[0].cur = l->elem[i].cur;
    }
    return i;
}

//生成一维数组备用链表，nodes[0]为头指针
SLinkList initSpaceSL() {
    SLinkList slinkList;
    Node *nodes = slinkList.elem;
    for (int i = 0; i < MAXSIZE - 1; i++) {
        nodes[i].cur = i + 1;
    }
    nodes[MAXSIZE - 1].cur = 0;
    return slinkList;
}

int main(int argc, const char * argv[]) {
////    difference();
////    SLinkList l = initSpaceSL();
////    listInsert(&l,1,3);
////    listInsert(&l, 1, 4);
////    listInsert(&l, 1, 1);
////    printList(l);
//    int m,n;
//    printf("请输入集合A的个数\n");
//    scanf("%d",&m);
//    SLinkList listA = createSlinkList(m);
////
//////    printf("请输入集合B的个数\n");
//////    scanf("%d",&n);
//////    SLinkList listB = createSlinkList(n);
////
//    printf("集合A：");
//    printList(listA);
//////    printf("集合B：");
//////    printList(listB);
////
////    listDelete(&listA, 2);
////    printList(listA);
////    difference();
////    int index = getIndexByElem(listA, 3);
////    printf("%d",index);
    SLinkList list = difference();
    printList(list);
    return 0;
}
