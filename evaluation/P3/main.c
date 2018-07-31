//
//
//  Stage 3
//  main.c
//  infixToPostfixExpressionV3
//
//  Created by williamzhuuestc on 2018/7/28.
//  Copyright © 2018年 williamzhuuestc. All rights reserved.
//



#include "expressionEvaluation.h"

#define properTestNumbers 10
#define improperTestNumbers 16
#define newProperTestNumbers 7
#define newImproperTestNumbers 6
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
        "23 + ( 58 -41 + 33 -25 *4)/ (49 + 1)"
    };
    
    char improperInfixExpressions[improperTestNumbers][infixLength]= {
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
    
    char newProperInfixExpressions[newProperTestNumbers][infixLength]= {
        "  -5 ",
        "  +5   ",
        "-(-5)",
        "-(3)",
        "+(-5)",
        "-(+3)",
        "1+2-(6 ) "
    };
    
    char newImproperInfixExpressions[newImproperTestNumbers][infixLength]= {
        "  - 5 ",
        "  + 5   ",
        "  --5 ",
        "  ++5   ",
        " - (-5) ",
        " - (+3) "
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
            printf("Sorry, we can't turn such an infix expression to a postfix expression.");
        }
        printf("----------------------------------------------------------------\n\n");
    }
    printf("-----***   End of tests for PROPER prefix expressions.    ***-----\n\n\n");
    
    printf("----***   The following are tests for IMPROPER prefix expressions.    ***---\n\n");
    for (int i = 0; i < improperTestNumbers; i++) {
        
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
    
    printf("----***   The following are tests for NEW PROPER prefix expressions.    ***---\n\n");
    for (int i = 0; i < newProperTestNumbers; i++) {
        printf("---------------------***   Test %d    ***------------------------\n\n", i + 1);
        printf("The infix expression:%s\n", newProperInfixExpressions[i]);
        if (infixToPostfix(newProperInfixExpressions[i], postfixExpression) == 1){
            printf("The postfix expression:%s\n", postfixExpression);
            if (computeValueFromPostfix(postfixExpression, &value) == 1)
            printf("The value of the expression:%g\n\n", value);
            else
            printf("Sorry, we can't evaluate such a postfix expression.");
        }
        else{
            printf("Sorry, we can't turn such an infix expression to a postfix expression.");
        }
        printf("----------------------------------------------------------------\n\n");
    }
    printf("-----***   End of tests for NEW PROPER prefix expressions.    ***-----\n\n\n");
    
    printf("----***   The following are tests for NEW IMPROPER prefix expressions.    ***---\n\n");
    for (int i = 0; i < newImproperTestNumbers; i++) {
        
        printf("---------------------***   Test %d    ***------------------------\n\n", i + 1);
        printf("The infix expression:%s\n", newImproperInfixExpressions[i]);
        if (infixToPostfix(newImproperInfixExpressions[i], postfixExpression) == 1){
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
    printf("-----***   End of tests for NEW IMPROPER prefix expressions.    ***-----\n\n\n");
    return 0;
}

