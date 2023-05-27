#include <stdio.h>
#include <stdlib.h>

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

int main() {
    int funcId;
    int numberOfElements;
    int element;
    int value;
    int i = 0;
    int * elements;
    int (*arr[])(int a, int b) = {max, min, sum}; /*array of pointers to functions*/

    printf("Input function id: ");
    scanf("%d", &funcId);
    printf("Input number of elements: ");
    scanf("%d", &numberOfElements);

    elements = (int*)calloc(numberOfElements, sizeof(int));
    if (elements == NULL) {
        printf("Memory allocation failed");
        return 1;
    }
    for(i = 0; i < numberOfElements; i++) {
        printf("Input number: ");
        scanf("%d", &element);
        elements[i] = element;
    }
    value = elements[0];
    for (i = 1; i < numberOfElements; i++) {
        value = (*arr[funcId])(value, elements[i]);
    }
    free(elements);
    printf("%d\n", value);
    return 0;
}