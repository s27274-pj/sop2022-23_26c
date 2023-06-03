#include <stdio.h>
#include <stdlib.h>

struct element
{
    int value;
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
    new->value = newValue;
    new->next = NULL;
    if (head == NULL) {
        head = new;
        return;
    } 
    while (last->next != NULL) { /*iterating over list to get to the last element*/
        last = last->next;
    }
    last->next = new; /*assigning our new element as next for the last element*/
}

void insertAt(struct element ** head, int position, int newValue) {
    struct element *prev = *head;
    struct element *new = (struct element*)malloc(sizeof(struct element));
    new->value = newValue;
    new->next = NULL;
    if (position < 0 || position > length(*head)) {  /*making sure that the position is within list boundaries*/
        free(new);
        printf("Incorrect position\n");
        return;
    }
    if (position == 0) {  /*if position is 0 then we are inserting a new head*/
        new->next = *head;
        *head = new;
        return;
    }
    while (--position > 0)  /*iterating over list to get to the desired position*/
    {
        prev = prev->next;
    }
    new->next = prev->next;
    prev->next = new;
}

void removeAt(struct element ** head, int position) {
    struct element *prev = *head;
    if (position < 0 || position > length(*head) + 1) {
        printf("Incorrect position\n");
        return;
    }
    if (position == 0) {  /*if position is 0 then we are moving head to the next element*/
        *head = (*head)->next;
        return;
    }
    while (--position >= 1)
    {
        prev = prev->next;
    }
    prev->next = prev->next->next;
}

void removeLast(struct element * head) {
    struct element * nextToLast = head;
    while (nextToLast->next->next != NULL) { /*iterating over list to get to the next to last element*/
        nextToLast = nextToLast->next;
    }
    nextToLast->next = NULL;
}

void sort(struct element * head) {
    struct element * current = head;
    struct element * index;
    int temp;
    if (head == NULL) {
        return;
    } 
    while (current != NULL) { /*iterating over all elements*/
        index = current->next;
        while (index != NULL) {
            if (current->value > index->value) { /*we compare each element to the current and switch their
                                                    position if necessary*/
                temp = current->value;
                current->value = index->value;
                index->value = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

struct element * elementAt(struct element * head, int position) {
    struct element *desired = head;
    while (position-- > 0)  
    {
        desired = desired->next;
    }
    return desired;
} 

int main() { //some code for testing the functions
    struct element * head = (struct element*)malloc(sizeof(struct element));
    head->value = 3;
    append(head, 1);
    append(head, 4);
    append(head, 5);
    printf("Initial list:\n");
    print(head);

    insertAt(&head, 2, 9);
    printf("Inserted 9 at pos 2:\n");
    print(head);

    sort(head);
    printf("Sorted:\n");
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