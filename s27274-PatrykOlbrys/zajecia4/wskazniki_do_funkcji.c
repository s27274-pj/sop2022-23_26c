#include <stdio.h>

int minimum(int x, int y) {
        return x < y ? x : y;
        /* ^ Ternary operator - skrócony zapis if-else.
        Jak prawda to zwraca a, jak fałsz to zwraca b */
}
int maksimum(int x, int y) {
    return x > y ? x : y;
}
int suma(int x, int y) {
    return x + y;
}

int main() {
    int functionId = 0;
    int elementCount = 0;
    int v = 0;
    int i = 0;
    int (*functions[3])(int, int) = {minimum, maksimum, suma};
    /* Deklaracja tablicy wskaźników do funkcji typu int o nazwie 'functions' o rozmiarze 3. 
    (int, int) to typy argumentów jakie te funkcje przyjmują */


    printf("Podaj functionId. (0 - minimum, 1 - maksimum, 2 - sum): ");
    scanf("%d", &functionId);
    /* Zapisujemy podaną liczbę do adresu zmiennej functionId */

    printf("Podaj liczbe elementow: ");
    scanf("%d", &elementCount);

    printf("Podaj elementy: \n");
    scanf("%d", &v);
    /* Wartość pierwszego elementu przyjmuje zmienna v */

    for (i = 1; i < elementCount; i++) {
        int element;
        scanf("%d", &element);
        v = functions[functionId](v, element);
        /* Porównujemy każdy kolejny element z poprzednim 
        i wywołujemy tym samym konkretną funkcję według functionId,
        które podaliśmy na samym początku z argumentami v i element.*/
    }
    
    printf("Wynik: %d\n", v);

    return 0;
}