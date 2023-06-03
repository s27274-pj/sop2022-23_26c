#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    int sum,i;
    int arg = atoi(argv[1]);
    pid_t pid = fork();
    if(argc!=2){
        printf("please run it with 1 argument\n");
        return 0;
    }
    if(pid < 0 ){
        printf("fork error");
        return 1;
    } else if (pid == 0){
        for(i=1;i<=arg;i++){
                if(i % 2 == 1){
                printf("%d\n",i);
            }
        }
    } else {
        wait(NULL);
        for(i=0;i<=arg;i++){
            sum+=i;
        }
        printf("Sum = %d\n", sum);
    }
    return 0;
}
