#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid<0){
        printf("unsuccesfull fork");
        return 0;
    } else if (pid==0){
        printf("child process, PID = %d PPID = %d\n",getpid(),getppid());
    } else {
        wait(NULL);
        printf("parent process, PID = %d PPID = %d\n",getpid(),getppid());
    }
    return 0;
}
