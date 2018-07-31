#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
typedef int ElemType;

#define SizeOf(s) s->top+1;

#define CHECKPOINTER(p) do { \
    if(NULL==p) {\
        printf("err! illegal parameter, the pointer is NULL.\n"); \
        return 0; \
    } \
} while(0);


/*  Sequential stack to store char elements.
 */
typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack *s) {
    s->top = -1;
}

void DestroyStack(SqStack *s) {
    free(s);
}

int main() {
    SqStack *s = (SqStack *)malloc(sizeof(SqStack));
    CHECKPOINTER(s);
    InitStack(s);
    int ssize = SizeOf(s);
    printf("%d\n", ssize);
    for (int i = 0; i< 10; i++) {
        s->top ++;
        if (s->top > 3) {
            ssize = SizeOf(s);
            printf("%d\n", ssize);
        }
    }

    DestroyStack(s);
    s = NULL;
    if (1) {CHECKPOINTER(s);}
    
    return 0;
}