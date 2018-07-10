#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seqstack.h"

Stack *resize(Stack* stack) {

	printf("the capacity of the stack is %d and the stack is full! \n", getSize(stack));
	printf("now resize the stack, the new capacity is %d\n", 2*stack->capacity);

	Element* new = (Element *)malloc(sizeof(Element)*2*stack->capacity);
	memcpy(new, stack->data, stack->capacity * sizeof(Element));
	Element* tmp = stack->data;
	stack->data = new;
	free(tmp);
	return stack;
}

int isEmpty(Stack *stack) {
	return stack->top < 0;
}

int isFull(Stack *stack) {
	return stack->capacity == (stack->top + 1);
}

int getSize(Stack *stack) {
	return stack->top+1;
}

void push(Stack *stack, Element e) {
	if (isFull(stack)) {
		stack = resize(stack);
	}
	stack->data[++stack->top] = e;
}




Stack* createStack() {
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->data = (Element *)malloc(sizeof(Element)*INIT_SIZE);
	stack->capacity = INIT_SIZE;
	stack->top = -1; 
	return stack;
}


Element pop(Stack *stack) {
	if (isEmpty(stack)) {
		printf("Empty!\n");
	}
	return stack->data[stack->top--];
}

/***/
void traval(Stack *stack) {
	while (stack->top >= 0) {
		printf("%d\t", pop(stack));
	}
	printf("\n");
}
/**/
void main() {
	Stack *stack = createStack();
	int n = 5;
	for (int i = 0; i < n; ++i)	{
		push(stack, i);
	}
	printf("the size of stack is %d\n", getSize(stack));
	traval(stack);
	printf("the size of stack is %d\n", getSize(stack));
	printf("%d\n", stack->data[1]);
	printf("%d\n", stack->data[2]);
	printf("%d\n", stack->data[3]);
	printf("%d\n", stack->data[0]);
}