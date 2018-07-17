#include "seqqueue.h"
#include <stdio.h>
#include <stdlib.h>


Queue* createQueue() {
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->data = (Element *)malloc(sizeof(Element)*QUEUE_SIZE);
	queue->capacity = QUEUE_SIZE;
	queue->rear = -1;
	queue->front = 0;
}

int getSize(Queue *queue) {
	return queue->rear - queue->front + 1;
	
}

int isFull(Queue *queue) {
	return getSize(queue) >= queue->capacity;
}

int isEmpty(Queue *queue) {
	return getSize(queue) <= 0;
}

void enqueue(Queue *queue, Element e) {
	if(isFull(queue)) {
		printf("the queue is full!\n");
		return;
	}
	printf("enqueue     %d\n", e);
	/* the number of front is continue, the position is internal */
	queue->data[(++queue->rear)%queue->capacity] = e;

}

Element dequeue(Queue *queue) {
	if (isEmpty(queue)) {
		printf("the queue is empty\n");
		return NULL;
	}
	return queue->data[(queue->front++)%queue->capacity];
}

// void show(Queue *queue) {
// 	printf("--------------------\n");
// 	printf("front index is %d\n", queue->front);
// 	printf("rear index is %d\n", queue->rear);
// 	printf("the queue contains \n");
// 	for (int i = 0; i < queue->capacity; i++) {
// 		printf("%d\t", queue->data[i]);
// 	}
// 	printf("\n--------------------\n");
// 	printf("\n");
// }


void main(int argc, char const *argv[]) {
	Queue *queue = createQueue();
	
	enqueue(queue, 1);
	enqueue(queue, 3);
	enqueue(queue, 6);
	enqueue(queue, 7);

	enqueue(queue, 7);
	printf("dequeue-----%d\n", dequeue(queue));
	printf("dequeue-----%d\n", dequeue(queue));

	enqueue(queue, 9);
	enqueue(queue, 11);

	printf("the size of queue is %d\n", getSize(queue));

	printf("dequeue-----%d\n", dequeue(queue));
	printf("dequeue-----%d\n", dequeue(queue));
	printf("dequeue-----%d\n", dequeue(queue));
	printf("dequeue-----%d\n", dequeue(queue));
	printf("the size of queue is %d\n", getSize(queue));
	printf("dequeue %d\n", dequeue(queue));

	show(queue);

	enqueue(queue, 1);
	enqueue(queue, 3);
	enqueue(queue, 6);
	enqueue(queue, 7);

	enqueue(queue, 7);
	printf("dequeue-----%d\n", dequeue(queue));
	printf("dequeue-----%d\n", dequeue(queue));

	enqueue(queue, 9);
	enqueue(queue, 11);

	printf("the size of queue is %d\n", getSize(queue));

	printf("dequeue-----%d\n", dequeue(queue));
	printf("dequeue-----%d\n", dequeue(queue));
	printf("dequeue %d\n", dequeue(queue));
	printf("dequeue %d\n", dequeue(queue));
	printf("the size of queue is %d\n", getSize(queue));
	printf("dequeue-----%d\n", dequeue(queue));

	return 0;
}