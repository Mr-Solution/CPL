typedef int Element;

typedef struct Node{
	Element val;
	struct Node *next;
}Node;


typedef struct Queue{
	Node *front;
	Node *rear;
	int size;
}Queue;



int getSize(Queue *queue);

int isEmpty(Queue *queue);
Queue* createQueue();
void enqueue(Queue *queue, Element e);
Element dequeue(Queue *queue);
void show(Queue *queue);

