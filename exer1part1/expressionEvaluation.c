#include "expressionEvaluation.h"
// #include "linkedstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int infixToPostfix(char *properInfixExpressions, char postfixExpression[]) {
    int index = 0;
    Stack *stack = createStack(sizeof(char));
    while(*properInfixExpressions != '\0' ){
        char c = *properInfixExpressions;
        if (isdigit(c)){
            postfixExpression[index++] = c;
            if (*(properInfixExpressions+1) != '\0' && !isdigit(*(properInfixExpressions + 1)))    
                postfixExpression[index++] = ' ';
        }else if(c =='('){
            push(stack, &c);
        }else if(c == '/' || c == '*'){
            if(!isEmpty(stack)){
                char tmp = *(char *)peek(stack);
                while(tmp=='/'||tmp=='*') {
                    tmp = *(char *)pop(stack);
                    postfixExpression[index++] = tmp;
                    if (isEmpty(stack))    break;
                    tmp = *(char *)peek(stack);
                }
            }
            push(stack, &c);
        }else if(c == '+' || c == '-'){
            if(isEmpty(stack)) {
                push(stack, &c);
                properInfixExpressions++;
                continue;
            }
            char tmp = *(char *)peek(stack);
            while(tmp=='*' || tmp=='/') {
                tmp = *(char *)pop(stack);
                postfixExpression[index++] = tmp;
                if (isEmpty(stack))    break;
                tmp = *(char *)peek(stack);
            }
            while(tmp=='+' || tmp=='-') {
                tmp = *(char *)pop(stack);
                postfixExpression[index++] = tmp;
                if (isEmpty(stack))    break;
                tmp = *(char *)peek(stack);
            }

            push(stack, &c);

        }else if(c == ')') {
            char tmp = *(char *)pop(stack);
            while (tmp != '(') {
                postfixExpression[index++] = tmp;
                tmp = *(char *)pop(stack);
            }
        }
        properInfixExpressions++;
    }
    while(!isEmpty(stack)){
        postfixExpression[index++] = *(char *)pop(stack);
    }
    postfixExpression[index] = '\0';
    return 1;
}


int computeValueFromPostfix(char *postfixExpression, double *value) {
    *value = -1;
    Stack* stack = createStack(sizeof(double));
    while(*postfixExpression != '\0') {
        char ch = *postfixExpression;
        if(isdigit(ch)) {
            double i = ch - '0';
            while(isdigit(*(postfixExpression+1))){
                postfixExpression++;
                i = i * 10 + (*postfixExpression) - '0';
            }
            push(stack, &i);
        } else {
            if (ch == '+'){
                *value = *(double *)pop(stack) + *(double *)pop(stack);
                push(stack,value);
            } else if (ch == '-') {
                double t = *(double *)pop(stack);
                *value = *(double *)pop(stack) - t;
                push(stack,value);
            } else if (ch == '/') {
                double t = *(double *)pop(stack);
                *value = 1.0 * *(double *)pop(stack) / t;
                push(stack,value);
            } else if (ch == '*') {
                *value = 1.0 * *(double *)pop(stack) * *(double *)pop(stack);
                push(stack,value);
            }
        }
        postfixExpression++;
    }
    return 1;
}