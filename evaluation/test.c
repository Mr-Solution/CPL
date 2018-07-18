/*************************************************************************
    > File Name: test.c
    > Author: reeves
    > Mail: seereeves@163.com 
    > Created Time: 16/07/2018 - 16:59
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char *s = "23+(58-41+33-25*8/4/2*12/3) / (49+1)";
    int len = strlen(s);
    for (int i=0; i<len; ++i) {
        printf("%c\t",*(s+i));
        if (isdigit(*(s+i)))
            printf("%d\t",*(s+i));
        else
            printf("char\t");
        int ascii = *(s+i);
        printf("%d\n",ascii);
    }
    printf("\n");
    printf("sizeof char is : %d\n",sizeof(char));
    printf("sizeof int is : %d\n",sizeof(int));
    printf("sizeof float is : %d\n",sizeof(float));
    printf("sizeof double is : %d\n",sizeof(double));

    return 0;
}
