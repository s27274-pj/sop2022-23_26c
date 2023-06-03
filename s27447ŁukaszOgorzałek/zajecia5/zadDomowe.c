#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void create_child() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        printf("Failed to create a child process.\n");
        return;
    }

    if (pid == 0) {
        /* Kod procesu potomnego */
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
        fflush(stdout);
        exit(0);
    } else {
        wait(NULL);
    }
}

int main() {
    pid_t pidB, pidC;

    printf("Process A - PID: %d\n", getpid());

    /* Proces A tworzy proces B */
    pidB = fork();

    if (pidB < 0) {
        printf("Error during process B creation.\n");
        return 1;
    } else if (pidB == 0) {
        printf("Process B - PID: %d, PPID: %d\n", getpid(), getppid());
        /* Proces B tworzy D i E */
        create_child(); /* D */
        create_child(); /* E */
        exit(0);
    } else {
        wait(NULL);

        /* Proces A tworzy proces C */
        pidC = fork();
        if (pidC < 0) {
            printf("Error during process C creation.\n");
            return 1;
        } else if (pidC == 0) {
            printf("Process C - PID: %d, PPID: %d\n", getpid(), getppid());
            /* Process C tworzy proces F and G */
            create_child(); /* F */
            create_child(); /* G */
            exit(0);
        } else {
            wait(NULL);
        }
    }

    return 0;
}
