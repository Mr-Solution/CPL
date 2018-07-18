//
//  main.c
//  InfixToPostfixV1
//
//  Created by williamzhuuestc on 2018/7/3.
//  Copyright © 2018年 williamzhuuestc. All rights reserved.
//

#include "expressionEvaluation.h"

#define testNumbers 4
#define infixLength 100

int main(int argc, const char * argv[]) {
    char properInfixExpressions[testNumbers][infixLength]= {
        "23+(58-41+33-25*8/4/2*12/3)/(49+1)",
        "2-(5+5*4+3*2-1)/(27+3*1)",
        "4*3+(10*4+6*2+8)/(52-2+10)-2",
        "3/2"
    };
    
    char postfixExpression[infixLength];
    double value;
    
    for (int i = 0; i < testNumbers; i++) {
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
            printf("Sorry, we can't turn such an infix expressin to a postfix expression.");
        }
        printf("----------------------------------------------------------------\n\n");
    }
    
    return 0;
}


