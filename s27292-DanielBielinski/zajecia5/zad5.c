#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int sum;
    pid_t child_pid;
    for(sum = 0 ; sum <= 100 ; sum++){
        child_pid = fork();
        if(child_pid < 0 ){
            printf("fork error");
            return 0;
        } else if (child_pid == 0){
            printf("child nr %d PID %d PPID %d\n",sum,getpid(),getppid());
            return 0;
        } else {
            wait(NULL);
        } 
    }
    while (wait(NULL)>0);
    return 0;
}
