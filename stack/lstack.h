/*************************************************************************
	> File Name: lstack.h
	> Description: linked stack
    > Author: libo
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
    int size;       //栈的当前size
    lnode *top;     //栈顶指针
    lnode *bottom;  //栈底指针，数据区的首地址，默认不存放数据，val=0,next=null
} STACK;

STACK *creat_stack();

int size(STACK *s);

int isEmpty(STACK *s);

/*
 * 入栈操作
 * */
void push(STACK *s, ElemType elem);

/*
 * 返回栈顶元素，存放在*val中
 * */
int pop(STACK *s, ElemType *val);

/*
 * 销毁栈
 * */
void dispose_stack(STACK *s);

#endif
