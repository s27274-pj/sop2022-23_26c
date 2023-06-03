#include <stdio.h>

int main() {
    int number, sum = 0;

    printf("Input numbers you wish to add together (enter \"0\" to display the sum). \n");
	printf("HINT: Use \"echo $?\" immediately after the program ends to display the sum. \n\n");

    while (1) {
        scanf("%d", &number);

        if (number == 0) {
            break;
        }

        sum += number;
    }

    return sum;
}
