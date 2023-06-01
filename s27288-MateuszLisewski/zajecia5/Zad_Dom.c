#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int status;
    int i;
    unsigned int PID;

    for (i = 0; i < 2; i++)
    {
        PID = fork();
        if(PID == 0) 
            break;
    }
    if (PID == 0)
    {
        for (i = 0; i < 2; i++)
        {
            if(fork() == 0)
                break;
        }
    }
    while(wait(&status) < 0);

    return 0;
}