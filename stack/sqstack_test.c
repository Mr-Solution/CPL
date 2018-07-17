/*************************************************************************
	> File Name: main.c
    > Description: linear stack
    > Author: libo
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 19时31分15秒
 ************************************************************************/

#include <stdio.h>
#include "sqstack.h"

int main() {
    STACK *sk = creat_stack(10);
    /* 
     * 入栈出栈测试, 将10024个整型变量压入栈
     * 栈可以动态扩容至10000
     * */
    for (int i = 1; i <= 10024; ++i) {
        push(sk, i);
    }
    ElemType ret;
    while(!isEmpty(sk)) { 
        ret = pop(sk);
        printf("pop %0.0f\n",ret);
    }
    clear(sk);

    /* 读取FLAME.txt 中的数据，倒序输入至data.txt 中 */
    FILE *fpRead = fopen("FLAME.txt","r");
    if (NULL == fpRead) {
        printf("open file err\n");
        return 0;
    }
    FILE *fpWrite = fopen("data.txt","w");
    if (NULL == fpWrite) {

        printf("write file err\n");
        return 0;
    }
    ElemType buf;  //读取文件中的数据
    while (!feof(fpRead)) {
        fscanf(fpRead,"%f ", &buf);
        push(sk, buf);
    }
    ElemType ret1,ret2,ret3;
    while(!isEmpty(sk)) { 
        ret1 = pop(sk);
        ret2 = pop(sk);
        ret3 = pop(sk);
        fprintf(fpWrite, "%0.2f ", ret3);
        fprintf(fpWrite, "%0.2f ", ret2);
        fprintf(fpWrite, "%0.0f\n", ret1);
    }
    fclose(fpRead);
    fclose(fpWrite);
    dispose_stack(sk);
    return 0;
}
