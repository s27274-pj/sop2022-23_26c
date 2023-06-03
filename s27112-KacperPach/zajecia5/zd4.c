#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CHILDREN 100

int main(int argc, char const *argv[])
{
    unsigned int childPid;
    int status, count = 0;
    
    do
    {
       childPid = fork();
       count++;
    } while (childPid == 0 && count < MAX_CHILDREN);
    
    if (childPid != 0)
        waitpid(childPid, &status, WIFEXITED(childPid));

    return 0;
}
