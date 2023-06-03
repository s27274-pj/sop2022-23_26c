#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *plik;
    int liczba_elementow, liczba, i;

    if (argc < 2) {
        printf("Please enter the file name as an argument!\n");
        return 1;
    }

    plik = fopen(argv[1], "r");
    if (plik == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    fscanf(plik, "%d", &liczba_elementow);

    printf("Numbers from the file:\n");
    for (i = 0; i < liczba_elementow; i++) {
        fscanf(plik, "%d", &liczba);
        printf("%d\n", liczba);
    }

    fclose(plik);

    return 0;
}

/* 
jeżeli dobrze zrozumiałem, "FILE" to struktura (typ) w C, która reprezentuje strumień
plikowy. Zmienna "plik" posłuży do przechowania otwartego pliku (należy pamiętać o wskaźniku).

"fopen()" - otwieramy plik za pomocą tej funkcji. Pamiętamy o parametrze "r", czyli trybie 
odczytu.

"fclose()" - funkcja służąca do zamknięcia pliku. Umieszczamy ją na końcu (w tym przypadku),
ponieważ kończymy wtedy pracę z plikiem i możemy zwolnić zasoby systemowe z nim związane.

"fscanf()" - ta funkcja służy nam do odczytania danych z pliku. Za argumeny przyjmuje
strumień wejściowy, format odczytu i adresy zmiennych.
*/
