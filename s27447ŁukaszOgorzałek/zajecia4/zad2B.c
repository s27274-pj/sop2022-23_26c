#include <stdio.h>
#include <stdlib.h>

void wypisz_odwrotnie(int *liczby, int liczba_elementow) {
    int i;
    for (i = liczba_elementow - 1; i >= 0; i--) {
        printf("%d\n", liczby[i]);
    }
}

int main(int argc, char *argv[]) {
    int *liczby, i;
    int liczba_elementow = 0;

    if (argc > 1) {
        /* Wczytanie z pliku */
        FILE *plik = fopen(argv[1], "r");
        if (plik == NULL) {
            printf("Unable to open the file.\n");
            return 1;
        }

        fscanf(plik, "%d", &liczba_elementow);

        /* Alokacja pamięci dla tablicy */
        liczby = (int *)malloc(liczba_elementow * sizeof(int));
        if (liczby == NULL) {
            printf("Memory allocation error.\n");
            fclose(plik);
            return 1;
        }

        /* Wczytanie liczb */
        for (i = 0; i < liczba_elementow; i++) {
            fscanf(plik, "%d", &liczby[i]);
        }

        fclose(plik);
    } else {
        /* Wczytaj ze standardowego wejścia */
        printf("Enter the number of elements to display: ");
        scanf("%d", &liczba_elementow);

        /* Alokacja pamięci dla tablicy */
        liczby = (int *)malloc(liczba_elementow * sizeof(int));
        if (liczby == NULL) {
            printf("Memory allocation error.\n");
            return 1;
        }

        /* Wczytanie liczb */
        for (i = 0; i < liczba_elementow; i++) {
            printf("Enter the number: ");
            scanf("%d", &liczby[i]);
        }
    }

    /* Wypisanie liczb w odwrotnej kolejności */
    wypisz_odwrotnie(liczby, liczba_elementow);

    /* Zwolnienie zaalokowanej pamięci */
    free(liczby);

    return 0;
}

/* 
korzystając z poprzedniego zadania, wprowadziłem kilka modyfikacji zgodnie z poleceniem.

przede wszystkim cała logika została zamknięta w głównym ifie, który najpierw sprawdza,
czy użytkownik wprowadził plik jako argument. Jeżeli tak, liczby zostaną wczytane z pliku,
w przeciwnym razie zostaną wczytane ze standardowego wejścia.

zgodnie z poleceniem, do dynamicznej alokacji używamy "malloc()". Można też użyć "calloc()", 
różnica jest taka, że "calloc()" dodatkowo inicjalizuje wszystkie bity pamięci zerami.

"free()" jest funkcją, dzięki której zwalniamy dynamicznie zaalokowaną pamięć. 
Po wykonaniu funkcji free() blok pamięci staje się dostępny do ponownego użycia.

wypisujemy za pomocą "wypisz_odwrotnie()", funkcją z prostym forem.
*/
