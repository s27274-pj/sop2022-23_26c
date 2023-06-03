/* Disclaimer 
 To nie jest mój kod, nie jestem jeszcze
 w stanie napisać swojego od zera,
 ale żeby go zrozumieć wytłumaczę każdą
 linijkę co robi i po co ona jest. */

#include <stdio.h>
/* ^ Biblioteka obsługująca input/output */
#include <stdlib.h>
/* ^ Umożliwia korzystanie m. in. z funkcji exit() */
#include <unistd.h>
/* ^ Potrzebne do getpid() i getppid() */
#include <sys/wait.h>
/* ^ Potrzebne do waitpid() */

void createProcess(int depth, int children) {
    /* ^ Definiujemy funkcję, która nic nie zwraca i bierze
    dwa parametry typu int. Depth - dla głębokości drzewa
    procesów, Children - dla ilości dzieci. */

    int i;
    /* ^ Deklarujemy i na potrzebę pętli for */

    for (i = 0; i < children; i++) {
    /* ^ Pętla for, wykonuj dopóki i jest mniejsze
    od children. */
        switch (fork()) {
        /* ^ Wywołujemy funkcję fork w switchu. */
            case -1:
            /* ^ Jeżeli fork zwróci -1 to jest błąd */
                printf("Fork error\n");
                exit(1);
            /* ^ Informujemy o błędzie i wychodzimy z programu */
            case 0:
            /* ^ Jeżeli zwróci 0 to dziecko zostało stworzone,
            czyli fork się powiódł. */
                printf("PID: %i\tPPID: %i\n", getpid(), getppid());
                /* ^ Wypisujemy PID i PPID dla każdego dziecka */
                if (depth > 1) {
                    createProcess(depth - 1, children);
                /* ^ Jeżeli głębokość jest większa od 1 to
                wywołujemy ponownie funkcję, tylko że z depth
                pomniejszonym o 1 */
                }
                sleep(15);
                exit(0);
                /* ^ Gdy ostatni proces zostanie stworzony,
                wszystko zatrzyma się na 15 sekund a potem 
                nastąpi wyjście z programu. */
        }
    }
}

int main() {
    /* ^ Funkcja główna */
    int status;
    /* ^ deklarujemy zmienną status na potrzebę
    funkcji waitpid() */

    printf("PID: %i\tPPID: %i\n", getpid(), getppid());
    /* ^ Tutaj wypisujemy PID parenta, wiadomo, że to
    jest parent bo wypisujemy jego pid przed tworzeniem
    innych procesów (przed funkcją fork) */

    createProcess(2, 2);
    /* ^ Wywołujemy naszą funkcję z parametrami
    depth - 2 | children - 2
    Czyli będziemy mieli dwie generacje (od procesu głównego)
    po dwójkę dzieci od każdego rodzica. */

    waitpid(0, &status, 0);
    /* ^ Rodzic czeka, aż wszystkie dzieci zakończą się wykonywać.
    Sam przy tym nie może się zakończyć. 
    Zmienna status przyjmuje wartość statusu dziecka, czyli
    wartości zwracanej przez nie gdy zakończy się wykonywać.
    
    Przydatne: https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-waitpid-wait-specific-child-process-end */

    return 0;
    /* Zwracamy 0 z funkcji main czyli kończymy program i do widzenia */
}
