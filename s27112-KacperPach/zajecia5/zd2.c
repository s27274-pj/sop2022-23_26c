#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    unsigned int childPid;
    int status;
    childPid = fork();

    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    if (childPid != 0)
        waitpid(childPid, &status, WIFEXITED(childPid));

    return 0;
}
