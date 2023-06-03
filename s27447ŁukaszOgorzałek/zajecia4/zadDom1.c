#include <stdio.h>
#include <stdlib.h>

/* Struktura węzła listy */
typedef struct Node {
    int data;            /* Przechowywane dane */
    struct Node* next;   /* Wskaźnik do następnego węzła */
} Node;

/* Funkcja do dodawania elementu na koniec listy */
void append(Node** headRef, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        Node* current = *headRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

/* Funkcja do wyświetlania zawartości listy */
void display(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/* Funkcja do zwalniania pamięci zajmowanej przez listę */
void free_list(Node** headRef) {
    Node* current = *headRef;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *headRef = NULL;
}

int main() {
    Node* head = NULL;

    append(&head, 14);
    append(&head, 2);
    append(&head, 7);

    display(head);

    free_list(&head);

    return 0;
}

/*
w "append()" tworzony jest nowy węzeł, a następnie jest on dodawany na koniec listy.
jeśli lista jest pusta, nowy węzeł staje się głową listy. W przeciwnym przypadku, 
iterujemy po liście aż do ostatniego węzła i ustawiamy wskaźnik next ostatniego węzła
na nowy węzeł.

"display()" iteruje po wszystkich węzłach listy i wyświetla ich zawartość.

"freeList()" zwalnia pamięć zajmowaną przez wszystkie węzły listy. Iterujemy po liście, 
zwalniamy bieżący węzeł i przechodzimy do następnego węzła.
*/
