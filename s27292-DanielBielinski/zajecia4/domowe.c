#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* createNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNodeStart(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertNodeEnd(struct Node** head, int data){
    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void displayLinkedList(struct Node* head) {
    struct Node* list = head;
    if (list == NULL) {
        printf("Linked list is empty\n");
        return;
    }
    while (list != NULL) {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

void deleteLinkedList(struct Node** head){
    struct Node* current = *head;
    struct Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main(){

    struct Node* newLinkedList;
    insertNodeStart(&newLinkedList,2);
    insertNodeStart(&newLinkedList,1);
    displayLinkedList(newLinkedList);
    insertNodeEnd(&newLinkedList,3);
    displayLinkedList(newLinkedList);
    return 0;
}
