#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    unsigned int childPid;
    int status, i, sum = 0;

    if (argc < 2)
    {
        return 1;
    }
    
    childPid = fork();
    
    if (childPid == 0)
    {
        for (i = 0; i < atoi(argv[1]); i++)
        {
            if (i % 2 == 1)
                printf("%d ", i );
        }
        printf("\n");
    } 
    else 
    {
        waitpid(childPid, &status, WIFEXITED(childPid));
        for ( i = 0; i <= atoi(argv[1]); i++)
        {
            sum += i;
        }
        printf("suma: %d\n", sum);
    }
    
    return 0;
}
