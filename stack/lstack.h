/*************************************************************************
	> File Name: lstack.h
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 20时42分24秒
 ************************************************************************/

#ifndef LSTACK_H_
#define LSTACK_H_

typedef int ElemType;  //节点数据的类型

typedef struct node {
    ElemType val;
    struct node *next;
} lnode;

typedef struct stack {
    int size;
    int len;
    lnode *top;
    lnode *bottom;
} STACK;

STACK *creat_stack(int maxElem);

int isEmpty(STACK *s);

int isFull(STACK *s);

void push(STACK *s, ElemType elem);

int pop(STACK *s, ElemType *val);

void dispose_stack(STACK *s);

#endif
