/*************************************************************************
	> File Name: sqlist_test.c
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 11时17分45秒
 ************************************************************************/

#include <stdio.h>
#include "sqlist.h"

int main() {
    SqList *sl = creat_list_sq();
    for (int i=0; i<100; ++i) {
        insert_list_sq(sl, i);
    }
    traversal(sl);
/*    for (int j=0; j < 200; ++j) {
        insert_list_sq(sl, j+10000);
    }
    */
    int len = get_buf_len(sl);
    int index = len/2;
    insert_list_sq_at(sl, index, len);
    traversal(sl);
    int data = 0;
    remove_from_list_sq(sl, index-1, &data);
    traversal(sl);
    printf("data = %d\n",data);
    return 0;
}
