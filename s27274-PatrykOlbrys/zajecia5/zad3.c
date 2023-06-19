#include <stdio.h>
/* ^ Nagłówek wymagany do wejścia/wyjścia */
#include <sys/types.h>
#include <unistd.h>
/* ^ Dwa nagłówki wymagane do getpid() i getppid() */
#include <sys/wait.h>
/* ^ Nagłówek wymagany do użycia funkcji waitpid() */
#include <stdlib.h>
/* ^ Umożliwia korzystanie z atoi */

int main(int argc, char **argv) {
    pid_t p;
    int status, i;
    int sum = 0;
    int arg1 = atoi(argv[1]);

    p = fork();
    /* ^ Uruchamiamy podproces */

    switch (p) {
        case -1:
            /* Błąd */
            break;
        case 0:
            /* Dziecko */
            printf("Liczby nieparzyste od 1 do %d\n", arg1);
            for (i = 1; i <= arg1; i++) {
                if (i % 2 != 0) {
                    printf("%d\n", i);
                }
            }

            fflush(stdout);
            break;
        default:
            /* Rodzic */

            for (i = 0; i <= arg1; i++) {
                sum += i;
            }
            printf("Suma liczb od 0 do %d\n", arg1);
            printf("%d\n", sum);

            fflush(stdout);
            /* ^ Żeby dobrze wydrukowało się na ekranie, 
            możemy wymusić spłukanie bufora. */
            break;
    }

    return 0;
}
