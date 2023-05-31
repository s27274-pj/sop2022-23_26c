#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int depth = 0;
    int children = 0;
    while (depth < 2 && children < 2) { 
        pid_t pid = fork();
        if (pid == 0) {
            children = 0;
            depth++;
        } else {
            children++;
        }
    }
    return 0;
}