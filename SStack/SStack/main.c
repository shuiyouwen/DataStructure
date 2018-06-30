//
//  main.c
//  SStack
//  顺序栈
//  Created by Shuiyouwen on 2018/6/30.
//  Copyright © 2018年 Shuiyouwen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000

const int STACK_INIT_SIZE = 100;

typedef int Status;
typedef int SElemType;
typedef struct SqStack {
    SElemType *base;//栈底指针
    SElemType *top;//栈顶指针
    int stacksize;//当前可使用的最大容量
} SqStack;

Status initStack(SqStack *s);
Status destroyStack(SqStack *s);
Status clearStack(SqStack *s);
Status stackEmpty(SqStack s);
int stackLength(SqStack s);
SElemType getTop(SqStack s);
//插入元素e为新的栈顶元素
Status push(SqStack *s,SElemType e);
//删除栈顶元素，并用e返回值
SElemType pop(SqStack *s);
//遍历栈中元素
Status stackTraverse(SqStack s,Status(*visit)(SElemType));

Status initStack(SqStack *s) {
    s->base = (SElemType *)malloc(sizeof(SElemType)*STACK_INIT_SIZE);
    if (!s) {
        exit(-1);
    }
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
    return OK;
}

//插入元素e为新的栈顶元素
Status push(SqStack *s,SElemType e) {
    if (s->top-s->base > s->stacksize) {
        s->base = (SElemType *)realloc(s->base, s->stacksize+STACK_INIT_SIZE*sizeof(SElemType));
        if (!s->base) {
            exit(-1);
        }
    }
    
    *(s->top++) = e;
    return OK;
}

//遍历栈中元素
Status stackTraverse(SqStack s,Status(*visit)(SElemType)) {
    SElemType *b = s.base;
    SElemType *t = s.top;
    while (t>b) {
        visit(*b++);
    }
    printf("\n");
    return OK;
}

//删除栈顶元素，并用e返回值
SElemType pop(SqStack *s) {
    SElemType e;
    if (s->top == s->base) {
        exit(-1);
    }else {
        e = * --s->top;
    }
    return e;
}

Status visit(SElemType e) {
    printf("%d ",e);
    return OK;
}

//若栈不空，则用e返回s的栈顶元素，并返回ok，否则返回error
SElemType getTop(SqStack s) {
    if (s.top == s.base) {
        return ERROR;
    }
    
    return *(s.top-1);
    return OK;
}

Status destroyStack(SqStack *s) {
    free(s->base);
    s->top = NULL;
    s->base = NULL;
    s->stacksize = 0;
    return OK;
}

Status clearStack(SqStack *s) {
    s->top = s->base;
    return OK;
}

Status stackEmpty(SqStack s) {
    return s.top == s.base;
}

int stackLength(SqStack s) {
    return s.top - s.base;
}

int main(int argc, const char * argv[]) {
    SqStack s;
    initStack(&s);
    push(&s, 10);
    push(&s, 2);
    push(&s, 3);
    push(&s, 10);
    push(&s, 2);
    push(&s, 3);
    push(&s, 10);
    push(&s, 2);
    push(&s, 3);
    stackTraverse(s, visit);
    SElemType top;
    top =  getTop(s);
    printf("%d\n",top);
    SElemType p = pop(&s);
    printf("pop:%d\n",p);
    stackTraverse(s, visit);
    printf("长度：%d\n",stackLength(s));
    return 0;
}
