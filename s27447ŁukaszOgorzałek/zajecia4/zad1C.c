#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int height, i, j;

    if (argc < 2) {
        printf("Please enter the height of the tree as an argument!\n");
        return 1;
    }

    height = atoi(argv[1]);

    for (i = 0; i < height; i++) {
        for (j = 0; j < height - i - 1; j++) {
            printf(" ");
        }
        for (j = 0; j < i * 2 + 1; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}

/* 
[!]pamiętamy o deklaracji zmiennych zgodnie ze standardem ANSI C
[!]w tym i następnych zadaniach.

"argc" (ang. argument count) - oznacza liczbę argumentów przekazanych do programu podczas
jego wywołania. "argv[]" (ang. argument vector) - zawiera wartości argumentów przekazanych 
do programu jako ciągi znaków.

"atoi()" - funkcja zwraca wartość z łańcucha znaków przekonwertowaną do postaci liczbowej
w przypadku sukcesu. Jeżeli zalezy nam na większej kontroli i zaawansowanej obsłudze błędów,
warto zastosować funkcję "strtol()".

Dzięki temu program może odczytać parametry wywołania i wykonać odpowiednie akcje 
w zależności od wartości tych parametrów. 
*/ 
