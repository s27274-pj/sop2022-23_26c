#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_child(int level, int max_level) {
    pid_t pid;

    if (level >= max_level) {
        return;
    }
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Nie udało się utworzyć procesu potomnego\n");
        exit (1);
    }
    else if (pid == 0) {
        printf("Proces potomny - PID: %d, PPID: %d\n", getpid(), getppid());
        create_child(level + 1, max_level);
        exit (0);
    }
    else {
        wait(NULL);
    }
}
int main() {
    printf("PID: %d\n", getpid());
    create_child(0, 100);
    return 0;
}
