#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int shouldExit = 0;

void handleSignal(int sigId) {
    shouldExit = 1;
}

int main() {
    signal(SIGINT, SIG_IGN); /*ignores interrupt signal (ctrl+c)*/
    signal(SIGUSR1, handleSignal);
    printf("PID: %d\n", getpid());
    fflush(stdout);
    while (shouldExit != 1) {
        sleep(1);
    }
    printf("Program ended\n");
    return 0;
}
