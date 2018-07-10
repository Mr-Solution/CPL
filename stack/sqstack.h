/*************************************************************************
	> File Name: sqstack.h
	> Description: stack sequence
    > Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 15时47分15秒
 ************************************************************************/

#ifndef SQSTACK_H_
#define SQSTACK_H_

#define EmptyTOP -1

typedef int ElemType;  //存储单元的数据类型

typedef struct stack {
    int length;            //当前长度
    int size;              //栈的大小
    int top;               //栈顶指针
    ElemType *array;       //存放数据的数组
} STACK;
/*
 * 创建一个空栈
 * */
STACK *creat_stack(int maxElem);

/*
 * 判空
 * */
int isEmpty(STACK *s);

/*
 * 判满
 * */
int isFull(STACK *s);

/*
 * 入栈
 * */
void push(STACK *s, ElemType elem);

/*
 * 出栈
 * */
ElemType pop(STACK *s);

/*
 * 释放一个栈
 * */
void dispose_stack(STACK *s);

/*
 * 扩展顺序栈的大小为size*sizeof(ElemType)
 * */
int expand_stack(STACK *s);

#endif
