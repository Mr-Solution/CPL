<<<<<<< HEAD
#include <string.h>

// typedef int Element;

typedef struct Stack{
	size_t data_size;
	void *data;
=======
typedef int Element;

typedef struct Stack{
	Element *data;
>>>>>>> 2a749424c409a67c24a882ef72d453108ef1863c
	int capacity;	/*	*/
	int top;	/* index the top  always have number */
}Stack;

#define INIT_SIZE 8

Stack *resize(Stack* stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
int getSize(Stack *stack);
<<<<<<< HEAD
void push(Stack *stack, void *e);
Stack* createStack(size_t data_size);
void *pop(Stack *stack);
// void traval(Stack *stack);
=======
void push(Stack *stack, Element e);
Stack* createStack();
Element pop(Stack *stack);
void traval(Stack *stack);
>>>>>>> 2a749424c409a67c24a882ef72d453108ef1863c





