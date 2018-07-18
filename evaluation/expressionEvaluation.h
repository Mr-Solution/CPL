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

int priority(char *c);

#endif
