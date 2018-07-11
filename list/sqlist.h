/*************************************************************************
	> File Name: sqlist.h
	> Description: 线性表的顺序存储
    > Author: reeves
	> Mail: seereeves@163.com 
	> Created Time: 2018年07月07日 星期六 21时40分40秒
 ************************************************************************/

#ifndef SQLIST_H_
#define SQLIST_H_

typedef int ElemType; //存储单元数据类型

typedef struct {
    int len;        // 记录buf数组中已使用的长度
    int free;       // 记录buf数组中未使用的长度
    ElemType *buf; // 数组，用于保存数据
} SqList;

/*
 * 创建顺序表
 * */
SqList *creat_list_sq();

/*
 * 获取顺序表当前长度
 * */
int get_buf_len(SqList *sl);

/*
 * 扩展数组长度
 * */
int expand_buf_size(SqList *sl);

/*
 * 特定位置插入数据  index : 0~
 * */
int insert_list_sq_at(SqList *sl, int index, ElemType val);

/*
 * 表尾插入数据
 * */
int insert_list_sq(SqList *sl, ElemType val);

/*
 * 在顺序表中删除指定位置的元素
 * */
int remove_from_list_sq(SqList *sl, int index, ElemType *);

/*
 * 遍历顺序表
 * */
void traversal(SqList *sl);

/*
 * 删除顺序表
 * */
void del_list_sq(SqList *sq);

#endif  /* SQLIST_H_ */
