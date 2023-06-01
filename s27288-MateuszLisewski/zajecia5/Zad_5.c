#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, terminated_pid;
    int status, i;
    int number_of_children = 10;

    printf("Proces główny - PID: %d, PPID: %d\n", getpid(), getppid());

    for (i = 0; i < number_of_children; i++) {
        child_pid = fork();

        if (child_pid < 0) {
            fprintf(stderr, "Nie udało się utworzyć procesu potomnego\n");
            exit (1);
        }
        else if (child_pid == 0) {
            printf("Proces potomny - PID: %d, PPID: %d\n", getpid(), getppid());
            exit (0);
        }
    }

    for (i = 0; i < number_of_children; i++) {
        terminated_pid = waitpid(-1, &status, 0);
        printf("Proces potomny - PID: %d, zakonczony status: %d\n", terminated_pid, status);
    }
    printf("Proces rodzica. Procesy potomne zakonczyly dzialanie.\n");
    return 0;
}
