#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        printf("Error");
    } else if (pid == 0) { /*child process*/
        printf("C PID: %d\n", getpid());
        printf("C PPID: %d\n", getppid());
    } else { /*parent process*/
        int status;   
        waitpid(pid, &status, 0); /*waiting till child finishes*/
        printf("P PID: %d\n", getpid());
        printf("P PPID: %d\n", getppid());
    }
    return 0;
}
