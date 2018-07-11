/*************************************************************************
	> File Name: lstack.c
	> Description: linked stack
    > Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 20时51分06秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lstack.h"

#define MAXLEN 1000

STACK *creat_stack(int maxElem) {
    if (maxElem > MAXLEN) {
        printf("The size of stack is limited to %d\n", MAXLEN);
        return NULL;
    }
    STACK *sk;
    sk = (STACK *)malloc(sizeof(STACK));
    sk->size = maxElem;
    sk->len = 0;

    sk->bottom = (lnode *)malloc(sizeof(lnode));
    if (NULL == sk->bottom) {
        printf("Memory allocation failure.\n");
        exit(-1);
    }
    sk->bottom->val = 0;
    sk->bottom->next = NULL;
    sk->top = sk->bottom;
    return sk;
}

int isEmpty(STACK *s) {
    return s->top == s->bottom ? 1:0;
}

int isFull(STACK *s) {
    return s->len == s->size ? 1:0;
}

void push(STACK *s, ElemType elem) {
    if (isFull(s)) {
        printf("The stack is full\n");
    }
    else {
        lnode *p = (lnode *)malloc(sizeof(lnode));
        if (NULL == p) {
            printf("Memory allocation failure.\n");
            exit(-1);
        }
        p->val = elem;
        p->next = s->top;
        s->top = p;
    }
}

int pop(STACK *s, ElemType *val) {
    if (isEmpty(s)) {
        printf("The stack is empty.\n");
        return -1;
    }
    lnode *p = s->top;
    *val = s->top->val;
    s->top = s->top->next;
    free(p);
    p = NULL;
    return 0;
}

void dispose_stack(STACK *s) {
    if (isEmpty(s)) {
        return;
    }
    else {
        lnode *p = NULL;
        while (s->top != s->bottom) {
            p = s->top;
            s->top = s->top->next;
            free(p);
            p = NULL;
        }
    }
}
