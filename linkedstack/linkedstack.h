typedef int Element;

typedef struct Node{
	Element val;
	struct Node *next;
}Node;

typedef struct Stack{
	Node *top;
	int size;
}Stack;



#define INIT_SIZE 8

int isEmpty(Stack *stack);
int getSize(Stack *stack);
void push(Stack *stack, Element e);
Stack* createStack();
Element pop(Stack *stack);





