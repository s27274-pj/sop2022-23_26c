#include <stdio.h>

/* funkcja rekurencyjna */ 
int fibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
}

/* funkcja iteracyjna */ 
int fibonacciIterative(int n) {
    int prevPrev = 0;
    int prev = 1;
    int current = 0;
    int i;
    if (n <= 1) {
        return n;
    }
    for ( i = 2; i <= n; i++) {
        current = prev + prevPrev;
        prevPrev = prev;
        prev = current;
    }
    return current;
}

int main() {
    int n = 10;
    printf("%d\n", fibonacciRecursive(n));
    printf("%d\n", fibonacciIterative(n));
    return 0;
}
