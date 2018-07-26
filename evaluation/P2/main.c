//
//  main.c
//  infixToPostfixExpressionV2
//
//  Created by williamzhuuestc on 2018/7/15.
//  Copyright © 2018年 williamzhuuestc. All rights reserved.
//

#include "expressionEvaluation.h"

#define properTestNumbers 10
#define inproperTestNumbers 16
#define infixLength 100

int main(int argc, const char * argv[]) {
    char properInfixExpressions[properTestNumbers][infixLength]= {
        "23+(58-41+33-25*8/4/2*12/3)/(49+1)",
        "2-(5+5*4+3*2-1)/(27+3*1)",
        "4*3+(10*4+6*2+8)/(52-2+10)-2",
        "3/2",
        
        "4 * 3 + ( 10 * 4 + 6 * 2 + 8) / ( 52       - 2 + 10 ) - 2",
        "5",
        " 62 ",
        "(5)",
        " ( 62  )",
        "23 + ( 58 – 41 +   33 – 25 * 4) / (49 + 1 )"
    };
    
    char improperInfixExpressions[inproperTestNumbers][infixLength]= {
          //empty expressions
        "",
        " ",
        "  ",
        "      ",
          //spaces
        " 6 2 ",
          //insufficient operands
        " + ",
        " 6 * 3 - ",
        " 6+4*2/ ",
        " 6++4*2/ ",
        " 6+-4*2/ ",
          //improper braces
        " 5) ",
        " ( 62   ",
        " ) 713 (   ",
          //illegal character
        " a ",
        " 5 + b   ",
        " 3 x 4 + 5   "
    };
    
    char postfixExpression[infixLength];
    double value;
    
     printf("----***   The following are tests for PROPER prefix expressions.    ***---\n\n");
    for (int i = 0; i < properTestNumbers; i++) {
        printf("---------------------***   Test %d    ***------------------------\n\n", i + 1);
        printf("The infix expression:%s\n", properInfixExpressions[i]);
        if (infixToPostfix(properInfixExpressions[i], postfixExpression) == 1){
            printf("The postfix expression:%s\n", postfixExpression);
            if (computeValueFromPostfix(postfixExpression, &value) == 1)
            printf("The value of the expression:%g\n\n", value);
            else
            printf("Sorry, we can't evaluate such a postfix expression.");
        }
        else{
            printf("Sorry, we can't turn such an infix expressin to a postfix expression.\n");
        }
        printf("----------------------------------------------------------------\n\n");
    }
    printf("-----***   End of tests for PROPER prefix expressions.    ***-----\n\n\n");
    
    printf("----***   The following are tests for IMPROPER prefix expressions.    ***---\n\n");
    for (int i = 0; i < inproperTestNumbers; i++) {
        
        printf("---------------------***   Test %d    ***------------------------\n\n", i + 1);
        printf("The infix expression:%s\n", improperInfixExpressions[i]);
        if (infixToPostfix(improperInfixExpressions[i], postfixExpression) == 1){
            printf("The postfix expression:%s\n", postfixExpression);
            if (computeValueFromPostfix(postfixExpression, &value) == 1)
            printf("The value of the expression:%g\n\n", value);
            else
            printf("Sorry, we can't evaluate such a postfix expression.\n");
        }
        else{
            printf("Sorry, we can't turn such an infix expressin to a postfix expression.\n");
        }
        printf("----------------------------------------------------------------\n\n");
    }
    printf("-----***   End of tests for IMPROPER prefix expressions.    ***-----\n\n\n");
    
    return 0;
}

