#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int y, x;
    int height = atoi(argv[1]);
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < height - y; x++)
            printf(" ");
        for (x = 0; x < 2 * y - 1; x++)
            printf("*");
        printf("\n");
    }

    return 0;
}
