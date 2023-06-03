#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signalHandler(int signum) {
    if (signum == SIGUSR1) {
        printf("Received signal SIGUSR1. Closing the program.\n");
        exit(0);
    }
}

int main() {
    /* Wypisanie PID programu */
    printf("PID: %d\n", getpid());

    /* Ustawienie obsługi sygnału SIGUSR1 */
    signal(SIGUSR1, signalHandler);

    /* Pętla nieskończona */
    while (1) {
        /* Czekanie na sygnał */
        pause();
    }

    return 0;
}
