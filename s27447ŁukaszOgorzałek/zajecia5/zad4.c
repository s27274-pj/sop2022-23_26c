#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create_process(int level) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Failed to create a child process.\n");
        exit(1);
    } else if (child_pid == 0) {
        /* Kod procesu potomnego */
        printf("CHILD (PID: %d, PPID: %d, LEVEL: %d)\n", getpid(), getppid(), level);
        if (level < 10) {
            create_process(level + 1);
        } else if (level == 10) {
			printf("\n~INFO: the last (%d) CHILD has been created~\n\n", level);
		}
        exit(0);
    } else {
        /* Kod procesu rodzica */
        wait(NULL);
		if (level == 10) {
            /* Oczekiwanie na dane od użytkownika */
            printf("Try \"pstree\" in another terminal, then press \"enter\" to continue.\n");
            getchar();
		}
    }
}

int main() {
    create_process(1);
	
    printf("Try \"pstree\" in another terminal again to see the difference.\n");
	
    return 0;
}

/*
w programie używamy funkcji "fork()" do tworzenia kolejnych procesów potomnych. 
każdy proces potomny, jeśli poziom (liczba dzieci do wygenerowania) jest mniejszy niż 10,
tworzy kolejny proces potomny rekurencyjnie. Całość zamknięta jest w funkcji "create_process()",

aby zwiększyć lub zmniejszyć liczbę wygenerowanych procesów potomnych, wystarczy
zmienić warunek w ifie w linijce 16 (i 25, ale to tylko do sprawdzenia jak wygląda
drzewko procesów).
*/
