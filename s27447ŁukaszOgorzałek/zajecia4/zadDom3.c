#include <stdio.h>

/* Rekurencyjna wersja */
int fibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

/* Iteracyjna wersja */
int fibonacciIterative(int n) {
    int prev = 0;
    int current = 1;
	int i;

    if (n <= 1) {
        return n;
    }

    for (i = 2; i <= n; i++) {
        int next = prev + current;
        prev = current;
        current = next;
    }

    return current;
}

int main() {
    int n = 10; 	/* liczba kolejnych wartości do obliczenia dla wersji rekurencyjnej */
	int m = 9; 		/* liczba kolejnych wartości do obliczenia dla wersji iteracyjnej */
	int j, k;

    printf("Ciąg Fibonacciego (wersja rekurencyjna):\n");

    for (j = 0; j < n; j++) {
        printf("%d ", fibonacciRecursive(j));
    }
    printf("\n");

    printf("Ciąg Fibonacciego (wersja iteracyjna):\n");
	
    for (k = 0; k < m; k++) {
        printf("%d ", fibonacciIterative(k));
    }
    printf("\n");

    return 0;
}
