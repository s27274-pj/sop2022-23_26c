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


bool wait = true;
FILE *fptr;
int pidFromFile;
/* ^ Store the content of the file */

void registerHandlerUSR1();
void registerHandlerINT();


void createLockFile() {
    pid_t pid = getpid();

    fptr = fopen("/tmp/lock", "w");
    /* Tworzymy plik /tmp/lock */

    /* fwrite(&pid, sizeof(pid), 1, fptr); */
    fprintf(fptr, "%d", pid);
    /* ^ Zapisujemy pid do pliku*/
    fclose(fptr);
    printf("Stworzono plik /tmp/lock\n");
}

void handleUSR1(int s) {
    registerHandlerUSR1();
    printf("Wykryto probe uruchomienia drugiej instancji programu.");
}

void handleINT(int s) {
    /* ^ Handle SIGINT czyli wtedy kiedy
    zostanie naciśnięte CTRL+C */
    registerHandlerINT();
    printf("Got INT ");

    remove("tmp/lock");

    wait = false;
}

void startNormally() {
    createLockFile();
    registerHandlerUSR1();
    registerHandlerINT();

    while (wait) {
        /* pause(); */
        sleep(1000);
    }
}

void registerHandlerUSR1() {
    sigset_t iset;
    struct sigaction act;

    sigemptyset(&iset);
    
    act.sa_handler = &handleUSR1;
    act.sa_mask = iset;
    act.sa_flags = 0;

    sigaction(SIGUSR1, &act, NULL);
}

void registerHandlerINT() {
    sigset_t iset;
    struct sigaction act;

    sigemptyset(&iset);

    act.sa_handler = &handleINT;
    act.sa_mask = iset;
    act.sa_flags = 0;

    sigaction(SIGINT, &act, NULL);
}


void sendSignal(int signalNumber, int otherInstancePid) {
    kill(otherInstancePid, signalNumber);
    /* ^ kill służy do wysłania sygnału 
    do pida drugiego procesu tego programu z numerem sygnału */
}

int loadPidFromLockFile() {
    fptr = fopen("tmp/lock", "r");
    pidFromFile = fscanf(fptr, "%d", &pidFromFile);
    fclose(fptr);

    /* DEBUG */
    printf("%d", pidFromFile);

    return pidFromFile;
}

void sendSignalAndQuit() {
    int otherInstancePid = loadPidFromLockFile();
    sendSignal(SIGUSR1, otherInstancePid);
}

int main() {
    if (access("tmp/lock", F_OK) == 0) {
    /* file exists */
    sendSignalAndQuit();
    } else {
    /* file doesn't exist */
    startNormally();
    }
    return 0;
}
