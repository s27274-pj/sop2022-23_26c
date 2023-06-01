#include <stdio.h>
#include <unistd.h>

int main() {

	char input[100];

    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());

    printf("Oczekiwanie na dane\n");

    fgets(input, sizeof(input), stdin);

    printf("Wprowadzono: %s", input);

    return 0;
}
/* 	
	do wylaczenia programu uzyjemy numeru PID podanego w konsoli 
   	kill "PID" 
*/
