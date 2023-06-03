#include <stdio.h>
#include <stdlib.h>

/* Struktura węzła listy */
typedef struct Node {
    int data;            /* Przechowywane dane */
    struct Node* prev;   /* Wskaźnik do poprzedniego węzła */
    struct Node* next;   /* Wskaźnik do następnego węzła */
} Node;

/* Funkcja do dodawania elementu na koniec listy */
void append(Node** headRef, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		perror("Failed to allocate memory for new node.\n");
		exit(1);
    }
	
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        Node* current = *headRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
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

/* Funkcja do usuwania konkretnego elementu z listy */
void remove_node(Node** headRef, int value) {
    Node* current = *headRef;
    while (current != NULL) {
        if (current->data == value) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *headRef = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

int main() {
      Node* head = NULL;

    append(&head, 5);
    append(&head, 2);
    append(&head, 7);
    append(&head, 9);

    display(head);

    remove_node(&head, 2);

    display(head);

    free_list(&head);

    return 0;
}

/*
ta lista dwukierunkowa ma dodatkową funkcjonalność, ponieważ możemy przechodzić
w obu kierunkach po liście, korzystając z wskaźnika "prev". Możemy również dodawać 
i usuwać elementy zarówno na początku, jak i na końcu listy.

w programie znajduje się też dodatkowa funkcja umożliwiająca usunięcie
danego elementu z listy.

"remove_node" iteruje po liście, sprawdzając każdy węzeł, czy jego wartość jest równa
podanej wartości do usunięcia. Jeśli tak, wykonuje odpowiednie operacje, aby usunąć 
węzeł z listy. Jeśli usuwany węzeł jest w środku listy, ustawia odpowiednie wskaźniki 
prev i next sąsiadujących węzłów tak, aby ominąć usuwany węzeł. Jeśli usuwany węzeł 
jest na początku listy, ustawia nową głowę listy. Po usunięciu węzła, zwalnia zaalokowaną pamięć.
*/
