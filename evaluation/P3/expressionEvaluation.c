/*************************************************************************
    > File Name: expressionEvaluation.c
    > Author: libo
    > Mail: seereeves@163.com 
    > Created Time: 30/07/2018 - 18:54
 ************************************************************************/

#include "expressionEvaluation.h"
#include <ctype.h>
#include <string.h>

#define DESTROYSTACK(stack) do { \
    DestroyStack(stack); \
    stack = NULL; \
} while(0);

#define DESTROYSTACK1(stack) do { \
    DestroyStack1(stack); \
    stack = NULL; \
} while(0);

#define PUSH(STACK, ELEM) do { \
    if (!Push(STACK, ELEM)) { \
        printf("err! Push failed \n"); \
        return 0; \
    } \
} while(0);

#define PUSH1(STACK, ELEM) do { \
    if (!Push1(STACK, ELEM)) { \
        printf("err! Push1 failed \n"); \
        return 0; \
    } \
} while(0);

int isUnaryOperator(char c);
int isBinaryOperator(char c);
int islegal(char c);
int priority(char c);
/*
 * This function will check whether the character is legal and 
 * Split the infixExpression into a series of separate elements: 
 * such as operands, binary operators, unary operators, etc. 
 * different elements are separated by a space
 * If everything is all right, RETURN 1; otherwise, RETURN 0 
*/ 
int splitExpression(char *infixExpression);

int infixToPostfix(char *infixExpression,char postfixExpression[]) {
    if (!splitExpression(infixExpression)) {
        return 0;
    }
    SqStack *sk = (SqStack *)malloc(sizeof(SqStack));
    if (NULL == sk) {
        printf("err! Memory allocation failed! \n");
        return 0;
    }
    InitStack(sk);
    char topch;
    int index = 0;
    // we don't do the legitimacy checking
    // because it has been done in the splitExpression function
    while (*infixExpression != '\0') {
        // append the operands to the postfixExpression immediately
        if (isdigit(*infixExpression)) {
            while (isdigit(*infixExpression)) {
                postfixExpression[index++] = *infixExpression;
                ++infixExpression;
            }
            postfixExpression[index++] = '_';
        }
        // pop out the element until the top of the stack is '('
        else if (')' == *infixExpression) {
            // priortype = BRACES;
            while (!StackEmpty(sk)) {
                if (!Pop(sk, &topch)) {
                    printf("err! Pop failed. \n");
                    return 0;
                }
                if ('(' == topch) {
                    break;
                }
                postfixExpression[index++] = topch;
            }
            if (topch != '(') {
                printf("err! Improper braces, lack '('. \n");
                DESTROYSTACK(sk);
                return 0;
            }
            ++infixExpression;
        }
        // push the '(' into the stack immediately
        else if ('(' == *infixExpression) {
            PUSH(sk, *infixExpression);
            ++infixExpression;
        }
        // process the operators
        else if (isBinaryOperator(*infixExpression) || isUnaryOperator(*infixExpression)) {
            if (StackEmpty(sk)) {
                PUSH(sk, *infixExpression);
            }
            else {
                if (GetTop(sk, &topch)) {
                    if ('(' == topch) {
                        PUSH(sk, *infixExpression);
                    }
                    else {
                        while (!StackEmpty(sk)
                            && topch != '('
                            && priority(topch) >= priority(*infixExpression)) {
                            if (!Pop(sk, &topch)) {
                                printf("err! Pop failed. \n");
                                return 0;
                            }
                            postfixExpression[index++] = topch;
                            GetTop(sk, &topch);
                        }
                        PUSH(sk, *infixExpression);
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
        if (!Pop(sk, &topch)) {
            printf("err! Pop failed. \n");
            return 0;
        }
        if ('(' == topch) {
            printf("err! Improper braces, lack ')'. \n");
            DESTROYSTACK(sk);
            return 0;
        }
        postfixExpression[index++] = topch;
        
    }
    if (index > 0) {
        postfixExpression[index++] = '\0';
        DESTROYSTACK(sk);
        return 1;
    }
    printf("err! Empty expression. \n");
    DESTROYSTACK(sk);
    return 0;
}

int computeValueFromPostfix(char *postfixExpression, double *value) {
    SqStack1 *sk = (SqStack1 *)malloc(sizeof(SqStack1));
    if (NULL == sk) {
        printf("err! Memory allocation failed! \n");
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
            PUSH1(sk, sum);
        }
        else if (isBinaryOperator(*postfixExpression)){
            if (!Pop1(sk, &b) || !Pop1(sk, &a)) {
                printf("ERROR occured when popping the operands. \n");
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
                        printf("err! ZERO DIVIDE! \n");
                        return 0;
                    }
                    res = a/b;
                    break;
                default:
                    res = 1;
            }
            PUSH1(sk, res);
            ++postfixExpression;
        }
        else if (isUnaryOperator(*postfixExpression)) {
            if (!Pop1(sk, &a)) {
                printf("ERROR occured when popping the operands. \n");
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
            PUSH1(sk, res);
            ++postfixExpression;
        }
        else {
            ++postfixExpression;
        }
    }
    if (!StackEmpty1(sk)) {
        if (!GetTop1(sk, value)) {
            printf("ERROR occured when getting the top of the stack. \n");
            return 0;
        }
        DESTROYSTACK1(sk);
        return 1;
    }
    printf("err! Calculation failed. \n");
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
        printf("err! Illegal operator : %c. \n", c); 
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

int splitExpression(char *s) {
    char tmp[100];
    int len = strlen(s);
    int itr = 0;
    for (int i=0; i<len; ++i) {
        if (!islegal(s[i])) {
            printf("err! Split found Illegal character: %c. \n", s[i]);
            return 0;
        }
        if (isdigit(s[i])) {  // Backward traversal 
            int spacesNum = 0;
            for (int j=i; j<len; ++j) {
                if (!islegal(s[j])) {
                    printf("err! split found Illegal character: %c.\n", s[j]);
                    return 0;
                }
                if (isBinaryOperator(s[j]) || ')' == s[j]) {
                    break;  // We expect an operator or a ')' behind the operand
                }
                if (isspace(s[j])) {
                    ++spacesNum;
                    continue;
                }
                if (isdigit(s[j])) {
                    if (spacesNum > 0) {
                        printf("err! There is an illegal space between operands %c and %c.\n",s[i], s[j]);
                        return 0;
                    }
                }
                if ('(' == s[j]) {
                    printf("err! An operator is required before the %d-th character '('.\n", i+j);
                    return 0;
                }
            }
            tmp[itr++] = s[i];
        }
        else if (isBinaryOperator(s[i])) {
            if (0 == i) {
                if ('-' == s[i]) 
                    s[i] = '$';
                else if ('+' == s[i]) 
                    s[i] = '@';
            }
            else { // i>0
                for (int j=i+1; j<len; ++j) { // Backward traversal 
                    if (!islegal(s[j])) {
                        printf("err! split found Illegal character: %c.\n", s[j]);
                        return 0;
                    }
                    if ('(' == s[j] || isdigit(s[j])) {
                        break;  // We expect a '(' or a digit behind the operator
                    }
                    if (isBinaryOperator(s[j])) {
                        printf("err! There are two successive operators %c %c.\n",s[i], s[j]);
                        return 0;
                    }
                    if (len-1 == j) {
                        printf("err! An operand is required after the operator %c.\n", s[i]);
                        return 0;
                    }
                }
                for (int j=i-1; j>=0; --j) {  // Forward traversal
                    if (!islegal(s[j])) {
                        printf("err! split found Illegal character: %c.\n", s[j]);
                        return 0;
                    }
                    if (')' == s[j] || isdigit(s[j])) {
                        break;
                    }
                    if (isBinaryOperator(s[j])) {
                        printf("err! There are two successive operators %c %c.\n",s[j], s[i]);
                        return 0;
                    }
                    if ('(' == s[j] || 0 == j) {
                        if ('-' == s[i]) 
                            s[i] = '$';
                        else if ('+' == s[i]) 
                            s[i] = '@';
                        break;
                    }
                }
            }
            if ('@' == s[i] || '$' == s[i]) {
                if (len == i) {
                    printf("err! An operand is required after the operator %c", s[i]);
                    return 0;
                }
                else if (!isdigit(s[i+1]) && '(' != s[i+1]) {
                    printf("err! The sign and the digit should not be separated by space.\n");
                    return 0;
                }
            }
            tmp[itr++] = s[i];
        }
        else if ('(' == s[i]) {
            if (itr > 0 && ')' == tmp[itr-1]) {
                printf("err! An operator is expected between ')' and '('. \n");
                return 0;
            }
            tmp[itr++] = s[i];
        }
        else if (')' == s[i]) {
            if (itr > 0 && '(' == tmp[itr-1]) {
                printf("err! Empty ( ). \n");
                return 0;
            }
            tmp[itr++] = s[i];
        }
        else {  // isspaces(s[i])
            ;   // Skip the spaces in the original string. 
        }
    }
    tmp[itr++] = '\0';
    strcpy(s, tmp);
    return 1;
}