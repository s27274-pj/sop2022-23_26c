#include "transfers.h"

void prepareServerAddress(struct sockaddr_in *address, int numerPortu);
void bindAddr(int socket, struct sockaddr_in *address);
void startListening(int socket);
void createHandleINT();
void handleINT();
bool wait = true;

int main(int argc, char** argv){
    FILE* log;
    int numerPortu, dlugoscAdresuKlienta;
    int listenSocket, newSock;
    struct sockaddr_in serverAddr, clientAddr;
    if((buffer = malloc(1023)) == NULL){
        printf("Couldnt allocate buffer");
        exit(1);
    }
    createHandleINT();
    checkArgumentNumber(2, argc);
    numerPortu = sprawdzNumerPortu(atoi(argv[1]));
    if((log = fopen("/tmp/logOut", "a")) == NULL){
        printf("ERROR Couldnt open pog file - aborting");
        exit(1);
    }
    assignSocket(&listenSocket);
    prepareServerAddress(&serverAddr, numerPortu);
    bindAddr(listenSocket, &serverAddr);
    printf("SERVER Socket z sukcesem otrzymał nazwę\n");
    startListening(listenSocket);
    printf("SERVER Socket rozpoczął nasłuchiwanie\n");

    do {
        newSock = accept(listenSocket, (struct sockaddr *) &clientAddr, (socklen_t * ) &dlugoscAdresuKlienta);
        printf("SERVER Połączenie otwarte\n");
        readFromFD(newSock);
        close(newSock);

    }while(wait);
    free(buffer);
    fclose(log);
    close(listenSocket);
    return 0;
}

void prepareServerAddress(struct sockaddr_in *address, int numerPortu){
    memset(address, 0, sizeof(*address));
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(numerPortu);
}

void bindAddr(int socket, struct sockaddr_in *address){
    if(bind(socket, (struct sockaddr *)address, sizeof(*address)) == -1){
        close(socket);
        switch(errno){
            case EACCES:
                printf("Port nie jest dostępny. Zamykanie.\n");
                exit(1);
            case EINVAL:
                printf("Socket jest już w użyciu. Zamykanie.\n");
                exit(1);
            default:
                printf("Błąd przypisania nazwy dla socketu: %d\n", errno);
                exit(1);
        }
    }
}
void startListening(int socket){
    if (listen(socket, BACKLOG) == -1) {
        /*socket jest zajęty albo niepoprawnie skonfigurowany*/
        printf("Błąd nasłuchiwania");
        close(socket);
        exit(1);
    }
}

void createHandleINT(){
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handleINT;
    sigaction(SIGINT, &action, NULL);
}
void handleINT(){
    printf("\nWykryto sygnał przerwania pracy - zamykanie.\n");
    wait = false;
}
