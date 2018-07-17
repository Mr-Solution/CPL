#include "seqstack.h"
#include <stdio.h>
#include <stdlib.h>

int infixToPostfix(char *properInfixExpressions, char postfixExpression[]);
int computeValueFromPostfix(char *postfixExpression, double *value);
