typedef int Element;

typedef struct{
	Element* data;
	int current_len;
	int size;
}SeqList;


int insert(SeqList *s, Element i, int position);
int delete(SeqList *s, int position);
void traversal(SeqList *s);
int search(SeqList *s, Element e);
SeqList *createSeqList(int n);
void resize(SeqList *s);
