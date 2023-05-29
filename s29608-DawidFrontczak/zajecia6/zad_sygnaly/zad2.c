#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
 
void handle_signal(int signal){
	printf("Wykryto probe uruchomienia drugiej instancji programu.\n");
}
 
void handle_ctrlc(int signal){
	printf("Przerwano program przy uzyciu CTRL+C.\n");
	remove("/tmp/lock");
	exit(0);
}
 
int main(){
	FILE* plik_blokady;
	printf("PID - %d \n", getpid());
	if (access("/tmp/lock", F_OK)==0){
		printf("Inna instancja jest juz uruchomiona.\n");
		return 0;
	}
 
	plik_blokady = fopen("/tmp/lock", "w");
	if (plik_blokady == NULL){
		printf("Blad tworzenia pliku blokady.\n");
		return 1;
	}
 
	fprintf(plik_blokady, "%d", getpid());
	fclose(plik_blokady);
 
	signal(SIGUSR1, handle_signal);
	signal(SIGINT, handle_ctrlc);
 
	while (1){
		sleep(1);
	}
	return 0;
}
