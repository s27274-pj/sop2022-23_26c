#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 500

int main() {
    FILE *file;
    int n, i, num;
    int arr[MAX_NUMBERS];

    file = fopen("Zad_2_OI_data.txt", "r");

	if (file == NULL) {
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(file, "%d", &num);
        arr[i] = num;
    }

    for (i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    fclose(file);

    return 0;
}
