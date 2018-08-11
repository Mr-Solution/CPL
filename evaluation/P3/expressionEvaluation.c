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

#define DESTROYSTACKDOUBLE(stack) do { \
    DestroyStackDouble(stack); \
    stack = NULL; \
} while(0);

#define PUSH(STACK, ELEM) do { \
    if (!Push(STACK, ELEM)) { \
        printf("err! Push failed \n"); \
        DESTROYSTACK(STACK); \
        return 0; \
    } \
} while(0);

#define PUSHDOUBLE(STACK, ELEM) do { \
    if (!PushDouble(STACK, ELEM)) { \
        printf("err! PUSHDOUBLE failed \n"); \
        DESTROYSTACKDOUBLE(STACK); \
        return 0; \
    } \
} while(0);

int isUnaryOperator(char c);
int isBinaryOperator(char c);
int islegal(char c);
int priority(char c);
/*
 * return the character before s[position - step]
 * if position == 0, return '\0'
 * */
char getpriorCH(char *s, int position, int step);
/* Convert a unary operator to a binary operator */
char U2B(char unary);
/* Convert a binary operator to a unary operator */
char B2U(char binary);
/*
 * This function will check whether the character is legal , 
 * filter out the spaces, and identify different elements,
 * such as operands, binary operators, unary operators, etc. 
 * If everything is all right, RETURN 1; otherwise, RETURN 0 
 * */ 
int expressionFilter(char *infixExpression);

State infixToPostfix(char *infixExpression,char postfixExpression[]) {
    /* verificate the infixExpression */
    if (!expressionFilter(infixExpression)) { return 0; }
 
    SequentialStackChar *sk = (SequentialStackChar *)malloc(sizeof(SequentialStackChar));
    InitStack(sk);

    char topch;
    int index = 0;
    /* There is no need to do the legitimacy checking,          */
    /* because it has been done in the expressionFilter function*/ 
    while (*infixExpression != '\0') {
        topch = '\0';  /* refresh the value of topch */
        /* append the operands to the postfixExpression immediately */
        if (isdigit(*infixExpression)) {
            while (isdigit(*infixExpression)) {
                postfixExpression[index++] = *infixExpression;
                ++infixExpression;
            }
            postfixExpression[index++] = '_';
        }
        /* pop out the element until the top of the stack is '(' */
        else if (')' == *infixExpression) {
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
                printf("err! No matched '(' before ')'. \n");
                DESTROYSTACK(sk);
                return 0;
            }
            ++infixExpression;
        }
        /* push the '(' into the stack immediately */
        else if ('(' == *infixExpression) {
            PUSH(sk, *infixExpression);
            ++infixExpression;
        }
        /* process the operators */
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
        /* spaces */
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
            printf("err! No matched ')' after '('. \n");
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

State computeValueFromPostfix(char *postfixExpression, double *value) {
    SequentialStackDouble *sk = (SequentialStackDouble *)malloc(sizeof(SequentialStackDouble));
    if (NULL == sk) {
        printf("err! Memory allocation failed! \n");
        return 0;
    }
    InitStackDouble(sk);
    double a,b;
    double res;
    while (*postfixExpression != '\0') {
        if (isdigit(*postfixExpression)) {
            double sum = 0;
            while (isdigit(*postfixExpression)) {
                sum = sum * 10 + *postfixExpression - '0';
                ++postfixExpression;
            }
            PUSHDOUBLE(sk, sum);
        }
        else if (isBinaryOperator(*postfixExpression)){
            if (!PopDouble(sk, &b) || !PopDouble(sk, &a)) {
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
                        printf("err! ZERO DIVISOR! \n");
                        return 0;
                    }
                    res = a/b;
                    break;
                default:
                    res = 1;
            }
            PUSHDOUBLE(sk, res);
            ++postfixExpression;
        }
        else if (isUnaryOperator(*postfixExpression)) {
            if (!PopDouble(sk, &a)) {
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
            PUSHDOUBLE(sk, res);
            ++postfixExpression;
        }
        else {
            ++postfixExpression;
        }
    }
    if (!StackEmptyDouble(sk)) {
        if (!GetTopDouble(sk, value)) {
            printf("ERROR occured when getting the top of the stack. \n");
            return 0;
        }
        DESTROYSTACKDOUBLE(sk);
        return 1;
    }
    printf("err! Calculation failed. \n");
    DESTROYSTACKDOUBLE(sk);
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

char getpriorCH(char *s, int position, int step) {
    int len = strlen(s);
    char priorCH;
    if (position > len || position < 0) {
        printf("err! Illegal parameter. \n");
        return '\0';
    }
    if (position <= 0) {
        priorCH = '\0';
    }
    else if (step > 0) {
        if (position == step)
            priorCH = '\0';
        else
            priorCH = s[position - 1 - step];
    }
    else {
        priorCH = s[position-1];
    }
    return priorCH;
}

char U2B(char unary) {
    if ('@' == unary)
        return '+';
    if ('$' == unary)
        return '-';
    return unary;
}

char B2U(char binary) {
    if ('+' == binary)
        return '@';
    if ('-' == binary) 
        return '$';
    return binary;
}

int expressionFilter(char *s) {
    char tmp[100];
    int len = strlen(s);
    int itr = 0;
    int spacesNum = 0;
    char priorCH;
    for (int i=0; i<len; ++i) {
        if (!islegal(s[i])) {
            printf("err! Illegal character '%c' in the expression. \n", s[i]);
            return 0;
        }
        if (isdigit(s[i])) {  
            /* forward traversal, the prior character (which is not a space) 
             * and the judgement are as follow:
             * digit : right
             * digit+space : wrong
             * '(' : right
             * ')' : wrong
             * binary operator : right
             * unary operator : right
             * unary operator + space: wrong
            */ 
            priorCH = getpriorCH(s, i, spacesNum);
            if (isdigit(priorCH) && spacesNum > 0) {
                printf("err! No operator between two operands. \n");
                return 0;
            }
            if (')' == priorCH) {
                printf("err! An operand is required between the ')' and digit '%c'. \n", s[i]);
                return 0;
            }
            if (isUnaryOperator(priorCH) && spacesNum > 0) {
                if ('$' == priorCH)
                    printf("err! A space follows a unary operator '-'. \n");
                else
                    printf("err! A space follows a unary operator '+'. \n");
                return 0;
            }
            tmp[itr++] = s[i];
            spacesNum = 0;
        }
        else if (isBinaryOperator(s[i])) {
            /* forward traversal, the prior character and the judgement are as follow
             * digit : right
             * '(' : +/- discriminate as an unary operator; while * and / is wrong
             * ')' : right
             * operator : wrong, successive operators
             * discriminate unary operator
            */

            /* Both the binary operator and the unary operator */
            /* are not allowed to locate in the last position  */
            if (i >= len-1) {
                printf("err! No operand after the last operator '%c' in the expression. \n", s[i]);
                return 0;
            }
            priorCH = getpriorCH(s, i, spacesNum);
            /* Unary operator */
            if ( '-' == s[i] || '+' == s[i]) {
                if ( '\0' == priorCH || '(' == priorCH ) {
                    s[i] = B2U(s[i]);
                    /* s[i] is an unary operator */
                }
            }
            if (isBinaryOperator(s[i])) {
                if ('\0' == priorCH) {
                    printf("err! No operand before the first operator '%c'. \n", s[i]);
                    return 0;
                }
                if (isBinaryOperator(priorCH)) {
                    printf("err! There are two successive operators '%c %c'. \n", priorCH, s[i]);
                    return 0;
                }
                if (isUnaryOperator(priorCH)) {
                    printf("err! There are two successive operator '%c %c'. \n", U2B(priorCH), s[i]);
                    return 0;
                }
                if ('(' == priorCH) {
                    printf("err! No operand between '(' and '%c'. \n", s[i]);
                    return 0;
                }
            }
            tmp[itr++] = s[i];
            spacesNum = 0;
        }
        else if ('(' == s[i]) {
            /* forward traversal, the prior character and the judgement are as follow
             * spaces : pass and spacesNum++
             * digit : wrong
             * '(' : right
             * ')' : wrong
             * binary operator : right
             * unary operator : right
             * unary operator + space : wrong
             * '\0' : right
            */
            priorCH = getpriorCH(s, i, spacesNum);
            if (isdigit(priorCH)) {
                printf("err! No operator between a digit '%c' and '('. \n", priorCH);
                return 0;
            }
            if (isUnaryOperator(priorCH) && spacesNum > 0) {
                printf("err! A space follows a unary operator '%c'. \n", U2B(priorCH));
                return 0;
            }
            if (')' == priorCH) {
                printf("err! No operator between ')' and '('. \n");
                return 0;
            }
            tmp[itr++] = s[i];
            spacesNum = 0;
        }
        else if (')' == s[i]) {
            /* forward traversal, the prior character and the judgement are as follow
             * spaces : pass and spacesNum++
             * digit : right
             * '(' : wrong
             * ')' : right
             * operator : wrong
             * '\0' : wrong
             * */
            priorCH = getpriorCH(s, i, spacesNum);
            if ('(' == priorCH) {
                printf("err! No operand between '(' and ')'. \n");
                return 0;
            }
            if (isBinaryOperator(priorCH)) {
                printf("err! No operand between '%c' and ')'. \n", priorCH);
                return 0;
            }
            if (isUnaryOperator(priorCH)) {
                printf("err! No operand between '%c' and ')'. \n", U2B(priorCH));
                return 0;
            }
            if ('\0' == priorCH) {
                printf("err! No matched '(' before ')'. \n");
                return 0;
            }
            tmp[itr++] = s[i];
            spacesNum = 0;
        }
        else {  
            /* isspaces(s[i]) */
            /* The counter spacesNum will be reset when s[i] is not a space. */  
            ++spacesNum;
        }
    }
    /* priorCH is the last character that is not a space */
    priorCH = getpriorCH(s, len, spacesNum);
    if (isBinaryOperator(priorCH)) {
        printf("err! No operand after the last operator '%c' in the expression. \n", priorCH);
        return 0;
    }
    if (isUnaryOperator(priorCH)) {
        printf("err! No operand after the last operator '%c' in the expression. \n", U2B(priorCH));
        return 0;
    }
    if ('(' == priorCH) {
        printf("err! No matched ')' after '('. \n");
        return 0;
    }
    tmp[itr++] = '\0';
    strcpy(s, tmp);
    return 1;
}
