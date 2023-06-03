#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int sum;
    pid_t child_pid = getpid();
    for (sum = 1; sum <= 100; sum++) {
        child_pid = fork();
        if (child_pid < 0) {
            printf("fork error");
            return 0;
        } else if (child_pid == 0) {
            printf("child nr %d PID %d PPID %d\n", sum, getpid(), getppid());
        } else {
            wait(NULL);
            break;
        }
    }
    if (child_pid != 0) {
        while (wait(NULL) > 0);
    }
    return 0;
}
