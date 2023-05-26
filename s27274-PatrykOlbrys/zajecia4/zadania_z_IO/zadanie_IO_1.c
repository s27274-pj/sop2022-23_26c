#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 100
/* ^ Zabezpieczenie przed przepełnieniem bufora */

int main(int argc, char** argv) {
    int i = 0;
    int liczba_elementow = 0;
    /* ^ Musiałem przypisać jakąś wartość do tej zmiennej
    bo kompilacja mnie nie przepuści */

    int* ciagLiczb = (int*) malloc(liczba_elementow * sizeof(int));
    
    if (ciagLiczb == NULL) {
        printf("Nie udalo sie zarezerwowac pamieci.");
        exit(0);
    }
    /* ^ Sprawdzamy czy udało się poprawnie zaalokować pamięć */
    
    FILE *plik;
    /* ^ Pointer pointing to a file */

    if (argc == 1) {
        /* Wczytywanie ze standardowego wejścia */
        printf("Podaj liczbe elementow ciagu: ");
        scanf("%d", &liczba_elementow);

        printf("Podaj elementy ciagu (po jednym w kaz dej linii):\n");
        for (i = 0; i < liczba_elementow; i++) {
            scanf("%d", &ciagLiczb[i]);
        }
    }

    else if (argc == 2) {
        plik = fopen(argv[1], "r");
        /* printf("%d", liczba_elementow); */

        if (plik == NULL) {
            printf("Nie można otworzyc pliku.\n");
            return 1;
        }

        fscanf(plik, "%d", &liczba_elementow);
        /* Wczytanie pierwszej liczby na pierwszej linijce pliku i przypisanie
        jej do adresu pamięci zmiennej liczba_elementow */

        for (i = 0; i < liczba_elementow; i++) {
            fscanf(plik, "%d", &ciagLiczb[i]);
            /* Czytamy z pliku cyfry i uzupełniamy tablicę ciągLiczb */
        }

        fclose(plik);
    }

    if (ciagLiczb == NULL) {
        printf("Błąd alokacji pamięci.\n");
        return 1;
    }


    /* Wyświetlanie wczytanego ciągu liczb */ 
    printf("Liczby wczytane:\n");
    for (i = 0; i < liczba_elementow; i++) {
        printf("%d\n", ciagLiczb[i]);
    }

    printf("Liczby w odwrotnej kolejnosci:\n");
    for (i = liczba_elementow - 1; i >= 0; i--) {
        printf("%d\n", ciagLiczb[i]);
    }

    free(ciagLiczb); /* Zwolnienie zaalokowanej pamięci */ 

    return 0;
}
