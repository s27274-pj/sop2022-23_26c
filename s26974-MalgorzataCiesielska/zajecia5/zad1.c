#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int data;
    pid_t pid = getpid(); /*process ID*/
    pid_t ppid = getppid(); /*parent process ID*/
    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);
    scanf("%d", &data);
    return 0;
}

/*to kill the process we need to use 'kill [PID]'*/
