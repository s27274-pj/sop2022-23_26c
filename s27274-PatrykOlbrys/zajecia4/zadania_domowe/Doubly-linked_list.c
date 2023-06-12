#include <stdio.h>
#include <stdlib.h>

struct node {
        struct node* prev;
        int data;
        struct node* next;
};

struct node* addAtBeg(struct node* head, int data) {
    /* ^ Ta funkcja przyjmuje head i data
    head to poprostu node (adres node'a?)
    data to dane znajdujące się w nodzie */
        
    struct node* temp = malloc(sizeof(struct node));
    /* ^ tworzymy pointer temp i allocatujemy do niego pamięć
    o wielkości structa node (czyli tworzymy nowego node'a)*/
        
    if (temp == NULL) {
        printf("Nie udalo sie zarezerwowac pamieci.");
        exit(0);
    }
    /* ^ Tutaj sprawdzamy czy *alloc nie zwraca NULL.
    Jeżeli tak się dzieje to znaczy że nie mamy wystarczająco
    dużo pamięci lub wystąpił jakikolwiek inny błąd gdzie poprostu
    tej pamięci nie udało się zarezerwować */
        
    temp->prev = NULL;
    /* ^ ustawiamy część prev na NULL*/
        
    temp->data = data;
    /* ^ ustawiamy część data na takie dane
    jakie przekazaliśmy do funkcji */
        
    temp->next = NULL;
    /* ^ część next też chwilowo na null (po co?) */
        
    temp->next = head;
    /* ^ Teraz część noda next przyjmuje wartość
    pointera head, który ma wartość node'a 
    którego stworzyliśmy na początku */

    head->prev = temp;
    /* Wskaznik head na nodzie który stworzyliśmy na początku ma taki
    sam adres jak część prev noda, teraz łączymy go wstecz z nodem
    ktory dodajemy na początku */

    head = temp;
    return head;
}

int main() {

    struct node *head = malloc(sizeof(struct node));
    /* ^ Rezerwuję pamięć dla nowego node'a i tworzę wskaźnik,
    który na niego wskazuje */
        
    if (head == NULL) {
        printf("Nie udalo sie zarezerwowac pamieci.");
        exit(0);
    }
    /* ^ Sprawdzamy czy udało się zaalokować pamięć */

    struct node* ptr;
    /* ^ Deklarujemy pointer ptr */

    head->prev = NULL;
    /* ^ To część node'a która wskazuje na poprzedniego.
    Jako, że jest to pierwszy node ustawiamy to na NULL*/
        
    head->data = 10;
    /* ^ Część data tego node'a ma wartość 10 */
        
    head->next = NULL;
    /* ^ Narazie mamy tylko jeden node więc też ustawiamy część wskazującą
    na następny na NULL */

    head = NULL;
    /* ^ Wartość pointera head ustawiamy na NULL */
    
    head = addAtBeg(head, 34);

    ptr = head;
    while(ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }

    printf("%s", "cos");
        
    free(head);

    return 0;
}
