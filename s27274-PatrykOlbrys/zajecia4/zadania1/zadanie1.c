#include <stdio.h>

int main() {
    int sum = 0, number;

    do {
        number = 0;
        printf("Podaj liczbe: ");
        scanf("%d", &number);
        sum += number;
    } while (number != 0);

    printf("%d\n", sum);

    return 0;
}
