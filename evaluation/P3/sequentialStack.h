//
//  main.c
//  sequentialStack
//
//  Created by williamzhuuestc on 2018/6/23.
//  Copyright © 2018年 williamzhuuestc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
typedef char ElemType;
typedef double ElemTypeDouble;
typedef enum state {FAILED, SUCCEEDED} State;   // State for stack operation

/*  Sequential stack to store char elements.
 */
typedef struct {
    ElemType data[MaxSize];
    int top;
} SequentialStackChar;

/*  Sequential stack to store double elements.
 */
typedef struct {
    ElemTypeDouble data[MaxSize];
    int top;
} SequentialStackDouble;


/* Interfaces for the 1st stack for char elements*/

/*  Initialize the sequential stack
 */
State InitStack(SequentialStackChar *s);

/*  Release the memory of the sequential stack
 */
void DestroyStack(SequentialStackChar *s);

/*  Check if the stack is empty.
    Return SUCCEEDED to indicate the stack is empty.
    Return FAILED to indicate the stack is NOT empty.
 */
State StackEmpty(SequentialStackChar *s);

/*  If the stack is NOT full, push e into it and return SUCCEEDED to indicate a successful push.
    If the stack is full, merely return FAILED to indicate an unsuccessful push.
 */
State Push(SequentialStackChar *s, ElemType e);

/*  If the stack is NOT empty, pop the top of the stack into e and return SUCCEEDED to indicate a successful pop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful pop.
 */
State Pop(SequentialStackChar *s, ElemType *e);

/*  If the stack is NOT empty, assign the top of the stack to e and return SUCCEEDED to indicate a successful gettop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful gettop.
 */
State GetTop(SequentialStackChar *s, ElemType *e);



/* Interfaces for the 2nd stack for double elements*/

/*  Initialize the sequential stack
 */
State InitStackDouble(SequentialStackDouble *s);

/*  Release the memory of the sequential stack
 */
void DestroyStackDouble(SequentialStackDouble *s);

/*  Check if the stack is empty.
 Return SUCCEEDED to indicate the stack is empty.
 Return FAILED to indicate the stack is NOT empty.
 */
State StackEmptyDouble(SequentialStackDouble *s);

/*  If the stack is NOT full, push e into it and return SUCCEEDED to indicate a successful push.
    If the stack is full, merely return FAILED to indicate an unsuccessful push.
 */
State PushDouble(SequentialStackDouble *s, ElemTypeDouble e);

/*  If the stack is NOT empty, pop the top of the stack into e and return SUCCEEDED to indicate a successful pop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful pop.
 */
State PopDouble(SequentialStackDouble *s, ElemTypeDouble *e);

/*  If the stack is NOT empty, assign the top of the stack to e and return SUCCEEDED to indicate a successful gettop.
    If the stack is empty, merely return FAILED to indicate an unsuccessful gettop.
 */
State GetTopDouble(SequentialStackDouble *s, ElemTypeDouble *e);
