#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    pid_t pid;
    int i;
    int number;
    if (argc < 2) {
        return 1;
    }
    number = atoi(argv[1]);
    switch (pid = fork()) {
        case -1: {
            printf("error");
            return 1;
        }
        case 0: { /*child process*/
            for (i = 1; i <= number; i++) {
                if (i % 2 != 0) {
                    printf("%d\n", i);
                }
            }
            return 0;
        }
        default: { /*parent process*/
            int status;
            int sum = 0;
            for (i = 0; i < number; i++) {
                sum += i;
            }
            waitpid(pid, &status, 0); /*parent waits for child to finish before printing the result*/
            printf("Sum: %d\n", sum);
        }
    }
    return 0;
}
