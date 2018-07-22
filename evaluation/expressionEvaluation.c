/*************************************************************************
	> File Name: expressionEvaluation.h
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 16/07/2018 - 16:49
 ************************************************************************/

#include "expressionEvaluation.h"
#include "sequentialStack.h"
#include <ctype.h>

int infixToPostfix(char *infixExpression, char postfixExpression[]) {
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
        else if ((isEmpty(sk) && *infixExpression != ')')
                || '(' == *infixExpression 
                || '(' == *(char *)stack_top(sk)) {
            push(sk, infixExpression);
            ++infixExpression;
        }
        else if (')' == *infixExpression){
            while (!isEmpty(sk)
                    && *(char *)stack_top(sk) != '(') {
                c = *(char *)pop(sk);
                postfixExpression[index++] = c;
                postfixExpression[index++] = ' ';
            }
            if (!isEmpty(sk))
                pop(sk); // '('出栈
            ++infixExpression;
        }
        else if (!isEmpty(sk)) {
            char top = *(char *)stack_top(sk);  // 栈顶元素
            while (priority(&top) >= priority(infixExpression)
                    && !isEmpty(sk)
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
        else if (' ' == *postfixExpression) {
            ++postfixExpression;
        }
        else {
            // 默认为运算符，暂时不做检测
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

int priority(char *c) {
    // 暂时不做合法性判断
    int ret = 0;
    switch(*c) {
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
