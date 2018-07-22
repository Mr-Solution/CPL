/*************************************************************************
	> File Name: expressionEvaluation.h
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 16/07/2018 - 16:49
 ************************************************************************/

#ifndef EXPRESSIONEVALUATION_H_
#define EXPRESSIONEVALUATION_H_

#include <stdio.h>

int infixToPostfix(char *infixExpression, char postfixExpression[]);

int computeValueFromPostfix(char *postfixExpression, double *value);

/*
 * 去掉数字和字符之间的空格
 * */
int strip(char *s);
/*
 * 是否是运算符：+ - * /
 * */
int isoperator(char c);
/*
 * 是否是操作数,数字和小数点
 * */
int isoperand(char c);
/*
 * 判断字符是否合法
 * */
int islegal(char c);
/*
 * return 运算符的优先级
 * */
int priority(char c);

#endif
