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
 * 格式化字符串s，去空格，负数变为0减正数，正数去+
 * */
int format(char *s);
/*
 * 是否是运算符：+ - * /
 * */
int isoperator(char c);
/*
 * 从s中提取操作数(数字和小数点)到t中
 * */
int extract_operand(char *s, char *t);
/*
 * 判断字符是否合法
 * */
int islegal(char c);
/*
 * return 运算符的优先级
 * */
int priority(char c);

#endif
