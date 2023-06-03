#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void run_child_processes() {
    pid_t child_pid[10]; 		/* Tablica na PID-y procesów potomnych */
    int i;

    /* Tworzenie 10 procesów potomnych */
    for (i = 0; i < 10; i++) {
        child_pid[i] = fork();
		
        if (child_pid[i] == -1) {
            perror("Failed to create a child process.\n");
            exit(1);
        } else if (child_pid[i] == 0) {
            /* Kod procesu potomnego */
            printf("CHILD %d (PID: %d, PPID: %d)\n", i + 1, getpid(), getppid());
            exit(0);
        }
    }

    /* Oczekiwanie na zakończenie procesów potomnych w odwrotnej kolejności */
    for (i = 9; i >= 0; i--) {
        int status;
        pid_t terminated_child = waitpid(child_pid[i], &status, 0);
        if (WIFEXITED(status)) {
            printf("CHILD process %d (PID: %d) terminated successfully\n", i + 1, terminated_child);
        } else {
            printf("ERROR: CHILD process %d (PID: %d) terminated unsuccessfully\n", i + 1, terminated_child);
        }
    }
}

int main() {
    run_child_processes();
    return 0;
}

/*
w programie w funkcji "run_child_processes()" utworzyliśmy tablicę "child_pid[]" 
na 10 PID-ów procesów potomnych. Następnie w pętli tworzymy procesy potomne i zapisujemy
ich PID-y w tablicy. Po utworzeniu wszystkich procesów potomnych, przechodzimy 
przez tablicę child_pid w odwrotnej kolejności (od indeksu 9 do 0) i używamy funkcji 
"waitpid()" do oczekiwania na zakończenie każdego procesu potomnego w odpowiedniej kolejności. 
(od ostatniego utworzonego do pierwszego).

[*] jeśli chodzi o wyświetlanie komunikatów w odpowiedniej kolejności, to mogą się one 
wyświetlać różnie, poniewaz wynika to z mechanizmów planowania procesów w systemie operacyjnym.

kiedy procesy potomne i proces rodzica wykonują swoje zadania równolegle, kolejność wypisywania 
komunikatów może być nieokreślona. Zależy to od tego, jak system operacyjny zarządza czasem procesora
dla każdego procesu i jakie priorytety przydziela.

w przypadku, gdy zachowanie wyświetlania komunikatów jest ważne, można skorzystać z mechanizmów
synchronizacji, takich jak np. semafory, które pozwalają na kontrolowanie kolejności wykonywania
procesów i wypisywania komunikatów w określonym porządku. Niestety oprócz tego, że wiem, 
iż takie mechanizmy istnieją, to nie mam pojęcia w jaki sposób się je stosuje.
*/
