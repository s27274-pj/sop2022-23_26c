#include <stdio.h>
#include <stdlib.h>
/* Biblioteka stdlib.h po to abyśmy mogli korzystać z atoi */ 
/* atoi - ASCII to integer */ 

int main(int argc, char **argv) {
/* argc - Number of arguments passed */
/* argv[] pointer array which points to each argument passed to the program */

    int i = 0;
    int k = 0;
    int j = 0;
    int stars = 1;
    int number = atoi(argv[1]);
    int spaces = number - 1;

    for (i = 0; i < number; i++){

        for (j = 0; j < spaces; j++)
            printf(" ");
        
        for (k = 0; k < stars; k++){
            printf("*");
        }
        printf("\n");

        spaces--;
        stars += 2;
    }
    return 0;
}
