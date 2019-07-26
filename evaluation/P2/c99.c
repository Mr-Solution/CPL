/*************************************************************************
    > File Name: c99.c
    > Author: reeves
    > Mail: seereeves@163.com 
    > Created Time: 26/07/2018 - 16:29
 ************************************************************************/

#include <stdio.h>
int main() {
#ifdef __STDC__
    printf("%s\n", "stardard C");
#endif
#ifdef __STDC_VERSION__
    printf("%d\n", __STDC_VERSION__);
#endif
    return 0;
}
