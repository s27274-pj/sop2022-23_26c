#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int height = atoi(argv[1]);  /*atoi converts char to int*/
	int spaces = height - 1;
	int stars = 1;
	int i;
	for (i = 1; i <= height; i++) {
		int j = 0;
		while (j < spaces) {  /*first prints however many spaces necessary*/
			printf(" ");
			j++;
		}
		j = 0;
		while (j < stars) {  /*then prints however many lines necessary*/
			printf("*");
			j++;
		}
		spaces--;
		stars += 2;  /*each row has two more stars than the one before*/
		printf("\n");
	}
	return 0;
}
