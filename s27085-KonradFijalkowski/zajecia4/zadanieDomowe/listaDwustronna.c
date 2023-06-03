#include <stdio.h>
#include <malloc.h>

/*dodanie wskaźnika do poprzedniego elementu*/
typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}Node;

/*https://www.geeksforgeeks.org/introduction-and-insertion-in-a-doubly-linked-list/ */
void printList(Node** currentNode){
    printf("List: ");
    while(*currentNode != NULL){
        printf("[%d] -> ", (*currentNode)->data);
        currentNode = &(*currentNode)->next;
    }
    printf("NULL\n");
}

void freeList(Node* node) {
    Node* nextNode = node;

    while (node != NULL) {
        nextNode = node->next;
        free(node);
        node = nextNode;
    }
}

void pushHead(Node** head, int newData){
    Node *newNode;

    if((*head)->prev != NULL){
        printf("Given pointer is not a head - cannot push\n");
        return;
    }
    newNode = malloc(sizeof (Node));
    if(newNode == NULL){
        perror("Malloc error: ");
        return;
    }
    newNode->data = newData;
    newNode->next = *head;
    newNode->prev = NULL;
    if(*head != NULL){
        (*head)->prev = newNode;
    }
    *head = newNode;
}
void insertAfterNode(Node * chosenNode, int newData){
    Node* newNode = malloc(sizeof (Node));
    if(newNode == NULL){
        perror("Malloc error: ");
        return;
    }
    newNode->data = newData;
    newNode->next = chosenNode->next;
    newNode->prev = chosenNode;
    chosenNode->next = newNode;

    /*genialna sprawa, ustawiam wskaźnik prev kolejnego węzła na newNode*/
    if(newNode->next != NULL){
        newNode->next->prev = newNode;
    }
}

int main(){
    int nodeValues[] = {1, 3, 4, 5, 6};
    int i;
    Node node1;
    Node* head = &node1;;

    /*designated initializer
    https://www.ibm.com/docs/en/zos/2.3.0?topic=initializers-designated-aggregate-types-c-only */
    /*Node node1 = { .data = -10,  .next = NULL, .prev = NULL};*/
    node1.data = -10;
    node1.next = NULL;
    node1.prev = NULL;
    for(i = 0; i < 5; i++){
        pushHead(&head, nodeValues[i]);
    }
    printList(&head);
    insertAfterNode(head->next, 20);

    pushHead(&(head), -4);
    printList(&head);
    freeList(head);
    return 0;
}
