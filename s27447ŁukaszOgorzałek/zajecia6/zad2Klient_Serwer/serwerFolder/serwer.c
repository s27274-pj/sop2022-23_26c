#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void handle_client(int clientSocket, struct sockaddr_in client_address, char* fileName);
void cleanup(int signum);

int serverSocket; 

int main() {
    int clientSocket, filenameLength;
    struct sockaddr_in server_address, client_address;
	
    socklen_t client_address_size;
	
    char fileName[BUFFER_SIZE];
    char logFileName[] = "connectionLogs.log";
	char client_ip[INET_ADDRSTRLEN];
	
    FILE* logFile;

    /* Set up Ctrl+C signal handling */
    signal(SIGINT, cleanup);

    /* Create server socket */
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    /* Initialize server address */
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345); /* any available port */
    server_address.sin_addr.s_addr = INADDR_ANY;

    /* Bind server address to socket */
    if (bind(serverSocket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding address");
        exit(EXIT_FAILURE);
    }

    /* Start listening on the port */
    if (listen(serverSocket, 1) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    printf("Server is ready to accept clients.\n");

    /* Open log file */
    logFile = fopen(logFileName, "a");
    if (logFile == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    while (1) {
        /* Accept client connection */
        client_address_size = sizeof(client_address);
        clientSocket = accept(serverSocket, (struct sockaddr *)&client_address, &client_address_size);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;
        }

        /* Log client connection */
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
        fprintf(logFile, "Client %s:%d connected\n", client_ip, ntohs(client_address.sin_port));
        fflush(logFile);

        /* Handle client in a separate process */
        if (fork() == 0) {
            /* Read fileName length */
            if (recv(clientSocket, &filenameLength, sizeof(filenameLength), 0) == -1) {
                perror("Error reading fileName length");
                close(clientSocket);
                fclose(logFile);
                exit(EXIT_FAILURE);
            }

            /* Read fileName */
            if (recv(clientSocket, fileName, filenameLength, 0) == -1) {
                perror("Error reading fileName");
                close(clientSocket);
                fclose(logFile);
                exit(EXIT_FAILURE);
            }

            printf("Client %s:%d requests file: %s\n", client_ip, ntohs(client_address.sin_port), fileName);

            /* Log requested file */
            fprintf(logFile, "Client %s:%d requested file: %s\n", client_ip, ntohs(client_address.sin_port), fileName);
            fflush(logFile);

            handle_client(clientSocket, client_address, fileName);

            /* Close connection with the client */
            close(clientSocket);
            exit(EXIT_SUCCESS);
        }

        close(clientSocket);
    }

    fclose(logFile);
    return 0;
}

void handle_client(int clientSocket, struct sockaddr_in client_address, char* fileName) {
    FILE* file;
    int fileSize;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    /* Open the file */
    file = fopen(fileName, "rb");
    if (file == NULL) {
        /* Send file size -1 in case of error */
        fileSize = -1;
        if (send(clientSocket, &fileSize, sizeof(fileSize), 0) == -1) {
            perror("Error sending file size");
            return;
        }
    } else {
        /* Get file size */
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        /* Send file size */
        if (send(clientSocket, &fileSize, sizeof(fileSize), 0) == -1) {
            perror("Error sending file size");
            fclose(file);
            return;
        }

        /* Send file in chunks */
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            if (send(clientSocket, buffer, bytes_read, 0) == -1) {
                perror("Error sending file");
                break;
            }
        }

        fclose(file);
    }
}

void cleanup(int signum) {
    printf("\nClosing the server...\n");
    close(serverSocket); /* Closing the sockeet */
    exit(EXIT_SUCCESS);
}
