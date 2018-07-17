/*************************************************************************
	> File Name: lstack.c
	> Description: linked stack
    > Author: libo
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 20时51分06秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lstack.h"

STACK *creat_stack() {
    STACK *sk;
    sk = (STACK *)malloc(sizeof(STACK));
    if (NULL == sk) {
        printf("Memory allocation failure.\n");
        exit(-1);
    }
    sk->bottom = (lnode *)malloc(sizeof(lnode));
    if (NULL == sk->bottom) {
        printf("Memory allocation failure.\n");
        exit(-1);
    }
    sk->bottom->val = 0;
    sk->bottom->next = NULL;
    sk->top = sk->bottom;
    sk->size = 0;
    return sk;
}

int size(STACK *s) {
    if (s != NULL) {
        return s->size;
    }
    else {
        return 0;
    }
}

int isEmpty(STACK *s) {
    return s->top == s->bottom ? 1:0;
}

void push(STACK *s, ElemType elem) {
    lnode *p = (lnode *)malloc(sizeof(lnode));
    if (NULL == p) {
        printf("Memory allocation failure.\n");
        exit(-1);
    }
    p->val = elem;
    p->next = s->top;
    s->top = p;
    ++s->size;
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
    --s->size;
    return 0;
}

void dispose_stack(STACK *s) {
    if (NULL == s)
        return;
    
    lnode *p = NULL;
    while (!isEmpty(s)) {
        p = s->top;
        s->top = s->top->next;
        free(p);
        p = NULL;
    }
    free(s);
    s=NULL;
}
