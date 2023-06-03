#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void childProcess(int limit) {
    int i;
    printf("Proces potomny: Liczby nieparzyste od 1 do %d\n", limit);
    for (i = 1; i <= limit; i++) {
        if (i % 2 != 0) {
            printf("%d\n", i);
        }
    }
}

void parentProcess(int limit) {
    int i;
    int sum = 0;
    printf("Proces rodzica: Obliczenie sumy liczb od 0 do %d\n", limit);
    for (i = 0; i <= limit; i++) {
        sum += i;
    }
    printf("Suma: %d\n", sum);
}

int main(int argc, char *argv[]) {
    int limit;
    pid_t pid;
    if (argc != 2) {
        fprintf(stderr, "Niepoprawna liczba argumentow\n");
        return 1;
    }
    limit = atoi(argv[1]);
    if (limit <= 0) {
        fprintf(stderr, "Niepoprawny wartosc argumentu\n");
        return 1;
    }
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Nie udalo sie utworzyc procesu potomnego\n");
        return 1;
    }
    else if (pid == 0) {
        childProcess(limit);
    }
    else {
        wait(NULL);
        parentProcess(limit);
    }
    return 0;
}
