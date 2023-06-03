#include <stdio.h>
#include <stdlib.h>

/* Lista jednostronnie wiązana */

int main() {
    struct node {
    /* ^ Używam structa, żeby zdefiniować każdy element (node) tej listy */
    int data;
    /* ^ data czyli miejsce w nodzie gdzie jest zdefiniowana wartość */
    struct node *link;
    /* ^ *link czyli pointer który wskazuje na adres następnej wartości w liście */
};

    int count = 0;
    struct node *ptr = NULL;
    /* ^ zmienne do pozniejszej petli */

    struct node *current = malloc(sizeof(struct node));
    struct node *head = malloc(sizeof(struct node));

    /* ^ Rezerwujemy pamięć dla pointera head.
    Nie zdefiniowałem typu zmiennych w tym przykładzie.
    Jest to dobra praktyka ale tutaj nie jest to niezbędne
    Wartość tego pointera teraz to adres pierwszego node'a */

    head->data = 45;

    /* ^ Część data pierwszego node'a ma wartość 45 */

    head->link = NULL;

    /* ^ Head wskazuje teraz na pierwszego node'a */

    /* head = malloc(sizeof(struct node));
    head->data = 98;
    head->link = NULL; */

    /* ^ Przypisaliśmy teraz head do drugiego node'a którego
    stworzyliśmy. Teraz nie ma możliwości żeby dostać się
    do pierwszego node'a */

    /* Poprawnym sposobem jest stworzenie drugiego pointera o nazwie current,
    który będzie wskazywał na drugiego node'a 
    struct node *current = malloc(sizeof(struct node));*/

    current->data = 98;

    /* Ustawiamy wartość drugiego node'a przez pointer current,
    który ma dostęp poprzez wartość adresu pamięci do tej zmiennej */

    current->link = NULL;
    /* Wartość link ustawiamy na NULL, bo jest to
    ostatni element tej listy */

    head->link = current;
    /* ^ Wartość link w pierwszym nodzie poprzez pointer head
    ustawiamy na wartość current, dzięki czemu ta wartość link
    przechowuje teraz adres pamięci drugiego node'a w części data.
    W ten sposób ta lista teraz jest jednostronnie wiązana.*/

    current = malloc(sizeof(struct node));
    current->data = 3;
    current->link = NULL;

    /* ^ Możemy użyć ponownie pointera current aby stworzyć kolejnego node'a.
    Ale ten trzeci nie jest jeszcze powiązany z drugim.
    Dlatego musimy stworzyć te powiązanie teraz poniżej. */

    head->link->link = current;

    /* ^ Uzyskujemy dostęp do części link drugiego node'a przez pointer head.
    i przypisujemy mu wartość pointera current.
    W ten sposób mamy już powiązany drugi node z trzecim. */

    if(head == NULL) {
        printf("Lista jest pusta");
        return 0;
    }
    ptr = head;
    while(ptr != NULL) {
        count++;
        ptr = ptr->link;
    }
    printf("Liczba nodow: ");
    printf("%d", count);

    /* ^ Liczymy ilość nodów */
    /* Output: 3 */

    printf("\n");

    ptr = head;

    printf("Elementy w nodach: ");

    while(ptr != NULL) {
        printf("%d ", ptr->data);
        /* ^ Wydrukuj to co jest w następnym nodzie w części data */
        ptr = ptr->link;
        /* ^ Potem przejdz do kolejnego noda po adresie w części link w obecnynm nodzie */
    }

    /* ^ Wypisujemy wszystkie dane na nodach */

    return 0;
}
