#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_process(int n) {
    int i;

    printf("CHILD: (PID: %d): Odd numbers from 1 to %d\n", getpid(), n);
    for (i = 1; i <= n; i += 2) {
        printf("%d ", i);
        fflush(stdout);
    }
    printf("\n");
    exit(0);
}

void parent_process(int n) {
    int sum = 0;
    int i;

    printf("PARENT (PID: %d): The sum of numbers from 0 to %d = ", getpid(), n);
    for (i = 0; i <= n; i++) {
        sum += i;
    }
    printf("%d\n", sum);
    exit(0);
}

int main(int argc, char *argv[]) {
	int n;
	pid_t child_pid;
		
    if (argc != 2) {
        printf("Please enter an integer as an argument!\n");
        return 1;
    }
	
	n = atoi(argv[1]);

    child_pid = fork();

    if (child_pid == -1) {
        perror("Failed to create a child process\n");
        return 1;
    } else if (child_pid == 0) {
        /* Kod procesu potomnego */
        child_process(n);
    } else {
        /* Kod procesu rodzica */
        int status;
        waitpid(child_pid, &status, 0);
        parent_process(n);
    }

    return 0;
}

/*
program przyjmuje jedną liczbę całkowitą jako argument wywołania. Po utworzeniu 
procesu potomnego, proces rodzica oblicza sumę liczb od 0 do podanej liczby, 
a proces potomny wypisuje liczby nieparzyste od 1 do podanej liczby. Wyniki 
są wypisywane w kolejności, w której najpierw wypisywane są liczby nieparzyste 
przez proces potomny, a następnie suma przez proces rodzica. 

program korzysta z funkcji "fork()" do utworzenia procesu potomnego, 
a następnie funkcji "waitpid()" do oczekiwania na zakończenie 
procesu potomnego przez proces rodzica.
*/
