/*************************************************************************
    > File Name: expressionEvaluation.c
    > Author: libo
    > Mail: seereeves@163.com 
    > Created Time: 30/07/2018 - 18:54
 ************************************************************************/

#include "expressionEvaluation.h"
#include <ctype.h>

#define DIGIT 1
#define BINARYOPERATOR 2
#define UNARYOPERATOR 3
#define BRACES 4

#define DESTROYSTACK(stack) do { \
    DestroyStack(stack); \
    stack = NULL; \
} while(0);

#define DESTROYSTACK1(stack) do { \
    DestroyStack1(stack); \
    stack = NULL; \
} while(0);

int isUnaryOperator(char c);
int isBinaryOperator(char c);
int islegal(char c);
int priority(char c);

int infixToPostfix(char *infixExpression,char postfixExpression[]) {
    SqStack *sk = (SqStack *)malloc(sizeof(SqStack));
    if (NULL == sk) {
        printf("err! Memory allocation failed!\n");
        return 0;
    }
    InitStack(sk);
    char topch;
    int index = 0;
    int priortype;        // the type of the prior character
    char priorch = '0';   // the value of the prior character
    while (*infixExpression != '\0') {
        // legitimacy checking
        if (!islegal(*infixExpression)) {
            printf("err! Illegal character: %c.\n", *infixExpression);
            DESTROYSTACK(sk);
            return 0;
        }
        // append the operands to the postfixExpression immediately
        if (isdigit(*infixExpression)) {
            if (DIGIT == priortype) {
                printf("err! There is an illegal space between operands %c and %c.\n", priorch,*infixExpression);
                return 0;
            }
            priortype = DIGIT;
            priorch = *infixExpression;
            while (isdigit(*infixExpression)) {
                postfixExpression[index++] = *infixExpression;
                ++infixExpression;
            }
            postfixExpression[index++] = '_';
        }
        // pop out the element until the top of the stack is '('
        else if (')' == *infixExpression) {
            priortype = BRACES;
            while (!StackEmpty(sk)) {
                if (Pop(sk, &topch)) {
                    if ('(' == topch) {
                        break;
                    }
                    postfixExpression[index++] = topch;
                }
            }
            if (topch != '(') {
                printf("err! Improper braces, lack '('\n");
                DESTROYSTACK(sk);
                return 0;
            }
            ++infixExpression;
        }
        // push the '(' into the stack immediately
        else if ('(' == *infixExpression) {
            priortype = BRACES;
            priorch = *infixExpression;
            if (!Push(sk, *infixExpression)) {
                printf("err! Push failed.\n");
                return 0;
            }
            ++infixExpression;
        }
        // process the operators
        else if (isBinaryOperator(*infixExpression)) {
            if (BINARYOPERATOR == priortype) {
                printf("err! There are two successive operators %c%c.\n",priorch, *infixExpression);
                return 0;
            }
            priortype = BINARYOPERATOR;
            if ( '-' == *infixExpression
                && ('(' == priorch || '0' == priorch) ) {
                *infixExpression = '$';
            }
            if ( '+' == *infixExpression
                && ('(' == priorch || '0' == priorch) ) {
                *infixExpression = '@';
            }
            priorch = *infixExpression;
            if (StackEmpty(sk)) {
                Push(sk, *infixExpression);
            }
            else {
                if (GetTop(sk, &topch)) {
                    if ('(' == topch) {
                        Push(sk, *infixExpression);
                    }
                    else {
                        while (!StackEmpty(sk)
                            && topch != '('
                            && priority(topch) >= priority(*infixExpression)) {
                            if (!Pop(sk, &topch)) {
                                printf("err! Pop failed.\n");
                            }
                            postfixExpression[index++] = topch;
                            GetTop(sk, &topch);
                        }
                        Push(sk, *infixExpression);
                    }
                }
            }
            ++infixExpression;
        }
        // spaces
        else {
            ++infixExpression;
        }
    }
    while (!StackEmpty(sk)) {
        if (Pop(sk, &topch)) {
            if ('(' == topch) {
                printf("err! improper braces, lack ')'\n");
                DESTROYSTACK(sk);
                return 0;
            }
            postfixExpression[index++] = topch;
        }
    }
    if (index > 0) {
        postfixExpression[index++] = '\0';
        DESTROYSTACK(sk);
        return 1;
    }
    printf("err! Empty expression.\n");
    DESTROYSTACK(sk);
    return 0;
}

int computeValueFromPostfix(char *postfixExpression, double *value) {
    SqStack1 *sk = (SqStack1 *)malloc(sizeof(SqStack1));
    if (NULL == sk) {
        printf("err! Memory allocation failed!\n");
        return 0;
    }
    InitStack1(sk);
    double a,b;
    double res;
    while (*postfixExpression != '\0') {
        if (isdigit(*postfixExpression)) {
            double sum = 0;
            while (isdigit(*postfixExpression)) {
                sum = sum * 10 + *postfixExpression - '0';
                ++postfixExpression;
            }
            Push1(sk, sum);
        }
        else if (isBinaryOperator(*postfixExpression)){
            if (!Pop1(sk, &b) || !Pop1(sk, &a)) {
                printf("ERROR occured when popping the operands. B\n");
                return 0;
            }
            switch (*postfixExpression) {
                case '+':
                    res = a+b;
                    break;
                case '-':
                    res = a-b;
                    break;
                case '*':
                    res = a*b;
                    break;
                case '/':
                    if (0 == b) {
                        printf("err! ZERO DIVIDE!\n");
                        return 0;
                    }
                    res = a/b;
                    break;
                default:
                    res = 1;
            }
            Push1(sk, res);
            ++postfixExpression;
        }
        else if (isUnaryOperator(*postfixExpression)) {
            if (!Pop1(sk, &a)) {
                printf("ERROR occured when popping the operands. U\n");
                return 0;
            }
            switch (*postfixExpression) {
                case '$':
                    res = -1 * a;
                    break;
                case '@':
                    res = a;
                    break;
                default:
                    res = 1;
            }
            Push1(sk, res);
            ++postfixExpression;
        }
        else {
            ++postfixExpression;
        }
    }
    if (!StackEmpty1(sk)) {
        if (!GetTop1(sk, value)) {
            printf("ERROR occured when getting the top of the stack.\n");
        }
        DESTROYSTACK1(sk);
        return 1;
    }
    DESTROYSTACK1(sk);
    return 0;
}

int isBinaryOperator(char c) {
    if ('+' == c 
            || '-' == c 
            || '*' == c 
            || '/' == c) {
        return 1;
    }
    return 0;
}

int isUnaryOperator(char c) {
    if ('@' == c
        || '$' == c) {
        return 1;
    }
    return 0;
}

int islegal(char c) {
    if (isdigit(c)
            || isspace(c)
            || isBinaryOperator(c)
            || '(' == c || ')' == c) {
        return 1;
    }
    return 0;
}

int priority(char c) {
    if (!isBinaryOperator(c) && !isUnaryOperator(c)) {
        printf("err! illegal operator : %c\n", c); 
        return 0;
    }   
    int ret = 0;
    switch(c) {
        case '+':
        case '-':
            ret = 1;
            break;
        case '*':
        case '/':
            ret = 2;
            break;
        case '$':
        case '@':
            ret = 3;
            break;
        default:
            ret = 0;
    }   
    return ret;
}