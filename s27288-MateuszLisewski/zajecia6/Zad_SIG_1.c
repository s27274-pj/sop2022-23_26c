#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int pid;

void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Otrzymano sygnal SIGUSR1. Wyjście...\n");
        _exit(0);
    }
}

int main() {
    pid = getpid();
    printf("PID: %d\n", pid);

    signal(SIGUSR1, signal_handler);

    while (1) {
        printf("Oczekiwanie na sygnal...\n");
        sleep(1);
        }

    return 0;
}
