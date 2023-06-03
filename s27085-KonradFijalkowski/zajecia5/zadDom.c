#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    int liczbaPodzialow = 2, liczbaDzieci = 2, status;
    while (liczbaPodzialow > 0 && liczbaDzieci > 0){
        /* nie można dać tutaj alternatywy zamiast sumy, ponieważ wtedy jeden argument będzie spełniony
         *  rodzic będzie próbował dalej forkować, bo liczbaPodziałów nigdy się nie zmniejszy
         *  dzieci będą dalej forkować, bo liczba dzieci nigdy się nie zmniejszy
         */
        switch(fork()){
            case -1:
                perror("fork failure");
                exit(EXIT_FAILURE);
            case 0:
                liczbaDzieci = 2;
                liczbaPodzialow--;
                break;
            default:
                liczbaDzieci--;
                break;
        }
    }
    while(wait(&status) > 0);
    printf("Proces\nPID: %d  PPID: %d\n", getpid(), getppid());
    return 0;
}
