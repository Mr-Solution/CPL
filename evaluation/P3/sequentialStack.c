/*************************************************************************
    > File Name: sequentialStack.c
    > Author: libo
    > Mail: seereeves@163.com 
    > Created Time: 30/07/2018 - 18:55
 ************************************************************************/

#include "sequentialStack.h"

#define StackLen(s) s->top+1
// test of validity, without return value
#define CHECKPOINTERVOID(pointer) do { \
    if (NULL==pointer) {\
        printf("err! illegal parameter, the pointer is NULL.\n"); \
        return ; \
    } \
} while(0);

// test of validity
#define CHECKPOINTER(pointer) do { \
    if (NULL==pointer) {\
        printf("err! illegal parameter, the pointer is NULL.\n"); \
        return 0; \
    } \
} while(0);

void InitStack(SqStack *s) {
    CHECKPOINTERVOID(s);
    s->top = -1;
}

/*  Release the memory of the sequential stack
 */
void DestroyStack(SqStack *s) {
    CHECKPOINTERVOID(s);
    s->top = -1;
    free(s);
    //s = NULL;
}

/*  Check if the stack is empty.
    Return 1 to indicate the stack is empty.
    Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty(SqStack *s) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        //printf("The stack is empty.\n");
        return 1;
    }
    else {
        return 0;
    }
}

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push(SqStack *s, ElemType e) {
    CHECKPOINTER(s);
    if (StackLen(s) >= MaxSize) {
        /* stack is full */
        printf("The stack is FULL.\n");
        return 0;
    }
    else {
        /* stack is not full */
        s->top++;
        s->data[s->top] = e;
        return 1;
    }
}

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop(SqStack *s, ElemType *e) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        /* stack is empty */
        printf("The stack is empty.\n");
        return 0;
    }
    else {
        /* stack is NOT empty */
        *e = s->data[s->top];
        s->top--;
        return 1;
    }
}

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop(SqStack *s, ElemType *e) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        /* stack is empty */
        return 0;
    }
    else {
        /* stack is NOT empty */
        *e = s->data[s->top];
        return 1;
    }
}

void display(SqStack *s) {
    CHECKPOINTERVOID(s);
    int cur_len = StackLen(s);
    for (int i=0; i<cur_len; ++i) {
        printf("%c\n", s->data[i]);
    }
}

/* Interfaces for the 2nd stack for double elements*/

/*  Initialize the sequential stack
 */
void InitStack1(SqStack1 *s) {
    CHECKPOINTERVOID(s);
    s->top = -1;
}

/*  Release the memory of the sequential stack
 */
void DestroyStack1(SqStack1 *s) {
    CHECKPOINTERVOID(s);
    free(s);
}

/*  Check if the stack is empty.
 Return 1 to indicate the stack is empty.
 Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty1(SqStack1 *s) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        //printf("The stack is empty.\n");
        return 1;
    }
    else {
        return 0;
    }
}

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push1(SqStack1 *s, ElemType1 e) {
    CHECKPOINTER(s);
    if (StackLen(s) >= MaxSize) {
        /* stack is full */
        printf("The stack is FULL.\n");
        return 0;
    }
    else {
        /* stack is not full */
        s->top++;
        s->data[s->top] = e;
        return 1;
    }
}

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop1(SqStack1 *s,ElemType1 *e) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        /* stack is empty */
        printf("The stack is empty.\n");
        return 0;
    }
    else {
        /* stack is NOT empty */
        *e = s->data[s->top];
        s->top--;
        return 1;
    }
}

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop1(SqStack1 *s,ElemType1 *e) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        /* stack is empty */
        return 0;
    }
    else {
        /* stack is NOT empty */
        *e = s->data[s->top];
        return 1;
    }
}