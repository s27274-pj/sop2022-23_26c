#include <stdio.h>
#include <stdlib.h>

/*the code here is mostly reused from the previous task, with some minor differences where
the pointer to previous element also needs to be modified*/

struct element
{
    int value;
    struct element * prev; /*pointer to previous element*/
    struct element * next;  /*pointer to next element*/
};

int length(struct element * head) {
    struct element * temp = head; /*temp element is necessary to not modify head*/
    int length = 0;
    while ( (temp = temp->next) != NULL) /*if next is null then we have reached the last element*/
    {
        length++;
    }
    return length;
}

void print(struct element * head) {
    struct element * temp = head;
    printf("[ ");
    while (temp != NULL)
    {
        if (temp->next == NULL) {
            printf("%d", temp->value);
        }
        else {
            printf("%d, ", temp->value);
        }
        temp = temp->next;
    }
    printf(" ]\n");
}

void append(struct element * head, int newValue) {
    struct element * last = head;
    struct element * new = (struct element*)malloc(sizeof(struct element));
    if (new == NULL) {
        printf("Memory allocation failed");
        return;
    }
    new->value = newValue;
    new->next = NULL;
    if (head == NULL) {
        head = new;
        return;
    } 
    while (last->next != NULL) { /*iterating over list to get to the last element*/
        last = last->next;
    }
    new->prev = last; /*here we're also assigning the last element as previous for our new element*/
    last->next = new; /*assigning our new element as next for the last element*/
}

void insertAt(struct element * head, int position, int newValue) {
    struct element *toInsertAfter = head;
    struct element *new = (struct element*)malloc(sizeof(struct element));
    if (new == NULL) {
        printf("Memory allocation failed");
        return;
    }
    new->value = newValue;
    if (position < 0 || position > length(head)) {  /*making sure that the position is within list boundaries*/
        free(new);
        printf("Incorrect position\n");
        return;
    }
    if (position == 0) {  /*if position is 0 then we are inserting a new head*/
        new->prev = NULL;
        new->next = head;
        head->prev = new;
        return;
    }
    while (--position > 0)  /*iterating over list to get to the desired position*/
    {
        toInsertAfter = toInsertAfter->next;
    }
    new->next = toInsertAfter->next; /*here we also have to assign pointers to prev element*/
    new->prev = toInsertAfter;
    toInsertAfter->next->prev = new;
    toInsertAfter->next = new;
}    

void removeAt(struct element ** head, int position) {
    struct element *toDeleteAfter = *head;
    if (position < 0 || position > length(*head) + 1) {
        printf("Incorrect position\n");
        return;
    }
    if (position == 0) {  /*if position is 0 then we are moving head to the next element*/
        (*head)->next->prev = NULL;
        *head = (*head)->next;
        return;
    }
    while (--position >= 1)
    {
        toDeleteAfter = toDeleteAfter->next;
    }
    toDeleteAfter->next->next->prev = toDeleteAfter;
    toDeleteAfter->next = toDeleteAfter->next->next;
}

void removeLast(struct element * head) {
    struct element * nextToLast = head;
    while (nextToLast->next->next != NULL) { /*iterating over list to get to the next to last element*/
        nextToLast = nextToLast->next;
    }
    nextToLast->next = NULL;
}

int main() {
    struct element * head = (struct element*)malloc(sizeof(struct element));
    if (head == NULL) {
        printf("Memory allocation failed");
        return 1;
    }
    head->value = 3;
    append(head, 1);
    append(head, 4);
    append(head, 5);
    printf("Initial list:\n");
    print(head);

    insertAt(head, 1, 9);
    printf("Inserted 9 at pos 1:\n");
    print(head);

    removeAt(&head, 3);
    printf("Removed at pos 3:\n");
    print(head);

    removeLast(head);
    printf("Removed last:\n");
    print(head);

    free(head);
    return 0;
}