#include <stdio.h>

int main(int argc, char const *argv[])
{
    int x, sum = 0;
    printf("Podaj liczby: ");
    while (scanf("%d", &x) == 1)
    {
        sum += x;
    }

    printf("Suma podanych liczb: %d\n", sum);
    return 0;
}
