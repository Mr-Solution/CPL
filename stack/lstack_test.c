/*************************************************************************
	> File Name: lstack_test.c
	> Description: linked stack test
    > Author: libo
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 22时15分45秒
 ************************************************************************/

#include <stdio.h>
#include "lstack.h"

int main() {
    STACK *sk = creat_stack(10);
    printf("please input three integer:\n");
    int x,y,z;
    scanf("%d %d %d",&x,&y,&z);
    
    push(sk, x);
    push(sk, y);
    push(sk, z);
    int current_size = size(sk);
    printf("the size of the stack is : %d\n", current_size);
    int val = 0;
    int ret = 0;
    for (int i=0; i<current_size; ++i) {
        ret = pop(sk, &val);
        if (0 == ret)
            printf("%d\n",val);
        else
            printf("pop err!\n");
    }
    printf("the size of the stack is : %d\n",size(sk));
    
    dispose_stack(sk);
    return 0;
}
