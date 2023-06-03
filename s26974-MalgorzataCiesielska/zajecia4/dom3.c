#include <stdio.h>

/*using recursion (less code but it takes significantly longer to calculate each element)*/
int fibonacciRec(int n) {
    if (n <= 1) {
        return n;
    }
    return (fibonacciRec(n-1) + fibonacciRec(n-2));
}

/*using iteration (more code but much faster calculations)*/
void fibonacciIt(int n) {
    int i;
    int f1 = 0, f2 = 1, fn;
    for (i = 0; i <= n; i++) {
        if (i <= 1) {
            fn = i;
        }
        else {
            fn = f1 + f2; /*this way each element will be the sum of the two preceeding ones*/
            f1 = f2;
            f2 = fn;
        }    
        printf("%d\n", fn);
    }
}

/*interactive program for testing*/
int main() {
    int n;
    int option;
    int i;

    printf("How many elements to generate?\n"); 
    scanf("%d", &n);

    /*for recursive method, above 50 elements the calculation of
    new elements significantly slows, but I'm leaving no limit here*/

    printf("How to generate?\n1.Recursively  2.Iteratively\n");
    scanf("%d", &option);
    if (option != 1 && option != 2) {
        printf("Invalid method");
        return 1;
    }
    
    if (option == 1) {
        for (i = 0; i < n; i++) {
            printf("%d\n", fibonacciRec(i));
        }
    }
    else {
        fibonacciIt(n);
    }
    return 0;
}