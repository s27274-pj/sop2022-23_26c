#include <stdio.h>

int fib(int x) {
    if (x <= 0) {
        return 0;
    } else if (x == 1) {
        return 1;
    } else {
        return fib(x - 1) + fib(x - 2);
                /* ^ Rekurencja */
    }
}

int main() {
    int n, i;
    
    printf("Podaj liczbe elementow ciagu Fibonacciego: ");
    scanf("%d", &n);
    
    printf("Ciag Fibonacciego o %d elementach:\n", n);
    for (i = 0; i < n; i++) {
        printf("%d ", fib(i));
    }
    
    return 0;
}
