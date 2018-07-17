#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedstack.h"


int isEmpty(Stack *stack) {
	return stack->size <= 0;
}


int getSize(Stack *stack) {
	return stack->size;
}

void push(Stack *stack, Element e) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->val = e;
	node->next = stack->top;
	stack->top = node;
	stack->size++; 
}


Stack* createStack() {
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->top = (Node *)malloc(sizeof(Node));
	stack->size = 0;
	return stack;
}


Element pop(Stack *stack) {
	if (isEmpty(stack))	{
		printf("the stack is empty\n");
		exit(-1);
	}
	Node *tmpn = stack->top;
	Element tmp = tmpn->val;
	stack->top = stack->top->next;
	free(tmpn);
	stack->size--;
	return tmp;
}

/**/
void main() {
	Stack *stack = createStack();
	push(stack,1);
	push(stack,6);
	push(stack,8);
	push(stack,3);
	push(stack,0);
	printf("the size of stack is %d\n", getSize(stack));
	
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));

	printf("the size of stack is %d\n", getSize(stack));
}