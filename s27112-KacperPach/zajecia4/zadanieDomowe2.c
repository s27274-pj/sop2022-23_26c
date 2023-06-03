#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List 
{
    struct Node *first;
    struct Node *last;
} List;

List *createList() {
    List *newList = malloc(sizeof(List));
    newList -> first = NULL;
    newList -> last = NULL;
    return newList;
}

void pushEnd(List *list, int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode-> value = val;
    newNode-> next = NULL;
    newNode-> prev = list -> last;
    if (list->first == NULL)
    {
        list ->first = newNode;
    } else {
        list -> last -> next = newNode;
    }
    list -> last = newNode;
}

void pushStart(List *list, int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode->next = list->first;
    newNode->prev = NULL;
    newNode->value = val;
    if (list->last == NULL)
    {
        list->last = newNode;
    } else {
        list->first->prev = newNode;
    }
    list->first = newNode;
}

void printList(List *list) {
    Node *item = malloc(sizeof(Node));
    if(list != NULL && list->first != NULL && list->last !=NULL) {
        item = list->first;
        while (item != NULL)
        {
            printf("%d ", item->value);
            item = item->next;
        }
    }
    printf("\n");
    free(item);
}

void popFirst(List *list) {
    Node *oldFirst;

    if (list->first == NULL)
        return;

    oldFirst = list->first;
    list->first = oldFirst->next;
    if (list->first != NULL) {
        list->first->next = NULL;
    } else {
        list->last = NULL;
    }
    free(oldFirst);
}

void deleteList(List *list) {
    while (list->first != NULL)
    {
        popFirst(list);
    }
    free(list);
}

int main(int argc, char const *argv[])
{
    List *new = createList();
    pushEnd(new,1);
    popFirst(new);
    pushEnd(new,2);
    pushEnd(new,3);
    pushStart(new,4);
    printList(new);
    deleteList(new);
    
    return 0;
}
