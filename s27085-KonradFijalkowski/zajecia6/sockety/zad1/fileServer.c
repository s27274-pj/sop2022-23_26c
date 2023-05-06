#include "transfers.h"

void prepareServerAddress(struct sockaddr_in *address, int numerPortu);
void bindAddr(int socket, struct sockaddr_in *address);
void startListening(int socket);
void createHandleINT();
void handleINT();
bool checkFile(char* path);
size_t loadFileToBuffer(char* path);
volatile sig_atomic_t wait = true;

int main(int argc, char** argv){
    FILE* log;
    int numerPortu, dlugoscAdresuKlienta;
    int listenSocket, newSock;
    struct sockaddr_in serverAddr, clientAddr;
    size_t rozmiarPliku;

    if((buffer = malloc(1024)) == NULL){
        printf("Couldn't allocate space for buffer");
        exit(1);
    }
    createHandleINT();
    checkArgumentNumber(2, argc);
    numerPortu = sprawdzNumerPortu(atoi(argv[1]));
    if((log = fopen("/tmp/logOut", "a")) == NULL){
        printf("ERROR Couldn't open log file - aborting");
        exit(1);
    }
    assignSocket(&listenSocket);
    printf("SERVER Socket created\n");
    prepareServerAddress(&serverAddr, numerPortu);
    bindAddr(listenSocket, &serverAddr);
    printf("SERVER Socket been assigned a name\n");
    startListening(listenSocket);
    printf("SERVER Socket is listening\n");

    while(wait) {
        newSock = accept(listenSocket, (struct sockaddr *) &clientAddr, (socklen_t * ) &dlugoscAdresuKlienta);
        printf("\nSERVER Channel is open\nSERVER Waiting for file name\n");
        /*odczytuje nazwe pliku od klienta */
        readFromFD(newSock);
        printf("SERVER Read file name: %s\n", buffer);
        /*sprawdzam, czy ten plik istnieje*/
        if (checkFile(buffer)) {
            rozmiarPliku = loadFileToBuffer(buffer);
            writeToFD(newSock, buffer, rozmiarPliku);
        } else {
            writeToFD(newSock, "", -1);
            printf("SERVER File doesn't exist - closing connection\n");
        }
        bzero(buffer, BUF_SIZE);
        close(newSock);
    }
    free(buffer);
    fclose(log);
    close(listenSocket);
    printf("SERVER Shutdown\n");
    return 0;
}

void prepareServerAddress(struct sockaddr_in *address, int numerPortu){
    memset(address, 0, sizeof(*address));
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = inet_addr("127.0.0.1");
    address->sin_port = htons(numerPortu);
}

void bindAddr(int socket, struct sockaddr_in *address){
    if(bind(socket, (struct sockaddr *)address, sizeof(*address)) == -1){
        close(socket);
        switch(errno){
            case EACCES:
                printf("Port is not accessible\n");
                exit(1);
            case EINVAL:
                printf("Socket is in use\n");
                exit(1);
            default:
                printf("Socket error errno: %d\n", errno);
                exit(1);
        }
    }
}
void startListening(int socket){
    if (listen(socket, BACKLOG) == -1) {
        /*socket jest zajęty albo niepoprawnie skonfigurowany*/
        printf("Listen error");
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
    printf("\nINT signal detected - aborting.\n");
    wait = false;
}

bool checkFile(char* path){
    FILE* file = fopen(path, "r");
    printf("SERVER Check if file exists: |%s|\n", path);
    printf("SERVER File name length: %ld\n", strlen(path));
    if(file != NULL){
        return true;
    }
    return false;
}

size_t loadFileToBuffer(char* path){
    FILE* plik;
    size_t rozmiar = 0L;
    plik = fopen(path, "rb");
    fseek(plik, 0, SEEK_END);
    rozmiar = ftell(plik);
    fseek(plik, 0, SEEK_SET);
    fread(buffer, rozmiar,1, plik);
    printf("Buffor: %s\n", buffer);
    fclose(plik);
    return rozmiar;
}
