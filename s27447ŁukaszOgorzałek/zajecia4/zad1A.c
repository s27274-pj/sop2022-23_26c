#include <stdio.h>

int main() {
    int number, sum = 0;

    printf("Input numbers you wish to add together (enter \"0\" to display the sum): ");

    while (1) {
        scanf("%d", &number);

        if (number == 0) {
            break;
        }

        sum += number;
    }

    printf("The sum is: %d\n", sum);

    return 0;
}
