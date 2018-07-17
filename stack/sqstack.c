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
#include "sqstack.h"


#define MAXLEN 10000

STACK *creat_stack(int maxElem) {
    if (maxElem > MAXLEN) {
        printf("The size of stack is limited to %d\n", MAXLEN);
        return NULL;
    }
    STACK *sk;
    sk = (STACK *)malloc(sizeof(STACK));
    sk->size = maxElem;
    sk->array = (ElemType *)malloc(sizeof(ElemType)*maxElem);
    sk->top = EmptyTOP;    //初始化为-1
    return sk;
}

int isEmpty(STACK *sk) {
    return sk->top == EmptyTOP ? 1:0;
}

int isFull(STACK *sk) {
    return sk->top == sk->size - 1 ? 1:0;
}

void push(STACK *sk, ElemType elem) {
    if (isFull(sk)) {
        int ret = expand_stack(sk);
        if (-1 == ret) {
            printf("The stack is full\n");
            return;
        }
    }
    sk->top++;  //栈顶加1
    sk->array[sk->top] = elem;
}

ElemType pop(STACK *sk) {
    if (isEmpty(sk)) {
        printf("The stack is empty\n");
        return 0;
    }
    ElemType ret = sk->array[sk->top];
    sk->top--;
    return ret;
}

void clear(STACK *sk) {
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
    if (sk->size >= MAXLEN) {
        printf("The size of stack is limited to %d\n", MAXLEN);
        ret = -1;
    }
    else {
        int size = sk->size + 100;
        if (size > MAXLEN) {
            size = MAXLEN;
        }

        ElemType *data = (ElemType *)malloc(sizeof(ElemType)*size);
        memcpy(data, sk->array, sk->size * sizeof(ElemType));
        free(sk->array);
        sk->array = data;
        sk->size = size;
    }
    return ret;
}

int stack_size(STACK *sk) {
    return sk->top+1;
}
