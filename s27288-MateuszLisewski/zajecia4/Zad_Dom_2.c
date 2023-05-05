#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;

void insertAtBeginning(int value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;
    if (head != NULL) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
}

void insertAtEnd(int value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = tail;
    newNode->next = NULL;
    if (tail != NULL) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

void deleteAtBeginning() {
    Node *temp = head;
	if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (head == tail) {
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
        head->prev = NULL;
    }
    free(temp);
}

void deleteAtEnd() {
	Node *temp = tail;
	
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (head == tail) {
        head = NULL;
        tail = NULL;
    } else {
        tail = tail->prev;
        tail->next = NULL;
    }
    free(temp);
}

void display() {
	Node *temp = head;
    
	if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    insertAtBeginning(15);
    insertAtEnd(25);
    insertAtEnd(55);
    insertAtBeginning(10);
    display();
    deleteAtEnd();
    deleteAtBeginning();
    display();
    return 0;
}
