/*************************************************************************
	> File Name: main.c
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 19时31分15秒
 ************************************************************************/

#include <stdio.h>
#include "sqstack.h"

int main() {
    STACK *sk = creat_stack(10);
    int x,y,z;
    scanf("%d %d %d",&x,&y,&z);
    push(sk, x);
    push(sk, y);
    push(sk, z);

    for (int i = 1; i < 100000; ++i) {
        push(sk, i);
    }

    int ret;

    while(!isEmpty(sk)) { ret = pop(sk);
        printf("pop %d\n",ret);
    }
    dispose_stack(sk);
    return 0;
}
