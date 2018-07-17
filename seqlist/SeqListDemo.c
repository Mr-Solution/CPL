#include <stdio.h>
#include <string.h>
#include "seqlist.h"
#include <stdlib.h>

int main(){
	int n = 9;
	SeqList *p = createSeqList(7);
	traversal(p);
	
	delete(p, 2);
	traversal(p);
	
	insert(p, 123, 2);
	traversal(p);
	
	int position = search(p, 3);
	printf("the position of number 3 is %d\n", position);

	for (int i = 0; i < 20000; ++i) {
		insert(p, i, i);
	}
	traversal(p);
	return 0;
}

SeqList *createSeqList(int n){
	SeqList *p = (SeqList *)malloc(sizeof(SeqList));
	int i = 1;
	while(i < n)	{i = i << 2;}
	p->size = i;
	p->data = (int *)malloc(sizeof(int)*i);
	p->current_len = n;
	for (int i = 0; i < n; ++i){
		p->data[i] = i;
	}
	printf("create your seq_list, the size of seq_list is %d\n", p->size);
	return p;
}

int insert(SeqList *s, Element i, int position){
	// printf("insert %d to SeqList s into %d\n", i, position);
	if (position < 0){
		printf("the position is illegal\n");
		exit(-1);
	}
	if (s->current_len+1 > s->size) {
		resize(s);
	}
	++s->current_len;
	for (int i = s->current_len; i > position; --i){
		s->data[i] = s->data[i-1];
	}
	s->data[position] = i;
	return 0;
}

void resize(SeqList *s){
	int new_size = 2 * (s->size);
	Element *new_data = (int *)malloc(sizeof(int)*new_size);
	if (NULL == new_data) {
	    printf("Memory allocation error\n");
	    exit(-1);
	}

	printf("the list is full, now resize the list\ncopy the list (old_size:%d) to new list (new_size:%d)\n",s->size, new_size);
	printf("-----------copy begin-----------\n");
	memcpy(new_data, s->data, s->size*sizeof(int));
	int *tmp = s->data;
	s->data = new_data;
	free(tmp);
	tmp = NULL;
	printf("-----------copy end-------------\n");
	s->size = new_size;
}

int delete(SeqList *s, int position){
	printf("delete the position %d data in SeqList s\n", position);
	if (position < 0 || position > s->current_len){
		printf("the position is illegal\n");
		return -1;
	}
	for (int i = position; i < s->current_len; ++i){
		s->data[i] = s->data[i+1];
	}
	--s->current_len;
	return 0;
}

void traversal(SeqList *s){
	printf("traversal the sql list\n");
	int len = s->current_len;
	for(int i=0; i<len; i++){
		printf("%d\t", s->data[i]);
	}
	printf("\n\n");
}

int search(SeqList *s, Element i){
	printf("search %d in SeqList s\n", i);
	for (int k = 0; k < s->current_len; ++k){
		if (s->data[k] == i)	return k;
	}
	printf("not find!\n");
	return -1;
}
