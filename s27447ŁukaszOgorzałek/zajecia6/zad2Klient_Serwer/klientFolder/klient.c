#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int clientSocket, filenameLength, fileSize, remaining_bytes;
    struct sockaddr_in server_address;
	
	size_t bytes_received;
	
    char fileName[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	
	FILE* file;
	
    /* Create client socket */
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    /* Initialize server address */
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345); /* same port number as the server */
    if (inet_pton(AF_INET, "127.0.0.1", &(server_address.sin_addr)) <= 0) {
        perror("Error converting address");
        exit(EXIT_FAILURE);
    }

    /* Connect to the server */
    if (connect(clientSocket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Enter the filename to download: ");
    fgets(fileName, BUFFER_SIZE, stdin);
    fileName[strcspn(fileName, "\n")] = 0; /* Remove newline character */

    /* Send filename length */
    filenameLength = strlen(fileName);
    if (send(clientSocket, &filenameLength, sizeof(filenameLength), 0) == -1) {
        perror("Error sending filename length");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    /* Send filename */
    if (send(clientSocket, fileName, filenameLength, 0) == -1) {
        perror("Error sending filename");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    /* Receive file size */
    if (recv(clientSocket, &fileSize, sizeof(fileSize), 0) == -1) {
        perror("Error receiving file size");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    if (fileSize == -1) {
        printf("File \"%s\" does not exist on the server.\n", fileName);
    } else {
        printf("Downloading file \"%s\" of size %d bytes...\n", fileName, fileSize);

        /* Open file for writing */
        file = fopen(fileName, "wb");
        if (file == NULL) {
            perror("Error opening file for writing");
            close(clientSocket);
            exit(EXIT_FAILURE);
        }

        /* Receive file in chunks */
		remaining_bytes = fileSize;
        while (remaining_bytes > 0) {
            int bytes_to_receive = (remaining_bytes < BUFFER_SIZE) ? remaining_bytes : BUFFER_SIZE;
            bytes_received = recv(clientSocket, buffer, bytes_to_receive, 0);
            if (bytes_received == -1) {
                perror("Error receiving file");
                break;
            }

            fwrite(buffer, 1, bytes_received, file);
            remaining_bytes -= bytes_received;
        }

        fclose(file);
        printf("File \"%s\" has been downloaded.\n", fileName);
    }

    /* Close connection with the server */
    close(clientSocket);

    return 0;
}
