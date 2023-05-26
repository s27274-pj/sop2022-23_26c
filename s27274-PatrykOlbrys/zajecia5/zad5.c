#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROCESSES_TO_SPAWN 10
/* ^ Procesy do stworzenia zdefiniowane globalnie */

int child() {
    printf("PID: %d\tPPID: %d\n", getpid(), getppid());
    /* ^ Wyświetlamy pid i ppid każdego dziecka */
    while(1) {
        pause();
        /* ^ Każde dziecko ma czekać po stworzeniu */
    }
    return 0;
}

int main() {
    int status, i;
    /* ^ Deklaracja statusu */

    for (i = 0; i < PROCESSES_TO_SPAWN; i += 1) {
        switch (fork()) {
            /* ^ Chcemy stworzyć wiele dzieci,
            które wychodzą bezpośrednio od tego samego rodzica,
            dlatego cały czas forkujemy ten sam proces którym jest
            właśnie ten rodzic, bo dziecko cały czas czeka w swojej
            funkcji wyżej */
        case -1:
            fprintf(stderr, "Błąd przy forku\n");
            return 0;
        case 0:
            /* Dziecko */
            /* Dziecko z funkcji fork ma zawsze zwracane 0 */
            return child();
            /* ^ Zwracamy dziecko i kontunuujemy pętlę */
        }
    }

    waitpid(0, &status, 0);

    return 0;
}
