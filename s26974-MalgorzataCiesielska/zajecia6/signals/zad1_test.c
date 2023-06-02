#define _POSIX_SOURCE
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/*simple program to test if zad1 works as it should*/
int main() {
    pid_t pid;
    printf("Input pid: ");
    scanf("%d", &pid);
    kill(pid, SIGUSR1);
    return 0;
}
