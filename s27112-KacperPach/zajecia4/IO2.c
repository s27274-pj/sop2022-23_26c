#include <stdio.h>
#include <stdlib.h>

#define NUM_BUFFER_ELEMENTS 16

int main(int argc, char const *argv[])
{
    FILE *chFile;
    unsigned char *buffer = malloc(NUM_BUFFER_ELEMENTS*sizeof(char));
    unsigned int lineNum = 1;
    int i;

    if(argc < 2) {
        printf("Nie podano argumentow");
        return 1;
    } else {
        chFile = fopen(argv[1],"r");
    }

    while (fread(buffer,sizeof(char),NUM_BUFFER_ELEMENTS, chFile) > 0)
    {
        printf("%08X  ",lineNum * NUM_BUFFER_ELEMENTS);

        for ( i = 0; i < sizeof(char)*NUM_BUFFER_ELEMENTS; i++ )
        {
            printf("%02X ", buffer[i]);
        }
        printf(" ");
        for ( i = 0; i < sizeof(char)*NUM_BUFFER_ELEMENTS; i++ )
        {
            if((buffer[i] > 31 && buffer[i] < 127 )|| buffer[i] > 127)
                printf("%c", buffer[i]);
            else
                printf(" ");
        }

        /* clear buffer */
        for ( i = 0; i < NUM_BUFFER_ELEMENTS; i++)
        {
            buffer[i] = ' ';
        }

        printf("\n");
        lineNum++;
    }

    fclose(chFile);
    free(buffer);
    return 0;
}
