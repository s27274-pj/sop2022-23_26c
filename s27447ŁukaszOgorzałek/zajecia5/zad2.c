#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Failed to create a child process.\n");
        return 1;
    } else if (pid == 0) {
        printf("CHILD - PID: %d, PPID: %d\n", getpid(), getppid());
    } else {
        printf("PARENT - PID: %d, PPID: %d\n", getpid(), getppid());
        wait(NULL);
    }

    return 0;
}
