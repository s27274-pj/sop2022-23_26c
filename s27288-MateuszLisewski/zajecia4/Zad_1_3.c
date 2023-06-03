#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	int i;
	int j;
	int height = atoi(argv[1]);
	
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return 1;
    }
    
    if (height < 1) {
        printf("Wrong height\n");
        return 1;
    }
    for (i = 1 ;i <= height; i++) {
        for (j = 1; j <= height - i; j++) {
            printf(" ");
        }
        for (j = 1; j <= i * 2 - 1; j++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
