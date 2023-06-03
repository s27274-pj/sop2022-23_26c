#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int parentSum(int addTillNumber){
    int sum = 0, i;
    for(i = 1; i <= addTillNumber; i++){
        sum += i;
    }
    return sum;
}

int childSum(int addTillNumber){
    int sum = 0, i;
    for(i = 1; i <= addTillNumber; i+=2){
        sum += i;
    }
    return sum;
}

int main(int argc, char ** argv){
    int firstArg = atoi(argv[1]);
    int status = 0;
    pid_t pid = fork();
    if(pid>0){
        waitpid(0, &status, 0);
        printf("Suma rodzica: %d\n", parentSum(firstArg));
    }
    if(pid == 0){
        printf("Suma dziecka: %d\n", childSum(firstArg));
    }
    return 0;
}
