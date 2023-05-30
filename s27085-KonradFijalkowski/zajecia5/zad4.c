#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main (){
    int liczbaProcesow = 100, status;
    /* opcja z forem
    pid = fork();
    for (i = 1; i < liczbaProcesow; ++i) {
        if(pid == 0){
            printf("Dziecko %d\n", i);
            pid = fork();
        }
        if(pid > 0){
            waitpid(0, &status, 0);
        }
        if(pid < 0){
            perror("Proces creation error");
            exit(EXIT_FAILURE);
        }
        if(i == 99){
            getchar();
        }

    }
     */
    while (liczbaProcesow) {
        switch (fork()) {
            case -1:
                perror("Nie utworzono procesu");
                exit(EXIT_FAILURE);
            case 0:
                printf("Proces %d\nPID: %d  PPID: %d\n", liczbaProcesow, getpid(), getppid());
                liczbaProcesow -= 1;
                break;
            default:
                waitpid(0, &status, 0);
                return 0;
        }
    }
    return 0;
}
