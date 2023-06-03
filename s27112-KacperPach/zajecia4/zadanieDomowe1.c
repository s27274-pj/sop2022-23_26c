#include <stdio.h>
#include <stdlib.h>

/* węzeł listy */ 
typedef struct Node {
    int value;         
    struct Node *next;  
} Node;

/* lista */
typedef struct List {
    Node *head;  /* wskaźnik do pierwszego węzła w liście */
} List;

/* funkcja inicjalizująca */
List *createList() {
    List *list = (List*) malloc(sizeof(List));
    list->head = NULL;
    return list;
}

/* funkcja dodająca element na koniec listy */
void push(List *list, int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *curr_node = list->head;
        while (curr_node->next != NULL) {
            curr_node = curr_node->next;
        }
        curr_node->next = new_node;
    }
}

/* funkcja usuwająca element z początku listy */
void popFirst(List *list) {
    if (list->head != NULL) {
        Node *old_head = list->head;
        list->head = old_head->next;
        free(old_head);
    }
}

/* funkcja wyświetlająca zawartość listy */
void printList(List *list) {
    Node *curr_node = list->head;
    while (curr_node != NULL) {
        printf("%d ", curr_node->value);
        curr_node = curr_node->next;
    }
    printf("\n");
}

/* funkcja usuwająca całą listę */
void deleteList(List *list) {
    while (list->head != NULL) {
        popFirst(list);
    }
    free(list);
}

int main() {
    List *list = createList();

    push(list, 1);
    push(list, 2);
    push(list, 3);

    printf("Lista: ");
    printList(list);

    popFirst(list);

    printf("Lista po usunięciu pierwszego elementu: ");
    printList(list);

    deleteList(list);

    return 0;
}
