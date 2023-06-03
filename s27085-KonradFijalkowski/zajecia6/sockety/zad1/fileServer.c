#include "transfers.h"

void prepareServerAddress(struct sockaddr_in *address, int numerPortu);
void bindAddr(int socket, struct sockaddr_in *address);
void startListening(int socket);
void createHandleINT();
void handleINT();
bool checkFile(char* path);
void cleanup();
void blokujIP(char* ip);
size_t loadFileToBuffer(char* path);
bool checkIfBlocked(char* ip);
volatile sig_atomic_t wait = true;
char** blacklist;
FILE* plikLogow;
int listenSocket, newSock;
int liczbaIP = 0;

int main(int argc, char** argv){
    int numerPortu;
    struct sockaddr_in serverAddr, clientAddr;
    size_t rozmiarPliku;
    socklen_t addrLen = 0;
    char* ipKlienta;
    if((ipKlienta = malloc(INET_ADDRSTRLEN)) == NULL){
        printf("SERVER Couldn't allocate space for client's ip\n");
        exit(1);
    }
    if((blacklist = malloc(20*sizeof(char *))) == NULL){
        printf("SERVER Couldn't allocate space for blacklist\n");
        exit(1);
    }
    if((buffer = malloc(BUF_SIZE)) == NULL){
        printf("SERVER Couldn't allocate space for buffer");
        exit(1);
    }
    createHandleINT();
    checkArgumentNumber(2, argc);
    numerPortu = sprawdzNumerPortu(atoi(argv[1]));
    assignSocket(&listenSocket);
    printf("SERVER Socket created\n");
    prepareServerAddress(&serverAddr, numerPortu);
    bindAddr(listenSocket, &serverAddr);
    printf("SERVER Socket been assigned a name\n");
    startListening(listenSocket);
    printf("SERVER Socket is listening\n");
    plikLogow = fopen("logsFile.txt", "w");
    if(plikLogow == NULL){
        printf("ERROR Couldn't open log file - aborting");
        exit(1);
    }
    blokujIP("127.0.0.2");
    while(wait){
        addrLen = sizeof(clientAddr);
        newSock = accept(listenSocket, (struct sockaddr *) &clientAddr, &addrLen);
        inet_ntop(AF_INET, &clientAddr.sin_addr, ipKlienta, INET_ADDRSTRLEN);
        if(checkIfBlocked(ipKlienta)){
            printf("SERVER Blacklisted IP address refused: %s\n", ipKlienta);
            close(newSock);
            continue;
        }
        printf("\nSERVER Channel is open with %s\nSERVER Waiting for file name\n", ipKlienta);
        /*odczytuje nazwe pliku od klienta */
        readFromFD(newSock);
        if(wait == false) break;
        printf("SERVER Read file name: %s\n", buffer);
        fprintf(plikLogow, "Połączenie: %s:%d %s\n", ipKlienta, numerPortu, buffer);
        /*sprawdzam, czy ten plik istnieje*/
        if (checkFile(buffer)) {
            rozmiarPliku = loadFileToBuffer(buffer);
            writeToFD(newSock, buffer, rozmiarPliku);
        } else {
            writeToFD(newSock, NULL, -1);
            printf("SERVER File doesn't exist - closing connection\n");
        }
        memset(buffer, 0, BUF_SIZE);
        close(newSock);
    }
    cleanup();
    printf("SERVER Shutdown\n");
    return 0;
}
bool checkIfBlocked(char* ip){
    int i;
    for (i = 0; i < liczbaIP; i++) {
        if (strcmp(ip, blacklist[i]) == 0){
            return true;
        }
    }
    return false;
}

void cleanup(){
    int i;
    if (plikLogow != NULL) {
        fclose(plikLogow);
    }
    for (i = 0; i < liczbaIP; i++) {
        free(blacklist[i]);
    }
    free(blacklist);
    close(listenSocket);
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

void blokujIP(char* ip) {
    if((blacklist[liczbaIP] = malloc(strlen(ip) + 1)) == NULL){
        printf("SERVER Failed to block: %s\n", ip);
        exit(1);
    }
    strcpy(blacklist[liczbaIP], ip);
    liczbaIP++;

    printf("SERVER Blocked IP address: %s\n", ip);
}

bool checkFile(char* path){
    FILE* file = fopen(path, "r");
    printf("SERVER Check if file exists: %s\n", path);
    printf("SERVER File name length: %ld\n", strlen(path));
    if(file != NULL){
        return true;
    }
    return false;
}

size_t loadFileToBuffer(char* path){
    FILE* plik;
    size_t rozmiar;
    plik = fopen(path, "rb");
    fseek(plik, 0, SEEK_END);
    rozmiar = ftell(plik);
    fseek(plik, 0, SEEK_SET);
    fread(buffer, rozmiar,1, plik);
    fclose(plik);
    return rozmiar;
}