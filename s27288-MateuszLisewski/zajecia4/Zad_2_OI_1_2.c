#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *input_file;
    int *numbers;
    int num_count, i;

    if (argc == 1) {
        input_file = stdin;
        printf("Enter the number of integers and then every number: ");
    } else if (argc == 2) {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }
	
    fscanf(input_file, "%d", &num_count);
    if (num_count == 0) {
        fprintf(stderr, "Error: Invalid number count %d\n", num_count);
        exit(EXIT_FAILURE);
    }

    numbers = malloc(num_count * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < num_count; i++) {
        fscanf(input_file, "%d", &numbers[i]);
    }

    if (input_file != stdin) {
        fclose(input_file);
    }

    for (i = num_count - 1; i >= 0; i--) {
        printf("%d\n", numbers[i]);
    }

    free(numbers);

    return 0;
}
