#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printIndent(int level) {
    int i;
    for (i = 0; i < level; i++) {
        printf("\t");
    }
}

void printTree(int level, int max_level) {
    int i;
    if (level >= max_level) {
        return;
    }
    for (i = 0; i < 2; i++) {
        pid_t child_pid = fork();
        if (child_pid < 0) {
            printf("fork error");
            return;
        } else if (child_pid == 0) {
            printIndent(level);
            printf("\\ pid %d, ppid %d\n", getpid(),getppid());
            printTree(level + 1, max_level);
            return;
        } else {
            wait(NULL);
        }
    }
}

int main() {
    printf("%d \\\n",getpid());
    printTree(1, 3);
    return 0;
}
