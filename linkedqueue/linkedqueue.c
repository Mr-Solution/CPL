#include "linkedqueue.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
	Queue *queue = createQueue();
	enqueue(queue, 33);
	enqueue(queue, 34);
	enqueue(queue, 35);
	enqueue(queue, 36);
	show(queue);
	printf("the size of the queue is %d\n", getSize(queue));
	printf("dequeue : %d\n", dequeue(queue));
	printf("dequeue : %d\n", dequeue(queue));
	printf("dequeue : %d\n", dequeue(queue));
	printf("dequeue : %d\n", dequeue(queue));
	printf("the size of the queue is %d\n", getSize(queue));
	return 0;
}

int getSize(Queue *queue) {
	return queue->size;
}

int isEmpty(Queue *queue) {
	return queue->size <= 0;
}


Queue* createQueue() {
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->front = (Node *)malloc(sizeof(Node));
	queue->rear = queue->front;
	queue->size = 0;
	return queue;
}

void enqueue(Queue *queue, Element e) {
	Node* node = (Node *)malloc(sizeof(Node));
	node->val = e;
	queue->rear->next = node;
	queue->rear = node;
	queue->size++;
}


Element dequeue(Queue *queue) {
	Node *tmp = queue->front->next;
	Element e = tmp->val;
	queue->front->next = queue->front->next->next;
	free(tmp);
	queue->size--;
	return e;
}

void show(Queue *queue) {
	printf("----------------\n");
	printf("the size of queue is %d\n", queue->size);
	Node *iter = queue->front->next;
	while (iter != NULL) {
		printf("%d\t", iter->val);
		iter = iter->next;
	}
	printf("\n----------------\n");
}

int destroy(Queue *queue){
	return 0;
}