#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void logToFile(const char *logMessage) {
    FILE *logFile = fopen("server.log", "a");
    if (logFile == NULL) {
        perror("Blad otwierania pliku .log");
        return;
    }

    fprintf(logFile, "%s\n", logMessage);
    fclose(logFile);
}

int main(int argc, char *argv[]) {
    int serverSocket, clientSocket;
    int fileSize;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientLength;
    FILE *file;

    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Blad tworzenia gniazda");
        return 1;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(atoi(argv[2]));

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Blad laczenia gniazda");
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 1) == -1) {
        perror("Blad nasluchiwania gniazda");
        close(serverSocket);
        return 1;
    }

    printf("Serwer nasluchuje na %s:%s\n", argv[1], argv[2]);
    logToFile("Serwer uruchomiony");

    while (1) {
        char logMessage[18 + BUFFER_SIZE];
        char fileName[BUFFER_SIZE];
        clientLength = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientLength);
        if (clientSocket == -1) {
            perror("Blad akceptowania polaczenia");
            close(serverSocket);
            return 1;
        }
        
        sprintf(logMessage, "Klient polaczony: %s:%d", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        printf("%s\n", logMessage);
        logToFile(logMessage);

        memset(fileName, 0, sizeof(fileName));
        if (recv(clientSocket, fileName, sizeof(fileName), 0) == -1) {
            perror("Blad odbierania nazwy pliku");
            close(clientSocket);
            close(serverSocket);
            return 1;
        }

        sprintf(logMessage, "Zawnioskowany plik: %s", fileName);
        printf("%s\n", logMessage);
        logToFile(logMessage);

        file = fopen(fileName, "rb");
        if (file == NULL) {
            ssize_t bytesSent = send(clientSocket, &fileSize, sizeof(fileSize), 0);
            fileSize = -1;
            if (bytesSent == -1) {
                perror("Blad wysylania rozmiaru pliku");
            }
        } else {
            ssize_t bytesSent = send(clientSocket, &fileSize, sizeof(fileSize), 0);
            char buffer[BUFFER_SIZE];
            size_t totalBytesSent = 0;
            fseek(file, 0, SEEK_END);
            fileSize = ftell(file);
            fseek(file, 0, SEEK_SET);

            if (bytesSent == -1) {
                perror("Blad wysylania rozmiaru pliku");
                fclose(file);
                close(clientSocket);
                close(serverSocket);
                return 1;
            }
            
            while (totalBytesSent < fileSize) {
                size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, file);
                ssize_t bytesSent = send(clientSocket, buffer, bytesRead, 0);
                if (bytesSent == -1) {
                    perror("Blad wysylania pliku");
                    fclose(file);
                    close(clientSocket);
                    close(serverSocket);
                    return 1;
                }
                totalBytesSent += bytesSent;
            }

            fclose(file);
        }
        close(clientSocket);
    }

    close(serverSocket);

    return 0;
}
