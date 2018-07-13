typedef int Element;

typedef struct Queue{
	Element *data;
	int front;
	int rear;
	int capacity;
	// int flag;
}Queue;

#define QUEUE_SIZE 4


int getSize(Queue *queue);
int isFull(Queue *queue);
int isEmpty(Queue *queue);
Queue* createQueue();
void enqueue(Queue *queue, Element e);
Element dequeue(Queue *queue);
void show(Queue *queue);
