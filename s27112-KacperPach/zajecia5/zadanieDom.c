#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CHILDREN 100

int main(int argc, char const *argv[])
{
    int status, i;
    unsigned int childPID;

    for (i = 0; i < 2; i++)
    {
        childPID = fork();
        if(childPID == 0) 
            break;
    }
    if (childPID == 0)
    {
        for (i = 0; i < 2; i++)
        {
            if(fork() == 0)
                break;
        }
    }
        
    scanf("%d", &i);
    while(wait(&status) < 0);

    return 0;
}
