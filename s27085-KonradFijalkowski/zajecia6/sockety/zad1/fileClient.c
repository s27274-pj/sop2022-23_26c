#include "transfers.h"

void checkServerInfo(char* adresIP, char* portNumber, struct addrinfo * serverAddrInfo);
void connectToServer(int clientSocket, int portNumber);
void prepareHints(struct addrinfo *hints);
void askForFile();
int main(int argc, char** argv) {
    struct addrinfo * serverAddrInfo;
    int portNumber;
    int serverConSocket;
    char path[256];
    char* adresIP;
    checkArgumentNumber(3, argc);

    if((buffer = malloc(1023)) == NULL){
        printf("Couldnt allocate buffer");
        exit(1);
    }
    portNumber = sprawdzNumerPortu(atoi(argv[2]));
    adresIP = malloc(16);
    if(adresIP == NULL){
        perror("malloc");
        exit(2);
    }
    adresIP = argv[1];
    assignSocket(&serverConSocket);
    printf("CLIENT Utworzono socket\n");

    checkServerInfo(adresIP, argv[2], serverAddrInfo);

    connectToServer(serverConSocket, portNumber);
    printf("CLIENT Połączenie nawiązane\n");

    printf("Podaj nazwe pliku:\n");
    fgets(path, 255, stdin);
    writeToFD(serverConSocket, path, strlen(path));
    close(serverConSocket);
    free(buffer);
    return 0;
}

void checkServerInfo(char* adresIP, char* portNumber, struct addrinfo * serverAddrInfo){
    struct addrinfo hints;
    int error;
    prepareHints(&hints);
    error = getaddrinfo(adresIP, portNumber, &hints, &serverAddrInfo);
    if(error != 0){
        printf("Nie można uzyskać informacji o adresie server. Zamykanie");
        freeaddrinfo(serverAddrInfo);
        exit(1);
    }
}
void prepareHints(struct addrinfo *hints){
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_protocol = 0;
    hints->ai_flags = 0;
}

void connectToServer(int clientSocket, int portNumber){
    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1){
        close(clientSocket);
        switch(errno){
            case ECONNREFUSED:
                printf("Żaden socket nie nasłuchuje. Zamykanie\n");
                exit(1);
            default:
                printf("Błąd połączenia z serwerem. Zamykanie\n");
                exit(1);
        }
    }
}
