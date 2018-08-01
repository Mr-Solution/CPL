#include "sequentialStack.h"

/* This function turns a prefix expression stored in 'prefiExpression' into a postfix expression
   and stores it in 'postfixExpression'
   If everything is all right, RETURN 1; otherwise, RETURN 0
 */
int infixToPostfix(char *infixExpression,char postfixExpression[]);

/* This function computes the value of a postfix expression stored in 'postfixExpression'
 and stores the final value in 'value'
 If everything is all right, RETURN 1; otherwise, RETURN 0
 */
int computeValueFromPostfix(char *postfixExpression, double *value);


