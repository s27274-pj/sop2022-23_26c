#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int n = 100;
    pid_t pid = fork(); /*creating the first child process*/
    while (n > 0) {
        if (pid == 0) { /*if we're a child process we want to break and exit the program*/
            break; 
        } else { /*parent process prints info about created child, waits for child to finish, and creates another child*/
            int status;   
            printf("PID %d created child #%d [%d]\n", getpid(), 101 - n, pid);
            waitpid(pid, &status, 0);
            pid = fork();
            n--;
        }
    }
    return 0;
}
