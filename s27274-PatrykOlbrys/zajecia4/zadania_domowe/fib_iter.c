#include <stdio.h>

int fib_iter(int n) {
    int a = 0;
    int b = 1;
    int i, temp;

    if (n == 0)
        return a;

    for (i = 2; i <= n; i++) {
    /* ^ Iterujemy od 2 bo dwa pierwsze indeksy
    zostały wcześniej zadeklarowane jako a i b */
        temp = a + b;
        a = b;
        b = temp;
    }

    return b;
    /* Zwracamy b jako sumę dwóch składników */
}

int main() {
    int n, i;
    
    printf("Podaj liczbe elementow ciagu Fibonacciego: ");
    scanf("%d", &n);
    
    printf("Ciag Fibonacciego o %d elementach:\n", n);
    for (i = 0; i < n; i++) {
        printf("%d ", fib_iter(i));
    }
    
    return 0;
}
