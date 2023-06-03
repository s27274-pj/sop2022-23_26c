#include <stdio.h>

int main(int argc, char const *argv[])
{
    int x, sum = 0;
    printf("Podaj liczby: ");
    while (scanf("%d", &x) == 1)
    {
        sum += x;
    }

    return sum; // nastepnie w konsoli echo $?
}
