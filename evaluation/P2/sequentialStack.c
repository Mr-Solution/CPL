/*************************************************************************
	> File Name: sqstack.c
    > Description: linear stack
    > Author: libo
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 16时19分58秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequentialStack.h"

#define MAXLEN 10000

/* len: 初始化数组长度  size: 数据类型的宽度sizeof
 * */
STACK *create_stack(int len, size_t size) {
    if (len > MAXLEN) {
        printf("The size of stack is limited to %d\n", MAXLEN);
        return NULL;
    }
    STACK *sk = (STACK *)malloc(sizeof(STACK));
    sk->free = len;
    sk->top = EmptyTOP;    //初始化为-1
    sk->size = size;
    sk->array = (void *)malloc(size*len);  //可以存放len个长度为size的数据
    return sk;
}

int isEmpty(STACK *sk) {
    return sk->top == EmptyTOP ? 1:0;
}

int isFull(STACK *sk) {
    return 0 == sk->free ? 1:0;
}

void *assign_value(void *dest, const void *val, size_t size) {
    memcpy(dest, val, size);
    return dest;
}

void push(STACK *sk, void *val) {
    if (isFull(sk)) {
        int ret = expand_stack(sk);
        if (-1 == ret) {
            printf("The stack is full\n");
            return;
        }
    }
    sk->top++;  //栈顶加1
    sk->free--;
    assign_value(sk->array + (sk->top * sk->size), val, sk->size);
}

void *pop(STACK *sk/*, size_t *size*/) {
    if (isEmpty(sk)) {
        printf("The stack is empty\n");
        return NULL;
    }
  //  *size = sk->size;
    sk->top--;
    sk->free++;
    return sk->array+(sk->top+1)*sk->size;
}

void *stack_top(STACK *sk) {
    return sk->array+(sk->top)*(sk->size);
}

void clear(STACK *sk) {
    sk->free += sk->top + 1;
    sk->top = EmptyTOP;
}

void dispose_stack(STACK *sk) {
    if (sk != NULL) {
        free(sk->array);
        sk->array = NULL;
        free(sk);
        sk = NULL;
    }
}

// 默认每次扩展100个空间
int expand_stack(STACK *sk) {
    int ret = 0;
    int current_len = sk->top + 1;
    if (current_len >= MAXLEN) {
        printf("The size of stack is limited to %d\n", MAXLEN);
        ret = -1;
    }
    else {
        int new_len = current_len+100 > MAXLEN ? MAXLEN : current_len+100;
        void *data = (void *)malloc(sk->size*new_len);
        memcpy(data, sk->array, current_len * sk->size);
        free(sk->array);
        sk->array = data;
        sk->free = new_len - current_len;
    }
    return ret;
}

int stack_size(STACK *sk) {
    return sk->top+1;
}
