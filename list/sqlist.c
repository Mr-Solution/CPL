/*************************************************************************
	> File Name: sqlist.c
    > Description: 线性表的顺序存储
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月09日 星期一 10时55分48秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlist.h"

#define MAX_LEN 100

SqList *creat_list_sq() {
    SqList *sl = (SqList *)malloc(sizeof(SqList));
    sl->len = 0;
    sl->free = MAX_LEN;
    sl->buf = (ElemType *)malloc(sizeof(ElemType)*sl->free);
    return sl;
}

int get_buf_len(SqList *sl) {
    if (NULL == sl)
        return 0;
    return sl->len;
}

int expand_buf_size(SqList *sl) {
    if (sl->free >= sl->len) {
        printf("there is no need to expand the buf size\n");
        return 0;
    }
    ElemType *new_buf = (ElemType *)malloc(sizeof(ElemType)*(sl->len)*2);
    memcpy(new_buf, sl->buf, sl->len * sizeof(ElemType));
    free(sl->buf);
    sl->buf = new_buf;
    sl->free = sl->len;
    return 0;
}

int insert_list_sq_at(SqList *sl, int index, ElemType val) {
    if (sl->free < 1) {
        expand_buf_size(sl);
    }
    if (index > sl->len || index < 0) {
        printf("Err, insert position wrong!\n");
        return 0;
    }
    for (int i=sl->len; i>index; --i) {
        sl->buf[i] = sl->buf[i-1];
    }
    sl->buf[index] = val;
    ++sl->len;
    --sl->free;
    return 0;
}

int insert_list_sq(SqList *sl, ElemType val) {
    if (sl->free < 1) {
        expand_buf_size(sl);
    }
    sl->buf[sl->len] = val;
    ++sl->len;
    --sl->free;
    return 0;
}

int remove_from_list_sq(SqList *sl, int index, ElemType *data) {
    if (0 == sl->len) {
        printf("err! there is no data in the buf.\n");
        return 0;
    }
    if (index > sl->len || index < 0) {
        printf("err! the index is wrong.\n");
        return 0;
    }
    *data = sl->buf[index];
    for (int i=index; i<sl->len; ++i) {
        sl->buf[i] = sl->buf[i+1];
    }
    --sl->len;
    ++sl->free;
    return 0;
}

void traversal(SqList *sl) {
    printf("****** traversal begin ******\n");
    for (int i=0; i<sl->len; ++i) {
        printf("%d  ",sl->buf[i]);
    }
    printf("\n****** traversal end ******\n");
}

void del_list_sq(SqList *sl) {
    sl->free += sl->len;
    sl->len = 0;
    free(sl->buf);
    sl->buf = NULL;
    free(sl);
    sl=NULL;
}
