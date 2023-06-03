#include <stdio.h>

int main(void) {
    int n, sum = 0;
    printf("Input integers (0 ends program):\n");
    while (scanf("%d", &n) == 1 && n != 0) {
        sum += n;
    }
    printf("Sum is %d\n", sum);
    return sum;
}
