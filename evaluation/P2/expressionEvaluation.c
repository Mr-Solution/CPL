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

/*
 * 格式化表达式
 * */
int format(char *s) {
    char tmp[100];
    int itr = 0;
    int len = strlen(s);
    int precursor = 0;
    int space_num = 0;
    for (int i=0; i<len; ++i) {
        if (isspace(s[i])) {
            // 去掉空格
            // 记录当前出现的空格数，作为判断数字间空格的依据
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

int extract_operand(char *s, char *t) {
    if (!isdigit(*s)) {
        return 0;
    }
    int index = 0;
    while (isdigit(*s) || '.' == *s) {
        t[index++] = *s;
        ++s;
    }
    if ('.'==t[index-1]) {
        t[index++] = '0';
    }
    t[index] = '\0';
    return 1;
}

int infixToPostfix(char *infixExpression, char postfixExpression[]) {
    if (format(infixExpression)) {
        return 0;
    }
    //创建一个字符栈
    STACK *sk = create_stack(100, sizeof(char));
    char c;
    int index = 0;
    while (*infixExpression != '\0') {
        c = *infixExpression;
        // 字符合法性检验
        if (!islegal(c)) {
            printf("err! illegal character: %c\n",c);
            dispose_stack(sk);
            return ILLEGAL_CHARACTER;
        }
        // 数字直接加入后缀表达式中
        if (isdigit(c)) {
            while (isdigit(c)) {
                postfixExpression[index++] = c;
                ++infixExpression;
                c = *infixExpression;
            }
            postfixExpression[index++] = ' ';
        }
        // 右括号，将栈内元素pop出来，直到遇到左括号。
        else if (')' == c) {
            // 若没有(，则说明(缺失
            while (!isEmpty(sk)
                    && *(char *)stack_top(sk) != '(') {
                c = *(char *)pop(sk);
                postfixExpression[index++] = c;
                postfixExpression[index++] = ' ';
            }
            if (!isEmpty(sk)) {
                pop(sk);
            }
            else {
                printf("err! improper braces, lack '('\n");
                dispose_stack(sk);
                return IMPROPER_BRACES;
            }
            ++infixExpression;
        }
        // 左括号直接入栈
        else if ('(' == c) {
            // 最后若无法pop出(,则说明)缺失
            push(sk, &c);
            ++infixExpression;
        }
        // 操作符，判断和栈顶操作符的优先级高低
        else if (isoperator(c)) {
            if (isEmpty(sk)
                    || '(' == *(char *)stack_top(sk)) {
                push(sk, &c);
            }
            else {
                while (!isEmpty(sk)
                        && priority(*(char *)stack_top(sk)) >= priority(c)
                        && *(char *)stack_top(sk) != '(') {
                    postfixExpression[index++] = *(char *)pop(sk);
                    postfixExpression[index++] = ' ';
                }
                push(sk, &c);
            }
            ++infixExpression;
        }
        // 空格
        else {
            ++infixExpression;
        }
    }
    while (!isEmpty(sk)) {
        c = *(char *)pop(sk);
        if ('(' == c) {
            printf("err! improper braces, lack ')'\n");
            dispose_stack(sk);
            return IMPROPER_BRACES;
        }
        postfixExpression[index++] = c;
        postfixExpression[index++] = ' ';
    }
    if (index > 0) {
        postfixExpression[index++] = '\0';
        dispose_stack(sk);
        return 1;
    }
    printf("err! empty expression\n");
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



/*
 * 合法操作符只有四种: + - * /
 * */
int isoperator(char c) {
    if ('+' == c 
            || '-' == c 
            || '*' == c 
            || '/' == c) {
        return 1;
    }
    return 0;
}

/*
 * 表达式的有效字符为: 数字，操作符，括号
 * 无效字符为: ' ', '   '
 * 其他字符为非法字符
 * */
int islegal(char c) {
    int ret = 0;
    if (isdigit(c)
            || isoperator(c)
            || isspace(c)
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
