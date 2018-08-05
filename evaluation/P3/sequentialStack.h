//
//  main.c
//  sequentialStack
//
//  Created by williamzhuuestc on 2018/6/23.
//  Copyright © 2018年 williamzhuuestc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MaxSize 30
typedef char ElemType;
typedef double ElemType1;

/*  Sequential stack to store char elements.
 */
typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

/*  Sequential stack to store double elements.
 */
typedef struct {
    ElemType1 data[MaxSize];
    int top;
} SqStack1;


/* Interfaces for the 1st stack for char elements*/

/*  Initialize the sequential stack
 */
void InitStack(SqStack *s);

/*  Release the memory of the sequential stack
 */
void DestroyStack(SqStack *s);

/*  Check if the stack is empty.
    Return 1 to indicate the stack is empty.
    Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty(SqStack *s);

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push(SqStack *s, ElemType e);

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop(SqStack *s, ElemType *e);

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop(SqStack *s, ElemType *e);

void display(SqStack *s);


/* Interfaces for the 2nd stack for double elements*/

/*  Initialize the sequential stack
 */
void InitStack1(SqStack1 *s);

/*  Release the memory of the sequential stack
 */
void DestroyStack1(SqStack1 *s);

/*  Check if the stack is empty.
 Return 1 to indicate the stack is empty.
 Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty1(SqStack1 *s);

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push1(SqStack1 *s, ElemType1 e);

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop1(SqStack1 *s,ElemType1 *e);

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop1(SqStack1 *s,ElemType1 *e);
