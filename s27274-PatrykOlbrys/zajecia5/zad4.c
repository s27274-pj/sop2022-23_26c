#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int processes_to_spawn = 10, status;
    /* ^ Liczba procesów do stworzenia
    i deklaracja statusu */

while (processes_to_spawn) {
    /* ^ Kiedy proces się stworzy 
        wracamy do tej linijki
        i tworzymy nowy proces,
        który jest jego dzieckiem */
        switch (fork()) {
        case -1:
            fprintf(stderr, "Błąd przy forku\n");
            return 0;
        case 0:
            /* Dziecko */
            /* Dziecko z funkcji fork ma zawsze zwracane 0 */

            printf("PID: %d\tPPID: %d\n", getpid(), getppid());
            processes_to_spawn -= 1;
            /* ^ Wszystkie zmienne w forku są przekazywane do dziecka
            tak więc każde kolejne dziecko będzie miało o 1 mniej
            procesów do stworzenia */
            break;
        default:
            /* Rodzic */
            printf("Procesów do stworzenia: %d\n", processes_to_spawn - 1);
            waitpid(0, &status, 0);
            return 0;
    }
}
    return 0;
}
