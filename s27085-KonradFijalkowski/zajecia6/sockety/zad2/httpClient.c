#include "transfers.h"

void checkServerInfo(char* adresIP, char* portNumber, struct addrinfo * serverAddrInfo);
void connectToServer(int clientSocket, int portNumber, char* ip);

int main(int argc, char** argv) {
    FILE* saveFile;
    int portNumber;
    int serverConSocket;
    char path[256];
    char* adresIP;
    int rozmiarPliku;
    char wybor;
    checkArgumentNumber(3, argc);

    if((buffer = malloc(1024)) == NULL){
        printf("Couldn't allocate buffer");
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
    printf("CLIENT Socket created\n");
    connectToServer(serverConSocket, portNumber, adresIP);
    printf("CLIENT Channel secured\n");

    printf("CLIENT Provide file name:\t");
    fgets(path, 255, stdin);

    /*wysyłam nazwe pliku*/
    writeToFD(serverConSocket, path, strlen(path)-1);
    /*otrzymuje rozmiar porządanego pliku*/
    switch(rozmiarPliku = readFromFD(serverConSocket)){
        case -1:
            printf("CLIENT File not found on server - aborting\n");
            close(serverConSocket);
            free(buffer);
            return 0;
        case -2:
            printf("CLIENT Server closed channel - aborting\n");
            close(serverConSocket);
            free(buffer);
            return 0;
        default:
            break;
    }
    printf("CLIENT File data size: %d\n", rozmiarPliku);
    printf("CLIENT Show file content [y/n]:\t");
    scanf("%c", &wybor);
    fflush(stdin);
    if(wybor == 'y'){
        printf("CLIENT File content:\n%s\n", buffer);
    }
    saveFile = fopen("output.txt", "w");
    fwrite(buffer, rozmiarPliku, 1, saveFile);
    fclose(saveFile);

    close(serverConSocket);
    free(buffer);
    return 0;
}


void connectToServer(int clientSocket, int portNumber, char* ip){
    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1){
        close(clientSocket);
        switch(errno){
            case ECONNREFUSED:
                printf("No socket found listening - aborting\n");
                exit(1);
            default:
                printf("Connection error errno: %d\n", errno);
                exit(1);
        }
    }
}
