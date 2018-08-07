#include "sequentialStack.h"

int main() {
    char testdata[] = "helloworldthisisatestprogram";
    printf("sizeof testdata is %d\n",sizeof(testdata));
    SqStack *s = (SqStack *)malloc(sizeof(SqStack));
    InitStack(s);
    for (int i=0; i<100; ++i) {
        if(Push(s, testdata[i]))
            printf("push successed\n");
        else
            break;
    }
    display(s);
    char ch;
    printf("Pop\n");
    for (int i=0; i< 100; ++i) {
        if(Pop(s, &ch))
            printf("%c\n",ch);
        else
            break;
    }
    DestroyStack(s);
    s=NULL;
    return 0;
}