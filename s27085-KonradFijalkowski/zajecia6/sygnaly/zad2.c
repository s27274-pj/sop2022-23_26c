#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

const char lockFilePath[] = "/tmp/lock";

void handleSIGINT();
void handleSIGUSR1();
void registerHandlerUSR1();
void registerHandlerINT();
bool wait = true;

int main(){
    FILE* plikLocku;
    int pidProcesu;
    /*access sprawdza dostęp realnego użytkownika do pliku lub czy plik w ogóle istnieje*/
    if(access(lockFilePath, F_OK) == 0){
        plikLocku = fopen(lockFilePath, "r");
        fscanf(plikLocku, "%d[^n]", &pidProcesu);
        printf("%d\n", pidProcesu);
        fclose(plikLocku);
        kill(pidProcesu, SIGUSR1);
    }
    else{
        /*ustaw handlery*/
        registerHandlerUSR1();
        registerHandlerINT();
        plikLocku = fopen(lockFilePath, "w");
        /*zapisz pid do pliku*/
        fprintf(plikLocku, "%d %c", getpid(), '\n');
        /*pause w pętli, bo tak po pierwszym obsłużeniu odebranego sygnału program by się zakończył*/
        fclose(plikLocku);
        while(wait){
            pause();
        }
    }
    return 0;
}

void registerHandlerUSR1(){
    struct sigaction action;
    /*ustaw właściwości sigaction*/
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handleSIGUSR1;
    sigaction(SIGUSR1, &action, NULL);
}

void registerHandlerINT(){
    struct sigaction action;
    /*ustaw właściwości sigaction*/
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handleSIGINT;
    sigaction(SIGINT, &action, NULL);
}

void handleSIGUSR1(){
    registerHandlerUSR1();
    printf("Wykryto próbę uruchomienia drugiej instancji programu.\n");
}
void handleSIGINT(){
    registerHandlerINT();
    printf("\nOtrzymano SIGINT - zamykanie\n");
    /*usuń plik z lockiem*/
    remove(lockFilePath);
    /*pozwól zakończyć się pause*/
    wait = false;
}
