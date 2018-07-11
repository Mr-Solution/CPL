/*************************************************************************
	> File Name: lstack_test.c
	> Description: linked stack test
    > Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 22时15分45秒
 ************************************************************************/

#include <stdio.h>
#include "lstack.h"

int main() {
    STACK *sk = creat_stack(10);
    int x,y,z;
    scanf("%d %d %d",&x,&y,&z);
    
    push(sk, x);
    push(sk, y);
    push(sk, z);

    int val = 0;
    int ret = pop(sk, &val);
    if (0 == ret)
        printf("%d\n",val);
    else
        printf("pop err!\n");

    dispose_stack(sk);
    return 0;
}
