/*************************************************************************
	> File Name: linkedlist.h
	> Description: 链接表
    > Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月10日 星期二 16时04分36秒
 ************************************************************************/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef int ElemType;

typedef struct node {
    ElemType val;
    struct node *next;
} LNODE;

/*
 * 创建一个节点，val=val
 * */
LNODE *create_lnode(ElemType val);

/*
 * 创建一个单链表
 * */
LNODE *create_linkedlist();

void insertHead(LNODE *head, ElemType val);

void insertTail(LNODE *head, ElemType val);

void insert(LNODE *head, int post, ElemType val);

void traversal(LNODE *head);

#endif
