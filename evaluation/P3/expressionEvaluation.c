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
 * return the character before s[position - step]
 * if position == 0, return '\0'
 */
char getpriorCH(char *s, int position, int step);

/*
 * This function will check whether the character is legal , 
 * filter out the spaces, and identify different elements,
 * such as operands, binary operators, unary operators, etc. 
 * If everything is all right, RETURN 1; otherwise, RETURN 0 
*/ 
int expressionFilter(char *infixExpression);

int infixToPostfix(char *infixExpression,char postfixExpression[]) {
    if (!expressionFilter(infixExpression)) {
        printf("err! expression filter failed. \n");
        return 0;
    }
    SqStack *sk = (SqStack *)malloc(sizeof(SqStack));
    InitStack(sk);

    char topch;
    int index = 0;
    // There is no need to do the legitimacy checking, 
    // because it has been done in the expressionFilter function
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

int expressionFilter(char *s) {
    char tmp[100];
    int len = strlen(s);
    int itr = 0;
    int spacesNum = 0;
    char priorCH;
    for (int i=0; i<len; ++i) {
        if (!islegal(s[i])) {
            printf("err! Filter found illegal character: '%c'. \n", s[i]);
            return 0;
        }
        if (isdigit(s[i])) {  
            /* forward traversal, the prior char (which is not a space) and the judgement are as follow
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
                printf("err! There has a space between two digits. \n");
                return 0;
            }
            if (')' == priorCH) {
                printf("err! An operand is required between the ')' and digit '%c'. \n", s[i]);
                return 0;
            }
            if (isUnaryOperator(priorCH) && spacesNum > 0) {
                printf("err! The sign and the digit should not be separated by space. \n");
                return 0;
            }
            tmp[itr++] = s[i];
            spacesNum = 0;
        }
        else if (isBinaryOperator(s[i])) {
            /* forward traversal, the prior char and the judgement are as follow
             * digit : right
             * '(' : +/- discriminate as an unary operator; while * and / is wrong
             * ')' : right
             * operator : wrong, successive operators
             * discriminate unary operator
            */

            // Both the binary operator and the unary operator are not allowed to locate in the last position
            if (i >= len-1) {
                printf("err! An operand is required after the operator '%c'. \n", s[i]);
                return 0;
            }
            priorCH = getpriorCH(s, i, spacesNum);
            // Unary operator
            if ( '-' == s[i] || '+' == s[i]) {
                if ( '\0' == priorCH || '(' == priorCH ) {
                    if ('-' == s[i])
                        s[i] = '$';
                    else 
                        s[i] = '@';
                    // s[i] is an unary operator
                }
            }
            if (isBinaryOperator(s[i])) {
                if ('\0' == priorCH) {
                    printf("err! An operand is required before the operator '%c'. \n", s[i]);
                    return 0;
                }
                if (isBinaryOperator(priorCH) || isUnaryOperator(priorCH)) {
                    printf("err! There are two successive operators '%c %c'. \n", priorCH, s[i]);
                    return 0;
                }
                if ('(' == priorCH) {
                    printf("err! An operand is required between '(' the operator '%c'. \n", s[i]);
                    return 0;
                }
            }
            
            tmp[itr++] = s[i];
            spacesNum = 0;
        }
        else if ('(' == s[i]) { // ) digit ( )
            /* forward traversal, the prior char and the judgement are as follow
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
                printf("err! An operator is required between '%c' and '%c'. \n", priorCH, s[i]);
                return 0;
            }
            if (isUnaryOperator(priorCH) && spacesNum > 0) {
                printf("err! The sign and the digit should not be separated by space. \n");
                return 0;
            }
            if (')' == priorCH) {
                printf("err! An operator is required between '%c' and '%c'. \n", priorCH, s[i]);
                return 0;
            }
            tmp[itr++] = s[i];
            spacesNum = 0;
        }
        else if (')' == s[i]) {
            /* forward traversal, the prior char and the judgement are as follow
             * spaces : pass and spacesNum++
             * digit : right
             * '(' : wrong
             * ')' : right
             * operator : wrong
             * '\0' : wrong
            */
            priorCH = getpriorCH(s, i, spacesNum);
            if ('(' == priorCH) {
                printf("err! There is no content in the braces. \n");
                return 0;
            }
            if (isBinaryOperator(priorCH) || isUnaryOperator(priorCH)) {
                printf("err! An operand is required between the operator '%c' and ')'. \n", priorCH);
                return 0;
            }
            if ('\0' == priorCH) {
                printf("err! Braces are not matched. \n");
                return 0;
            }
            tmp[itr++] = s[i];
            spacesNum = 0;
        }
        else {  
            // isspaces(s[i])
            // This counter will be reset when s[i] is not a space. 
            ++spacesNum;
        }
    }
    // priorCH is the last character
    priorCH = getpriorCH(s, len, spacesNum);
    if (isBinaryOperator(priorCH) || isUnaryOperator(priorCH)) {
        printf("err! An operand is required after the operator '%c' \n", priorCH);
        return 0;
    }
    if ('(' == priorCH) {
        printf("err! Braces are not matched. \n");
        return 0;
    }
    tmp[itr++] = '\0';
    strcpy(s, tmp);
    return 1;
}