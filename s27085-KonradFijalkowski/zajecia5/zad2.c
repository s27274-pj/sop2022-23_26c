#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void printPids(){
    printf("D: %d\n", getpid());
    printf("P: %d\n", getppid());
}

int main(){
    pid_t parentPid = getpid();
    pid_t pid = fork();
    int status = 0;
    if(pid >= 0){
        printPids();
    }
    if(parentPid == getpid()){
        waitpid(0, &status, 0);
    }

    return 0;
}
