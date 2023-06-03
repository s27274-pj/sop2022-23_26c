#define _POSIX_SOURCE /*necessary to be able to use kill() function that sends singals to processes*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int shouldExit = 0;

void handleSignal(int sigId) {
    if (sigId == SIGUSR1) {
        printf("Detected attempt to create another instance of the program\n");
        fflush(stdout);
    } else if (sigId == SIGINT) {
        unlink("/tmp/lock"); /*safe deletes file*/
        shouldExit = 1;
    }
}

int main() {
    int pid;
    int charsRead;
    FILE * filePtr;
    if (access("/tmp/lock", F_OK) == 0) { /*access with F_OK returns 0 if file exists*/
        filePtr = fopen("/tmp/lock", "r");
        if (filePtr == NULL) {
            printf("Failed to open file");
            return 1;
        }
        charsRead = fscanf(filePtr, "%d", &pid);
        fclose(filePtr);
        if (charsRead == 0) {
            printf("Couldn't read PID from file");
            return 1;
        }
        kill(pid, SIGUSR1); /*sends SIGUSR1 signal to program with given pid*/
    } else {
        filePtr = fopen("/tmp/lock", "w");
        if (filePtr == NULL) {
            printf("Failed to open file");
            return 1;
        }
        fprintf(filePtr, "%d", getpid()); /*writes pid to file*/
        fclose(filePtr);
        signal(SIGUSR1, handleSignal);
        signal(SIGINT, handleSignal);
        while (shouldExit != 1) {
            sleep(1);
        }
    }
    return 0;
}
