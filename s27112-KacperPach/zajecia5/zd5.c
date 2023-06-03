#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CHILDREN 100

int main(int argc, char const *argv[])
{
    unsigned int childPid;
    int status, i;

    for (i = 0; i < MAX_CHILDREN; i++)
    {
        if(fork() == 0) 
            break;
    }
    
    while(wait(&status) < 0);

    return 0;
}
