/*************************************************************************
	> File Name: linkedlist_test.c
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月10日 星期二 19时17分26秒
 ************************************************************************/

#include <stdio.h>
#include "linkedlist.h"

int main() {
    LNODE *ll = create_linkedlist();
    if (ll != NULL) {
        for (int i=0; i<10; ++i) {
            insertHead(ll, i);
        }
        traversal(ll);
        printf("*****************************\n");
        for (int j=110; j<120; ++j) {
            insertTail(ll, j);
        }
        traversal(ll);
        printf("*****************************\n");
        insert(ll, 3, 999);
        traversal(ll);
    }
    else {
        printf("create err!\n");
    }

    return 0;
}
