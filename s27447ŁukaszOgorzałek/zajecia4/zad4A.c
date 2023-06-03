#include <stdio.h>

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    int (*functions[3])(int, int) = {maximum, minimum, sum};
    int functionId, elementCount, val;

    printf("Enter the operation ID (0 for maximum, 1 for minimum, 2 for sum): ");
    scanf("%d", &functionId);

    printf("Enter the number of integers the program is going to use: ");
    scanf("%d", &elementCount);

    printf("Enter the integers:\n");
    scanf("%d", &val);

    {
        int i;
        int element;

        for (i = 1; i < elementCount; i++) {
            scanf("%d", &element);
            val = functions[functionId](val, element);
        }
    }

    printf("Result: %d\n", val);

    return 0;
}

/*
na początku definiujemy trzy funkcje maximum, minimum i sum, które przyjmują dwie liczby całkowite
i zwracają odpowiednio maksimum, minimum lub sumę tych liczb.

następnie w funkcji "main()" definiujemy tablicę "functions[]" zawierającą wskaźniki do tych funkcji. 
Potem pobieramy wartości "functionId" (wybór funkcji), elementCount (liczba elementów ciągu do pobrania) oraz kolejne liczby do ciągu.

w pętli for przechodzimy przez kolejne elementy ciągu i wywołujemy odpowiednią funkcję na podstawie "functionId", 
przekazując aktualną wartość "val" oraz aktualny element ciągu. Wynik zapisujemy z powrotem do "val".

na koniec program wypisuje wartość "val", która jest wynikiem zastosowania funkcji na całym ciągu.

program nie zawiera instrukcji warunkowych ani switch w pętli głównej, spełniając tym samym wymagania zadania.
*/
