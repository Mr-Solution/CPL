/*************************************************************************
    > File Name: sequentialStack.c
    > Author: libo
    > Mail: seereeves@163.com 
    > Created Time: 30/07/2018 - 18:55
 ************************************************************************/

#include "sequentialStack.h"

#define StackLen(s) s->top+1
/* test of validity, without return value */
#define CHECKPOINTERVOID(pointer) do { \
    if (NULL==pointer) {\
        printf("err! illegal parameter, the pointer is NULL.\n"); \
        return ; \
    } \
} while(0)
/* test of validity */
#define CHECKPOINTER(pointer) do { \
    if (NULL==pointer) {\
        printf("err! illegal parameter, the pointer is NULL.\n"); \
        return FAILED; \
    } \
} while(0)

State InitStack(SequentialStackChar *s) {
    CHECKPOINTER(s);
    s->top = -1;
    return SUCCEEDED;
}

/*  Release the memory of the sequential stack
 */
void DestroyStack(SequentialStackChar *s) {
    CHECKPOINTERVOID(s);
    s->top = -1;
    free(s);
}

/*  Check if the stack is empty.
 *  Return SUCCEEDED to indicate the stack is empty.
 *  Return FAILED to indicate the stack is NOT empty.
 */
State StackEmpty(SequentialStackChar *s) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        return SUCCEEDED;
    }
    else {
        return FAILED;
    }
}

/*  If the stack is NOT full, push e into it and return SUCCEEDED to indicate a successful push.
 *  If the stack is full, merely return FAILED to indicate an unsuccessful push.
 */
State Push(SequentialStackChar *s, ElemType e) {
    CHECKPOINTER(s);
    if (StackLen(s) >= MaxSize) {
        /* stack is full */
        printf("The stack is FULL.\n");
        return FAILED;
    }
    else {
        /* stack is not full */
        s->top++;
        s->data[s->top] = e;
        return SUCCEEDED;
    }
}

/*  If the stack is NOT empty, pop the top of the stack into e and return SUCCEEDED to indicate a successful pop.
 *  If the stack is empty, merely return FAILED to indicate an unsuccessful pop.
 */
State Pop(SequentialStackChar *s, ElemType *e) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        /* stack is empty */
        printf("The stack is empty.\n");
        return FAILED;
    }
    else {
        /* stack is NOT empty */
        *e = s->data[s->top];
        s->top--;
        return SUCCEEDED;
    }
}

/*  If the stack is NOT empty, assign the top of the stack to e and return SUCCEEDED to indicate a successful gettop.
 *   If the stack is empty, merely return FAILED to indicate an unsuccessful gettop.
 */
State GetTop(SequentialStackChar *s, ElemType *e) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        /* stack is empty */
        return FAILED;
    }
    else {
        /* stack is NOT empty */
        *e = s->data[s->top];
        return SUCCEEDED;
    }
}

/* Interfaces for the 2nd stack for double elements*/

/*  Initialize the sequential stack
 */
State InitStackDouble(SequentialStackDouble *s) {
    CHECKPOINTER(s);
    s->top = -1;
    return SUCCEEDED;
}

/*  Release the memory of the sequential stack
 */
void DestroyStackDouble(SequentialStackDouble *s) {
    CHECKPOINTERVOID(s);
    free(s);
}

/* Check if the stack is empty.
 * Return SUCCEEDED to indicate the stack is empty.
 * Return FAILED to indicate the stack is NOT empty.
 */
State StackEmptyDouble(SequentialStackDouble *s) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        return SUCCEEDED;
    }
    else {
        return FAILED;
    }
}

/* If the stack is NOT full, push e into it and return SUCCEEDED to indicate a successful push.
 * If the stack is full, merely return FAILED to indicate an unsuccessful push.
 */
State PushDouble(SequentialStackDouble *s, ElemTypeDouble e) {
    CHECKPOINTER(s);
    if (StackLen(s) >= MaxSize) {
        /* stack is full */
        printf("The stack is FULL.\n");
        return FAILED;
    }
    else {
        /* stack is not full */
        s->top++;
        s->data[s->top] = e;
        return SUCCEEDED;
    }
}

/* If the stack is NOT empty, pop the top of the stack into e and return SUCCEEDED to indicate a successful pop.
 * If the stack is empty, merely return FAILED to indicate an unsuccessful pop.
 */
State PopDouble(SequentialStackDouble *s,ElemTypeDouble *e) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        /* stack is empty */
        printf("The stack is empty.\n");
        return FAILED;
    }
    else {
        /* stack is NOT empty */
        *e = s->data[s->top];
        s->top--;
        return SUCCEEDED;
    }
}

/* If the stack is NOT empty, assign the top of the stack to e and return SUCCEEDED to indicate a successful gettop.
 * If the stack is empty, merely return FAILED to indicate an unsuccessful gettop.
 */
State GetTopDouble(SequentialStackDouble *s,ElemTypeDouble *e) {
    CHECKPOINTER(s);
    if (StackLen(s) <= 0) {
        /* stack is empty */
        return FAILED;
    }
    else {
        /* stack is NOT empty */
        *e = s->data[s->top];
        return SUCCEEDED;
    }
}
