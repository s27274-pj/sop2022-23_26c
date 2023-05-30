#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main (){
    int liczbaProcesow = 5, cpid, status;
    while (liczbaProcesow) {
        switch (fork()) {
            case -1:
                perror("Nie utworzono procesu");
                exit(EXIT_FAILURE);
            case 0:
                printf("Proces %d\nPID: %d  PPID: %d\n", liczbaProcesow, getpid(), getppid());
                return 0;
            default:
                liczbaProcesow-=1;
                break;
        }
    }
    while(wait(&status) > 0);
    return 0;

}
