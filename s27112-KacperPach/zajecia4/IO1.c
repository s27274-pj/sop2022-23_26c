#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR_LENGTH 200

int main(int argc, char const *argv[])
{
    FILE *chosenFile;
    int size, i;
    int *numArr;

    if (argc < 2)
        chosenFile = stdin;
    else
        chosenFile = fopen(argv[1], "r");

    if (fscanf(chosenFile,"%d\n",&size) != 1 || size < 1 || size > MAX_ARR_LENGTH )
    {
        /* ERR */
        fclose(chosenFile);
        return 1;
    }

    numArr = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++)
    {
        if(fscanf(chosenFile,"%d\n",&numArr[i]) != 1) {
            fclose(chosenFile);
            free(numArr);
            return 1;
        }
    }

    fclose(chosenFile);

    for (i = size-1; i > -1; i--)
    {
        printf("%d ", numArr[i]);
    }
    printf("\n");

    free(numArr);
    return 0;
}
