#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insert(struct Node** head, int value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = *head;
    *head = new_node;
}

void delete(struct Node **head) {
    if (*head == NULL) {
        return;
    }
    delete(&(*head)->next);
    free(*head);
    *head = NULL;
}

void deleteOne(struct Node** head, int value) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void print(struct Node* head) {
    struct Node* temp = head;

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main() {
    struct Node* head = NULL;

    insert(&head, 9);
    insert(&head, 4);
    insert(&head, 0);
    print(head);

    deleteOne(&head, 4);
    print(head);
	
	delete(&head);
	print(head);
    
	return 0;
}
