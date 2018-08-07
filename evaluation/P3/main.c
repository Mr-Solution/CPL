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
#include "string.h"
#include "stdlib.h"
#include "time.h"

#define properTestNumbers 37
#define improperTestNumbers 30
#define newProperTestNumbers 15
#define newImproperTestNumbers 22
#define infixLength 100

void test();
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
        "23 + ( 58 -41 + 33 -25 *4)/ (49 + 1)",
        
        "  -5 ",
        "  +5   ",
        "-(-5)",
        "-(3)",
        "+(-5)",
        "-(+3)",
        "1+2-(6 ) ",
        " +1+2+(6 ) ",
        " +1+   2-(6 ) ",
        "   +1+2*(6 ) ",
        "  +1+2 /(6 ) ",
        "+5+(3)",
        "+5-(3)",
        "+5*(3)",
        "+5/(3)",
        "-5+(3)",
        "-5-(3)",
        "-5*(3)",
        "-5/(3)",
        "+5+(+3)",
        "+5-(+3)",
        "+5*(+3)",
        "+5/(+3)",
        "-5+(    -3)",
        "-5-(   -3)",
        "-5*( -3)",
        "-5/(   -3)"
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
        " 3 x 4 + 5   ",
        // A space follows a unary operator
        "  - 5 ",
        "  + 5   ",
        " - (-5) ",
        " - (+3) ",
        //insufficient operands
        "  --5 ",
        "  ++5   ",
        "( )",
        "-1 + 5/( +2 + 3*4/12 -3)", //Zero divisor
        "+",
        "-",
        "*",
        "/",
        "  * 5 ",
        "  /5 "
    };
    
    char newProperInfixExpressions[newProperTestNumbers][infixLength]= {
        "3+( -5)",
        "08" ,
        " -5 / (-3) + (-6/2)*3  ",
        " -5 / ((+3*2) /(-1)- (-6/2)*3 ) ",
        "((((((((((3+1+1+1+1+1+1*3*5/6))))))))))/3+1   ",
        "( ((+18))*10  )   /      2",
        "-1200/(((12*((-12))/   12)))",
        "(9+8)*(3-2)",
        "(-2+9)/(8)",
        "-(1 -5/(-1)*(+1) + (-16))",
        "-(3*999+(((+2)*(-3))))",
        "-(       5*(  -3))",
        "(((-4)+3)*6)",
        "+2*4+(2/3) ",
        "(8*2) / (3+2)"
    };
    
    char newImproperInfixExpressions[newImproperTestNumbers][infixLength]= {
        " 3+( -  6)" ,
        "6(5+2)" ,
        "(5+2)  (8+5)",
        "(1+2) (4+5)",
        "*7+3-2 ",
        "  7+3-2*",
        "  (5+6)-(7+8)+(",
        " 2 ((3+2))",
        " (1+4)(3*7)",
        "( ((8+8))10  )",
        "8+(+)",
        "8+( )",
        "(9+8)9",
        "  (1*9+50-5)(5*6) ",
        "+(-5)*(-5*   -963)",
        "  +5+6-(7+  1(   +6 ))   ",
        "(4-3)(8*(-2))",
        "8(  )",
        "-(5*(      - 3))",
        "(8*2)  (3+2)",
        "9+(*9)    9",
        "(2+) *9",

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
            printf("Sorry, we can't turn such an infix expression to a postfix expression.\n");
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
    srand(time(0));
    test();
    return 0;
}

char character_set[]="0123456789+-*/.() ";
void test()
{
    for (int i = 0; i < 100; ++i)
    {
        // int len=10;
        char postfixExpression[infixLength];
        int len=strlen(character_set);
        char temp[20]={0};
        // 生成字符串
        for (int i = 0; i < 10; ++i)
        {
            int n=rand()%len;
            temp[i]=character_set[n];
        }
        double value=0;
        printf("string:%s\n", temp);
        if (infixToPostfix(temp, postfixExpression) == 1){
                    printf("The postfix expression:%s\n", postfixExpression);
                    if (computeValueFromPostfix(postfixExpression, &value) == 1)
                        printf("The value of the expression:%g\n\n", value);
                    else
                        printf("Sorry, we can't evaluate such a postfix expression.\n");
            }
            else{
                    printf("Sorry, we can't turn such an infix expressin to a postfix expression.\n");
        }
    }
    printf("all ok\n");
}