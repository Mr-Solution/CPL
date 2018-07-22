/*************************************************************************
	> File Name: expressionEvaluation.h
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 16/07/2018 - 16:49
 ************************************************************************/

#include "expressionEvaluation.h"
#include "sequentialStack.h"
#include <ctype.h>
#include <string.h>

#define IS_OPERAND 1
#define IS_OPERATOR 2

//错误码
#define EMPTY_EXPRESSION 1024
#define SPACES 1025
#define INSUFFICIENT_OPERANDS 1026
#define IMPROPER_BRACES 1027
#define ILLEGAL_CHARACTER 1028

int infixToPostfix(char *infixExpression, char postfixExpression[]) {
    int ret = strip(infixExpression);
    if (ret > 0){
        return 0;
    }
    //创建一个字符栈
    STACK *sk = create_stack(100, sizeof(char));
    char c;
    int index = 0;
    while (*infixExpression != '\0') {
        if (isdigit(*infixExpression)) {
            while (isdigit(*infixExpression)) {
                postfixExpression[index++] = *infixExpression;
                ++infixExpression;
            }
            postfixExpression[index++] = ' ';
        }
        // 字符操作
        else if (')' == *infixExpression){
            while (!isEmpty(sk)
                    && *(char *)stack_top(sk) != '(') {
                c = *(char *)pop(sk);
                postfixExpression[index++] = c;
                postfixExpression[index++] = ' ';
            }
            if (!isEmpty(sk)) {
                c = *(char *)pop(sk); // '('出栈
            }
            else {
                printf("err! improper braces\n");
                dispose_stack(sk);
                return IMPROPER_BRACES;
            }
            ++infixExpression;
        }
        else if ((isEmpty(sk) && *infixExpression != ')')
                || '(' == *infixExpression 
                || '(' == *(char *)stack_top(sk)) {
            push(sk, infixExpression);
            ++infixExpression;
        }
        else if (!isEmpty(sk)) {
            char top = *(char *)stack_top(sk);  // 栈顶元素
            while (!isEmpty(sk)
                    && priority(top) >= priority(*infixExpression)
                    && top != '(') {
                c = *(char *)pop(sk);
                postfixExpression[index++] = c;
                postfixExpression[index++] = ' ';
                top = *(char *)stack_top(sk);
            }
            push(sk, infixExpression);
            ++infixExpression;
        }
    }
    while (!isEmpty(sk)) {
        c = *(char *)pop(sk);
        if ('(' == c) {
            printf("err! improper braces\n");
            dispose_stack(sk);
            return IMPROPER_BRACES;
        }
        postfixExpression[index++] = c;
        postfixExpression[index++] = ' ';
    }
    if (index > 0) {
        postfixExpression[index] = '\0';
        dispose_stack(sk);
        return 1;
    }
    dispose_stack(sk);
    return 0;
}

int computeValueFromPostfix(char *postfixExpression, double *value) {
    STACK *sk = create_stack(100, sizeof(double));
    while (*postfixExpression != '\0') {
        if (isdigit(*postfixExpression)) {
            double sum = 0;
            while (isdigit(*postfixExpression)) {
                sum = sum * 10 + *postfixExpression - '0';
                ++postfixExpression;
            }
            push(sk, &sum);
        }
        else if (isspace(*postfixExpression)) {
            ++postfixExpression;
        }
        else if (isoperator(*postfixExpression)){
            double a,b;
            double res;
            b = *(double *)pop(sk);
            a = *(double *)pop(sk);
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
                    res = a/b;
                    break;
                default:
                    res = 1;
            }
            push(sk, &res);
            ++postfixExpression;
        }
        else {
            ++postfixExpression;
        }
    }
    if (1 == stack_size(sk)) {
        *value = *(double *)stack_top(sk);
        clear(sk);
        dispose_stack(sk);
        return 1;
    }
    dispose_stack(sk);
    return 0;
}

int strip(char *s) {
    char tmp[100];
    int itr = 0;
    int len = strlen(s);
    int precursor = 0;
    int space_num = 0;
    for (int i=0; i<len; ++i) {
        if (isspace(s[i])) {
            ++space_num;
        }
        else {
            if (!islegal(s[i])) {
                printf("err! illegal character %c.\n", s[i]);
                return ILLEGAL_CHARACTER;
            }
            if (precursor == IS_OPERATOR && isoperator(s[i])) {
                // 前一个有效字符是操作符，当前字符也是操作符
                printf("err! insufficient operands\n");
                return INSUFFICIENT_OPERANDS;
            }
            if (precursor == IS_OPERAND && isdigit(s[i]) && space_num > 0) {
                // 前一个有效字符是数字，当前字符也是数字, 并且之间有空格
                printf("err! Spaces between two operands\n");
                return SPACES;
            }
            if (isdigit(s[i])) {
                precursor = IS_OPERAND;
            }
            else if (isoperator(s[i])){
                precursor = IS_OPERATOR;
            }
            tmp[itr++] = s[i];
            space_num = 0;
        }
    }
    if (0 == itr) {
        printf("err! empty expression\n");
        return EMPTY_EXPRESSION;
    }
    if (precursor == IS_OPERATOR) {
        // 最后一个有效字符是操作符
        printf("err! insufficient operands\n");
        return INSUFFICIENT_OPERANDS;
    }
    tmp[itr++] = '\0';
    strcpy(s, tmp);
    return 0;
}

int isoperator(char c) {
    if ('+' == c 
            || '-' == c 
            || '*' == c 
            || '/' == c) {
        return 1;
    }
    return 0;
}

int isoperand(char c) {
    return 0;
}

int islegal(char c) {
    int ret = 0;
    if (isdigit(c)
            || isoperator(c)
            || '(' == c
            || ')' == c) {
        ret = 1;
    }
    return ret;
}

int priority(char c) {
    if (!islegal(c)) {
        printf("err! illegal character : %c\n", c);
        return ILLEGAL_CHARACTER;
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
        default:
            ret = 0;
    }
    return ret;
}


