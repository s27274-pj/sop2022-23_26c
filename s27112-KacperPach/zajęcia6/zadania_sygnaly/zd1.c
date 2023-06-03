#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler (int signum) {
    printf("otrzymalem sygnal\n");
    exit(0);
}

int main(int argc, char const *argv[])
{
    int pid = getpid();
    signal(SIGUSR1,handler );

    printf("PID: %d\n", pid);
    while (1)
    {
       
    }
    return 0;
}
