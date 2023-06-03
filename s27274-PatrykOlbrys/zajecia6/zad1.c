#define _POSIX_SOURCE
/* ^ Bez tego sigset_t jest undefined
Source: https://bytes.com/topic/c/answers/215198-sigset_t-gcc */

#include <stdio.h>
/* ^ Nagłówek wymagany do wejścia/wyjścia */

#include <sys/types.h>
#include <unistd.h>
/* ^ Dwa nagłówki wymagane do getpid() */

#include <signal.h>
/* ^ Potrzebne do sigset_t */

#include <stdbool.h>
/* ^ Potrzebne do obsługi booleanów 
bo bool to nie jest built in type w C*/


void registerHandler();
void signalHandler(int);
bool wait = true;

int main() {
    pid_t pid = getpid();

    printf("PID: %d\n", pid);

    while (wait) {
        pause();
    }
    printf("Koniec programu.");

    return 0;
}

void signalHandler(int s) {
    printf("Otrzymano sygnal USR1. s = %d\n", s);
    wait = false;
}

void registerHandler() {
    sigset_t iset;
    struct sigaction act;

    sigemptyset(&iset);

    act.sa_handler = &signalHandler;
    act.sa_mask = iset;
    act.sa_flags = 0;

    sigaction(SIGUSR1, &act, NULL);
}
