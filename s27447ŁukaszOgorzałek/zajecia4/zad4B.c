#include <stdio.h>

typedef int (*Compare)(int, int);

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int forAll(int *tab, int elementCount, Compare function) {
    int result = tab[0];
    int i;

    for (i = 1; i < elementCount; i++) {
        result = function(result, tab[i]);
    }

    return result;
}

int main() {
    int tab[] = {5, 2, 7, 9, 3};
    int elementCount = sizeof(tab) / sizeof(tab[0]);

    int result = forAll(tab, elementCount, maximum);
	
    printf("Maximum: %d\n", result);

    result = forAll(tab, elementCount, minimum);
    printf("Minimum: %d\n", result);

    result = forAll(tab, elementCount, sum);
    printf("Sum: %d\n", result);

    return 0;
}

/*
wykorzystując elementy z poprzedniego programu, aby ułatwić wprowadzenie założeń
polecenia w życie, najpierw deklarujemy typ wskaźnikowy "Compare" za pomocą "typedef". 
wskazuje on na funkcję, która przyjmuje dwie liczby całkowite i zwraca liczbę całkowitą.

	[*]keyword "typedef" służy do tworzenia nowych typów danych w języku C. Dzięki całemu 
	zabiegowi możemy używać typu "Compare" jako nazwy dla wskaźnika do funkcji o określonym 
	formacie, co ułatwia deklarację zmiennych i argumentów funkcji.
	
funkcja "forAll()" przyjmuje wskaźnik do tablicy "tab[]", liczbę elementów elementCount 
oraz wskaźnik do funkcji "function()". "forAll()" iteruje przez tablicę, a na końcu zwraca ostateczny wynik (result).

w funkcji "main()" tworzymy tablicę "tab[]" z kilkoma liczbami całkowitymi i obliczamy jej rozmiar. 
następnie wywołujemy funkcję "forAll()" trzy razy, podając różne funkcje jako trzeci argument. Wynik jest wypisywany
na standardowym wyjściu.
*/
