#include <stdio.h>

int main() {
	int numA;
	int numB;
	printf("First number: ");
	scanf("%d", &numA); /*'%d' scans a number, &numA is the address in memory of numA*/
	printf("Second number: ");
	scanf("%d", &numB);
	printf("%d\n", numA+numB);
	return 0;
}
