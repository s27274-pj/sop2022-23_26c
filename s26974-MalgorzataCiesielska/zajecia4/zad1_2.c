#include <stdio.h>

int main() {
        int numA;
        int numB;
        printf("First number: ");
        scanf("%d", &numA);
        printf("Second number: ");
        scanf("%d", &numB);
        return numA + numB;
}	
/* to print the return value in the console we need to call
 * ./zad1_2; echo $? (so we run the program normally but add echo at the end
 * to print the return value of the last run program */

