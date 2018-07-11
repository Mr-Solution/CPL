/*************************************************************************
	> File Name: linkedlist.c
	> Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月10日 星期二 16时34分52秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LNODE *create_lnode(ElemType val) {
    LNODE *node;
    node = (LNODE *)malloc(sizeof(LNODE));
    node->val = val;
    node->next = NULL;
    return node;
}

LNODE *create_linkedlist() {
    LNODE *head;
    head = create_lnode(0);    //head指针val不存数据
    return head;
}

void insertHead(LNODE *head, ElemType val) {
    LNODE *node = create_lnode(val);
    node->next = head->next;
    head->next = node;
}

void insertTail(LNODE *head, ElemType val) {
    LNODE *p = head;
    LNODE *node = create_lnode(val);
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = node;
}

void insert(LNODE *head, int pos, ElemType val) {
    LNODE *p;
    p = head;
    int count = 0;
    while (p != NULL) {
        if (count == pos-1) {
            LNODE *node = create_lnode(val);
            node->next = p->next;
            p->next = node;
            break;
        }
        p = p->next;
        ++count;
    }
    if (count != pos-1) {
        printf("err! index %d is bigger than list-length\n",pos);
    }
}

void traversal(LNODE *head) {
    printf("traversal begin\n");
    LNODE *p;
    p = head->next;
    while (p != NULL) {
        printf("%d  ",p->val);
        p = p->next;
    }
    printf("\ntraversal end\n");
}
