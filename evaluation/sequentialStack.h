/*************************************************************************
	> File Name: sequentialStack.h
	> Description: linear stack
    > Author: libo
	> Mail: seereeves@163.com 
	> Created Time: 09/07/2018 - 15:47
 ************************************************************************/

#ifndef SQSTACK_H_
#define SQSTACK_H_

#define EmptyTOP -1

typedef struct stack {
    int free;              //栈的剩余空间大小,栈总的空间为free+top+1
    int top;               //栈顶,指向栈顶元素的index（0- ）
    size_t size;           //栈内元素的宽度
    void *array;           //存放数据的数组
} STACK;
/*
 * 创建一个空栈
 * */
STACK *create_stack(int len, size_t size);

/*
 * 判空
 * */
int isEmpty(STACK *s);

/*
 * 判满
 * */
int isFull(STACK *s);

/*
 * 赋值操作
 * */
void *assign_value(void *dest, const void *val, size_t size);

/*
 * 入栈
 * */
void push(STACK *s, void *val, size_t size);

/*
 * 出栈
 * */
void *pop(STACK *s);

/*
 * 获取栈顶元素
 * */
void *stack_top(STACK *s);

/*
 * 清空栈的内容
 * */
void clear(STACK *sk);

/*
 * 释放一个栈
 * */
void dispose_stack(STACK *s);

/*
 * 扩展顺序栈的大小
 * */
int expand_stack(STACK *s);

/*
 * 获取栈的大小
 * */
int stack_size(STACK *s);

#endif
