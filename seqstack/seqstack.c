#include <stdio.h>
#include <stdlib.h>


#include "seqstack.h"

Stack *resize(Stack* stack) {

	printf("the capacity of the stack is %d and the stack is full! \n", getSize(stack));
	printf("now resize the stack, the new capacity is %d\n", 2*stack->capacity);
	stack->capacity *= 2;
	void* new = malloc(sizeof(stack->data_size)*2*stack->capacity);
	memcpy(new, stack->data, stack->capacity * sizeof(stack->data_size));
	void* tmp = stack->data;
	stack->data = new;
	free(tmp);
	return stack;
}

int isEmpty(Stack *stack) {
	return stack->top < 0;
}

int isFull(Stack *stack) {
	return stack->capacity <= (stack->top + 1);
}

int getSize(Stack *stack) {
	return stack->top+1;
}

void push(Stack *stack, void *e) {
	if (isFull(stack)) {
		stack = resize(stack);
	}
	++stack->top;
	memcpy(stack->data+(stack->top)*stack->data_size, e, stack->data_size);
}




Stack* createStack(size_t data_size) {
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->data = malloc(sizeof(data_size)*INIT_SIZE);
	stack->capacity = INIT_SIZE;
	stack->top = -1; 
	stack->data_size = data_size;
	return stack;
}


void *pop(Stack *stack) {
	if (isEmpty(stack)) {
		printf("Empty!\n");
	}
	void *e = stack->data + stack->top * stack->data_size;
	stack->top--;
	return e;
}

/***/
// void traval(Stack *stack) {
// 	while (stack->top >= 0) {
// 		printf("%d\t", pop(stack));
// 	}
// 	printf("\n");
// }
/**/
// void main() {

// 	Stack *stack = createStack(sizeof(int));
// 	// int n = 5;
// 	for (int i = 33; i > 0; --i)	{
// 		push(stack, &i);		
// 	}
// 	printf("the size of stack is %d\n", getSize(stack));
// 	// traval(stack);
// 	printf("the size of stack is %d\n", getSize(stack));

// 	while(!isEmpty(stack)){
// 		printf("pop %d\t", *(int *)pop(stack));
// 	}
	
// 	// int i = 0;
// 	// for (int i = 0; i < 5; ++i) {
// 	// 	printf("%d\t", *(int *)pop(stack));
// 	// }
// 	printf("\n");
// 	// printf("%d\n", ()stack->data[1]);
// 	// printf("%d\n", stack->data[2]);
// 	// printf("%d\n", stack->data[3]);
// 	// printf("%d\n", stack->data[0]);
// }