#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

    FILE *file;
    int n,i,number;

    if (argc == 1) {
        file = stdin;
    } else if (argc == 2) {
        file = fopen(argv[1],"r");
        if(file == NULL) {
            exit;
        }
    }

    fclose(file);

    return 0;
}