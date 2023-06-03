#include <stdio.h>
#include <stdlib.h>

#define BYTES_PER_LINE 16

int main(int argc, char *argv[]) {

    unsigned char buffer[BYTES_PER_LINE];
    int byte_count = 0;
    int line_count = 0;
    int i;
	
	FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 2;
    }

    printf("Loading file: %s\n\n", argv[1]);

    while (1) {
        byte_count = fread(buffer, 1, BYTES_PER_LINE, input_file);
        if (byte_count == 0) {
            break;
        }

        printf("%08X  ", line_count * BYTES_PER_LINE);

        for (i = 0; i < byte_count; i++) {
            printf("%02X ", buffer[i]);
            if (i == BYTES_PER_LINE/2 - 1) {
                printf(" ");
            }
        }

        for (; i < BYTES_PER_LINE; i++) {
            printf("   ");
            if (i == BYTES_PER_LINE/2 - 1) {
                printf(" ");
            }
        }

        printf(" ");

        for (i = 0; i < byte_count; i++) {
            if (buffer[i] >= 32 && buffer[i] <= 126) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }

        printf("\n");
        line_count++;
    }

    fclose(input_file);
	
	printf("\nClosing file: %s\n\n", argv[1]);

    return 0;
}
