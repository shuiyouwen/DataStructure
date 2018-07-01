//
//  main.c
//  LinkStack
//  链式栈
//  Created by Shuiyouwen on 2018/6/30.
//  Copyright © 2018年 Shuiyouwen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;
typedef struct Node {
    ElemType elem;
    struct Node *next;
} LinkStack, Node;

Status initStack(LinkStack *s);
Status destroyStack(LinkStack *s);
Status clearStack(LinkStack *s);
Status stackEmpty(LinkStack s);
int stackLength(LinkStack s);
ElemType getTop(LinkStack *s);
//插入元素e为新的栈顶元素
Status push(LinkStack *s,ElemType e);
//删除栈顶元素，并用e返回值
ElemType pop(LinkStack *s);
//遍历栈中元素
Status stackTraverse(LinkStack s,Status(*visit)(Node));
Status visit(Node n);
void conversion(void);
//括号匹配的校验
void bracket(void);
LinkStack *getStack(void);
void bracket2(void);
void lineEdite(void);

//获取链栈
LinkStack *getStack() {
    LinkStack *s;
    s = (Node *)malloc(sizeof(ElemType));
    if (!s) {
        exit(-1);
    }
    s->elem = 0;
    s->next = NULL;
    return s;
}

Status initStack(LinkStack *s) {
    s = (Node *)malloc(sizeof(ElemType));
    if (!s) {
        exit(-1);
    }
    s->elem = 0;
    s->next = NULL;
    return OK;
}

Status visit(Node n) {
    printf("%d ", n.elem);
    return OK;
}

Status stackTraverse(LinkStack s,Status(*visit)(Node)) {
    Node *p = s.next;
    while (p) {
        visit(*p);
        p = p->next;
    }
    printf("\n");
    return OK;
}

ElemType getTop(LinkStack *s) {
    if (!s->next) {
        exit(-1);
    }
    return s->next->elem;
}

//插入元素e为新的栈顶元素
Status push(LinkStack *s,ElemType e) {
    //申请新结点内存
    Node *q = (Node *)malloc(sizeof(Node));
    if (!q) {
        exit(-1);
    }
    q->elem = e;
    //把新结点插入到第一个位置
    Node *p = s->next;
    s->next = q;
    q->next = p;
    return OK;
}

Status destroyStack(LinkStack *s) {
    Node *p = s->next;
    while (p) {
        s->next = p->next;
        free(p);
        p = s->next;
    }
    return OK;
}

ElemType pop(LinkStack *s) {
    Node *p = s->next;
    ElemType e = p->elem;
    s->next = p->next;
    free(p);
    return e;
}

Status stackEmpty(LinkStack s) {
    if (!s.next) {
        return TRUE;
    }else {
        return FALSE;
    }
}

//数值转换demo，10进制转8进制
void conversion(void) {
    LinkStack result;
    initStack(&result);
    int num = 1348;
    int div;
    int mod;
    while (TRUE) {
        div = num / 8;
        mod = num % 8;
        num = div;
        push(&result, mod);
        
        if (div == 0) {
            break;
        }
    }
    
    //输出结果
    Node *p = result.next;
    while (!stackEmpty(result)) {
        printf("%d ",pop(&result));
        p = result.next;
    }
    printf("\n");
}

//括号匹配的校验
void bracket(void) {
    char source[] = "[([][])]";
    //s1记录中括号，s2记录大括号
//    LinkStack *s1 = getStack();
//    LinkStack *s2 = getStack();
    LinkStack *s1;
    initStack(s1);
    push(s1, 1);
    push(s1, 2);
    push(s1, 3);
//    for (int i = 0; i <= 50; i++) {
//        char c = source[i];
//        if (c == '[') {
//            push(s1, i);
//        }else if (c == '(') {
//            push(s2, i);
//        }
//        if (!c) {
//            break;
//        }
//    }
    stackTraverse(*s1, visit);
//    stackTraverse(*s2, visit);
}

void bracket2(void) {
    char source[] = "[([][)]]";
    LinkStack *s1 = getStack();
    LinkStack *s2 = getStack();
    for (int i = 0; i < strlen(source); i++) {
        switch (source[i]) {
            case '[':
                push(s1, i);
                break;
            case ']':
                pop(s1);
                break;
            case '(':
                push(s2, i);
                break;
            case ')':
                pop(s2);
                break;
        }
    }
    if (stackEmpty(*s1)&&stackEmpty(*s2)) {
        printf("格式正确\n");
    }else {
        printf("格式有误!\n");
        if (!stackEmpty(*s1)) {
            printf("中括号：");
            stackTraverse(*s1, visit);
        }
        if (!stackEmpty(*s2)) {
            printf("小括号：");
            stackTraverse(*s2, visit);
        }
    }
}

//行编辑程序
void lineEdite(void) {
   
}

int main(int argc, const char * argv[]) {
//    LinkStack s;
//    initStack(&s);
//    push(&s, 10);
//    push(&s, 12);
//    push(&s, 1);
//    push(&s, 3);
//    push(&s, 9);
//    stackTraverse(s, visit);
//    printf("%d\n",getTop(&s));
//    pop(&s);
//    stackTraverse(s,visit);
//    destroyStack(&s);
//    conversion();
    lineEdite();
    return 0;
}
