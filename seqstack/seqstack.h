typedef int Element;

typedef struct Stack{
	Element *data;
	int capacity;	/*	*/
	int top;	/* index the top  always have number */
}Stack;

#define INIT_SIZE 8

Stack *resize(Stack* stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
int getSize(Stack *stack);
void push(Stack *stack, Element e);
Stack* createStack();
Element pop(Stack *stack);
void traval(Stack *stack);





