#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int n = 100;
    while (n > 0)
    {
        pid = fork();
        if (pid == 0) { /*child process*/
            printf("#%d PID %d [PARENT ID %d]\n", 101-n, getpid(), getppid());
            n--;
        } else { /*parent process, waits for its child to finish and returns*/
            int status;   
            waitpid(pid, &status, 0);
            return 0;
        }
    }
    return 0;
}
