#include "sequentialStack.h"


/* This function turns a prefix expression stored in 'prefiExpression' into a postfix expression
   and stores it in 'postfixExpression'
   If everything is all right, RETURN SUCCEEDED; otherwise, RETURN FAILED
 */
State infixToPostfix(char *infixExpression,char postfixExpression[]);

/* This function computes the value of a postfix expression stored in 'postfixExpression'
 and stores the final value in 'value'
 If everything is all right, RETURN SUCCEEDED; otherwise, RETURN FAILED
 */
State computeValueFromPostfix(char *postfixExpression, double *value);


