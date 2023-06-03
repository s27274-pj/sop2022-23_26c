#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("Proces potomny - PID: %d, PPID: %d\n", getpid(), getppid());
        return 0;
    }
    else {
        printf("Proces rodzica - PID: %d, PPID: %d\n", getpid(), getppid());
        wait(NULL);
        printf("Proces rodzica. Process potomny zakonczyl dzialanie.\n");
        return 0;
    }
}
