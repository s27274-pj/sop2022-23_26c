#include <stdio.h>

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int min (int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int sum (int a, int b) {
    return a + b;
}

int forAll(int * array, int numberOfElements, int (*func)(int a, int b)) {
    int i;
    int value = array[0];
    for (i = 1; i < numberOfElements; i++) {
        value = (*func)(value, array[i]);
    }
    return value;
}

int main() {
    int numberOfElements = 5;
    int array[] = { 2, 3, 5, 9, 1 };
    int sumResult = forAll(array, numberOfElements, sum);
    int maxResult = forAll(array, numberOfElements, max);
    int minResult = forAll(array, numberOfElements, min);
    printf("Sum: %d, max: %d, min: %d\n", sumResult, maxResult, minResult);
    return 0;
}