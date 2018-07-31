#include "sequentialStack.h"

int main() {
    char testdata[] = "helloworldthisisatestprogram";
    printf("sizeof testdata is %d\n",sizeof(testdata));
    SqStack *s = (SqStack *)malloc(sizeof(SqStack));
    InitStack(s);
    for (int i=0; i<100; ++i) {
        Push(s, testdata[i]);
    }
    display(s);
    DestroyStack(s);
    s=NULL;
    return 0;
}