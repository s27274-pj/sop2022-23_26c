#include <stdio.h>
#include <malloc.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

//https://www.geeksforgeeks.org/insertion-in-linked-list/
void printList(Node* currentNode){
    printf("List: ");
    while(currentNode != NULL){
        printf("[%d] -> ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("NULL");
}
/*dodawanie węzła na końcu listy*/
void appendNode(Node ** head, int newData){
    Node* newNode = malloc(sizeof(Node));
    Node* lastNode = *head;
    if(newNode == NULL){
        perror("Malloc error: ");
        return;
    }

    newNode->data=newData;
    newNode->next=NULL;
    /*jeżeli head nie jest alokowany niech to będzie nowy head */
    if(*head == NULL){
        *head = newNode;
        return;
    }
    /*przejdź do ostatniego węzła */
    while(lastNode->next !=NULL){
        lastNode = lastNode->next;
    }
    /*niech ostatnim węzłem będzie ten utworzony w tej funkcji */
    lastNode->next = newNode;
    return;
}
/*zwalnianie przestrzeni adresowej*/
void freeList(Node* node) {
    Node* nextNode = node;
    while (node != NULL) {
        /*wskaż na kolejny węzeł*/
        nextNode = node->next;
        /*skasuj obecny węzeł*/
        free(node);
        /*ustaw kolejny węzeł jako obecny*/
        node = nextNode;
    }
}

int main(){
    struct Node* head = NULL;
    appendNode(&head, 6);
    appendNode(&head, 4);
    appendNode(&head, 1);
    appendNode(&head, 2);
    printList(head);
    freeList(head);
    return 0;
}
