#include <stdio.h>
/* ^ Nagłówek wymagany do wejścia/wyjścia */
#include <sys/types.h>
#include <unistd.h>
/* ^ Dwa nagłówki wymagane do getpid() i getppid() */
#include <sys/wait.h>
/* ^ Nagłówek wymagany do użycia funkcji waitpid() */

int main() {
    pid_t p;
    int status;

    p = fork();
    /* ^ Uruchamiamy podproces */

    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    /* ^ Drukujemy adresy procesów */

    switch (p) {
        case -1:
            /* Błąd */
            break;
        case 0:
            /* Dziecko */
            fflush(stdout);
            break;
        default:
            /* Rodzic */
            waitpid(p, &status, 0);
            /* ^ Rodzic czeka na dziecko */
            fflush(stdout);
            /* ^ Żeby dobrze wydrukowało się na ekranie, 
            możemy wymusić spłukanie bufora. */
            break;
    }

    return 0;
}
