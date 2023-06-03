#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handleSIGUSR1();

int main(){
    struct sigaction newAction;
    newAction.sa_handler = handleSIGUSR1;
    sigemptyset (&newAction.sa_mask);
    newAction.sa_flags = 0;
    printf("PID: %d\n", getpid());
    sigaction(SIGUSR1, &newAction, NULL);
    while(1) {
        pause();
    }
    return 0;
}

void handleSIGUSR1(){
    printf("Otrzymano SIGUSR1 - zamykanie\n");
    exit(0);
}
