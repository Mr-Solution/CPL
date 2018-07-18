/*************************************************************************
	> File Name: main.c
    > Description: linear stack
    > Author: libo
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 19时31分15秒
 ************************************************************************/

#include <stdio.h>
#include "sequentialStack.h"

typedef int ElemType;

int main() {
    STACK *sk = create_stack(10, sizeof(ElemType));
    void *vp = NULL;
    for (int i = 1; i <= 10024; ++i) {
        vp = (void *)&i;
        push(sk, vp, sizeof(ElemType));
        printf("stack size : %d  len : %d\n",stack_size(sk), sk->top+sk->free+1);
    }

    void *elem = NULL;
    size_t elem_size;
    char *c = NULL;
    int *id = NULL;
    float *f = NULL;
    double *d = NULL;

    while(!isEmpty(sk)) {
        elem = pop(sk, &elem_size);
        printf("%x\n",elem);
        if (1 == elem_size) {
            c = (char *)elem;
            printf("pop %c\n", *c);
        }
        else if (4 == elem_size) {
            id = (int *)elem;
            printf("pop %d\n", *id);
        }
        else {
            d = (double *)elem;
            printf("pop %lf\n", *d);
        }
    }
    clear(sk);
    dispose_stack(sk);
    return 0;
}
