#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];
    int fileSize;
    FILE *file;

    if (argc != 4) {
        printf("Uzyto: %s <server_ip> <port> <file_name>\n", argv[0]);
        return 1;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Blad tworzenia gniazda");
        return 1;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(atoi(argv[2]));

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Blad polaczenia do serwera");
        close(clientSocket);
        return 1;
    }

    if (send(clientSocket, argv[3], strlen(argv[3]), 0) == -1) {
        perror("Blad wysylania nazwy pliku");
        close(clientSocket);
        return 1;
    }


    if (recv(clientSocket, &fileSize, sizeof(fileSize), 0) == -1) {
        perror("Blad odbierania rozmiaru pliku");
        close(clientSocket);
        return 1;
    }

    if (fileSize == -1) {
        printf("Serwer nie mogl otworzyc pliku. \n");
    } else {
        size_t totalBytesReceived;
        ssize_t bytesRead;
        printf("Rozmiar pliku: %d bytes\n", fileSize);

        file = fopen("received_file", "wb");
        if (file == NULL) {
            perror("Error creating file");
            close(clientSocket);
            return 1;
        }

        memset(buffer, 0, sizeof(buffer));
        totalBytesReceived = 0;
        while (totalBytesReceived < fileSize) {
            bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead == -1) {
                perror("Blad odbierania pliku");
                fclose(file);
                close(clientSocket);
                return 1;
            }

            fwrite(buffer, 1, bytesRead, file);
            totalBytesReceived += bytesRead;
            memset(buffer, 0, sizeof(buffer));
        }

        fclose(file);
        printf("Plik odebrano prawidlowo.\n");
    }

    close(clientSocket);

    return 0;
}
