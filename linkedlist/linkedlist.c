#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int size = 0;

Node* creatLinkedList(int n){
	Node *head = (Node *)malloc(sizeof(Node));
	head->data = 9;
	size ++;
	Node *iter = head;
	int i = 0;
	while (i++ < n) {
		Node *node = (Node *)malloc(sizeof(Node));
		node->data = i * 5;
		iter->next = node;
		iter = iter->next;
		size++;
	}
	iter->next = NULL;
	return head;
}


void traval(Node *iter){
	while(iter){
		printf("%d\t", iter->data);
		iter = iter->next;
	}
	printf("\n\n");
}

Node* insert(Node *head, int position, Element data){
	if (position > size || position < 0)
	{
		printf("iillegal!\n");
		exit(-1);
	}
	size++;
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = data;
	/* first or last or others */
	if (position == 0)
	{
		node->next = head;
		head = node;
		return head;	
	} 
	Node *iter = head;
	while (position-- > 1){
		iter = iter->next;
	}
	if (iter->next == NULL)	{
		node->next = NULL;
		iter->next = node;
	}else{
		node->next = iter->next;
		iter->next = node;}
	return head;
}

Node* insertAtHead(Node* head, Element data){
	return insert(head,0,data);
}

Node* insertAtTail(Node* head, Element data){
	return insert(head,size,data);
}

Node* delete(Node* head, int position){
	if (position<0||position>size-1||size<=0)
	{
		printf("iillegal\n");
		exit(-1);
	}
	size --;
	Node* iter = head;
	/* delete the head node */
	if (position == 0)	
	{
		iter = head->next;
		head->next = NULL;
		free(head);
		return iter;
	}
	while(position-->1){
		iter = iter->next;
	}
	Node* tmp = iter->next;
	iter->next = tmp->next;
	tmp->next = NULL;
	free(tmp);
	return head;
}

Node *deleteAtHead(Node* head){
	delete(head, 0);
}

Node *deleteAtTail(Node* head){
	delete(head, size-1);
}

int getsize(){
	return size;
}


int main() {
	Node* head = creatLinkedList(5);
	traval(head);
	head = insert(head,5,456);
	traval(head);
	head = insertAtHead(head, 555);
	head = insertAtTail(head, 55995);
	traval(head);
	head = delete(head,0);
	traval(head);
	printf("%d\n", size);

	head = delete(head,7);
	traval(head);
	printf("%d\n", size);

	return 0;
}

