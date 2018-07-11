typedef int Element;

typedef struct Node{
	Element data;
	struct Node* next;
}Node;


Node* creatLinkedList(int n);
void traval(Node *iter);
Node* insert(Node *head, int position, Element data);
Node* insertAtHead(Node* head, Element data);
Node* insertAtTail(Node* head, Element data);
Node* delete(Node* head, int position);
Node *deleteAtHead(Node* head);
Node *deleteAtTail(Node* head);
int getSize();

