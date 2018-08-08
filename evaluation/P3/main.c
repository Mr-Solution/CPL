//
//
//  Stage 4
//  main.c
//  infixToPostfixExpressionV4
//
//  Created by williamzhuuestc on 2018/8/7.
//  Copyright © 2018年 williamzhuuestc. All rights reserved.
//



#include "expressionEvaluation.h"

#define properTestNumbers 52
#define improperTestNumbers 52
#define newProperTestNumbers 35
#define newImproperTestNumbers 101
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
        "-5/(   -3)",
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
        "  /5 ",
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
        "(2) 911"
    };
    
    char newProperInfixExpressions[newProperTestNumbers][infixLength]= {
        "7 *(5+6)",
        "( 5 ) / (7)",
        "(34)",
        "((8))",
        "(+7)",
        "(-8)",
        "(8*9)",
        "(1/4)",
        "+4+5",
        "+4-3",
        "+5*2",
        "+4/3",
        "-2+3",
        "-2-5",
        "-2*6",
        "-3/8",
        "2*3+5",
        "2*3-5",
        "2*3*4",
        "2*3/60",
        "2/4+5",
        "20/4*5",
        "20/4/4",
        "(2+3)",
        "(2-3)",
        "(2*3)",
        "(2/3)",
        "(3) -89",
        "6 +9",
        "0068",
        "1+2+3",
        "1+2-3",
        "1+2*3",
        "1+2/3",
        "((5))"
    };
    
    char newImproperInfixExpressions[newImproperTestNumbers][infixLength]= {
        "7 (5+6)",
        "( 5 ) (7)",
        "()",
        "(8))",
        "79)",
        "+)",
        "-)",
        "*)",
        "7*)",
        "/)",
        "8/)",
        "++",
        "1++",
        "+2+",
        "1+2+",
        "+-",
        "1+-",
        "+2-",
        "1+2-",
        "+*",
        "1+*",
        "+2*",
        "1+2*",
        "+/",
        "1+/",
        "+2/",
        "1+2/",
        "-+",
        "1-+",
        "-2+",
        "1-2+",
        "--",
        "1--",
        "-2-",
        "1-2-",
        "-*",
        "1-*",
        "-2*",
        "1-2*",
        "-/",
        "1-/",
        "-2/",
        "1-2/",
        "*+",
        "1*+",
        "*2+",
        "1*2+",
        "*-",
        "1*-",
        "*2-",
        "1*2-",
        "**",
        "1**",
        "*2*",
        "1*2*",
        "*/",
        "1*/",
        "*2/",
        "1*2/",
        "/+",
        "5/+",
        "/6+",
        "5/6+",
        "/-",
        "6/-",
        "/7-",
        "6/7-",
        "/*",
        "7/*",
        "/8*",
        "7/8*",
        "//",
        "8//",
        "/9/",
        "8/9/",
        "(+ ",
        "+(+ ",
        "-(+ ",
        "(-",
        "+(-",
        "-(-",
        "(*",
        "+(*",
        "-(*",
        "(/",
        "+(/",
        "-(/",
        ") 89",
        "+ ) 89",
        "- ) 89",
        "6 9",
        "+6 9",
        "-6 9",
        " *6 9",
        " /6 9",
        "Hello",
        "1+2+",
        "1+2-",
        "1+2*",
        "1+2/",
        "((5)"
    };
    
    
    char postfixExpression[infixLength];
    double value;
    
    printf("----***   The followings are tests for PROPER prefix expressions.    ***---\n\n");
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
    
    printf("----***   The followings are tests for IMPROPER prefix expressions.    ***---\n\n");
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
    
    printf("----***   The followings are tests for NEW PROPER prefix expressions.    ***---\n\n");
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
    
    printf("----***   The followings are tests for NEW IMPROPER prefix expressions.    ***---\n\n");
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

