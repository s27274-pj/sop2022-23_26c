#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 		/* <fcntl.h> zawiera definicje stałych i funkcji związanych
						z operacjami na plikach. Wykorzystujemy ten nagłówek do 
						otwarcia pliku z flagami O_CREAT, O_WRONLY i O_EXCL. */

#define LOCK_FILE "/tmp/lock"

int lockFileDescriptor;
int whileLoopInit;

void cleanup() {
	printf("\nDeleting the lock file and terminating the program...\n");
    close(lockFileDescriptor);
    unlink(LOCK_FILE);
	whileLoopInit = 0;
}

void handle_ctrl_c(int sig) {
    exit(0);
}

void handle_usr1(int sig) {
    printf("WARNING: Another instance of this program is attempting to run!\n");
}

extern int kill(pid_t pid, int sig);

int main() {

    lockFileDescriptor = open(LOCK_FILE, O_CREAT | O_WRONLY | O_EXCL, 0644);

    if (lockFileDescriptor == -1) {
        int pid;
        FILE* file = fopen(LOCK_FILE, "r");
        if (file != NULL) {
            fscanf(file, "%d", &pid);
            fclose(file);
            kill(pid, SIGUSR1);
        }
        printf("An instance of this program is already running!\nTerminating...\n");
        exit(0);
    } else {
        int pid = getpid();
        FILE* file = fopen(LOCK_FILE, "w");
        if (file != NULL) {
            fprintf(file, "%d", pid);
            fclose(file);
        }
		signal(SIGUSR1, handle_usr1);
		signal(SIGINT, handle_ctrl_c);
        printf("First instance is running.\nLock file created.\nSwitching to standby mode (press 'ctrl+c' to terminate).\n");
    }
	
	atexit(cleanup);
	
	whileLoopInit = 1;
    
    /* Pętla nieskończona */
    while (whileLoopInit) {
        pause();
    }
    
    return 0;
}
