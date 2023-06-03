#define BUFFER_SIZE 256
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void error(char* message) {
    perror(message);
    exit(1);
}

void setUpClient(int* clientSocket, struct sockaddr_in* serverAddress, char* address, int portNumber) {
    printf("Starting client\n");
    *clientSocket = socket(AF_INET, SOCK_STREAM, 0); /*AF_INET - communication over the internet,
                                                SOCK_STREAM - TCP will be used (the other option is UDP)*/
    if (*clientSocket < 0) {
        error("Error, failed to open socket");
    }
    printf("Opened socket\n");
    memset(serverAddress, 0, sizeof(*serverAddress)); /*allocating memory for server address - fills the buffer 
                                                      with zeroes*/
    /*setting up server parameters*/
    serverAddress->sin_family = AF_INET;
    serverAddress->sin_port = htons(portNumber); /*converts number to network byte order (big-endian, 
                                                most significant byte at smallest address)*/
    inet_pton(AF_INET, address, &serverAddress->sin_addr); /*converts ip address to needed format and saves the converted value to s_addr*/
}

void connectToServer(int clientSocket, struct sockaddr_in serverAddress) {
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        error("Error, failed to connect to server");
    }
    printf("Connected to server\n");
}

char* formRequest(char* data) {
    char* request;
    int requestLength;
    requestLength = 13*sizeof(char) + strlen(data);
    request = (char*)calloc(requestLength, sizeof(char));
    if (request == NULL) {
        error("Error, failed to allocate memory");
    }
    sprintf(request, "GET %s HTTP/1.1", data); /*forms http request*/
    return request;
}

void sendRequest(int clientSocket) {
    char buffer[BUFFER_SIZE]; /*buffer will be used to read and write data to socket*/
    char* filename;
    char* request;
    int n;
    memset(buffer, 0, sizeof(buffer)); /*allocating memory for buffer*/
    if (buffer == NULL) {
        error("Error, failed to allocate memory");
    }
    printf("Enter filename: ");
    fgets(buffer, 255, stdin);
    filename = (char*)calloc(((int)strlen(buffer)-1), sizeof(char));
    if (filename == NULL) {
        error("Error, failed to allocate memory");
    }
    memcpy(filename, buffer, (int)strlen(buffer)-1);
    request = formRequest(filename);
    printf("Sending request: %s\n", request);
    n = write(clientSocket, request, strlen(request)); 
    printf("%d\n", n);
    if (n < 0) {
        error("Error, failed to write to socket");
    }
    printf("Request sent to server\n");
}

int main(int argc, char *argv[]) {
    int clientSocket, portNumber;
    char* address;
    struct sockaddr_in serverAddress;
    if (argc < 3) {
        fprintf(stderr, "Error, arguments should be [ip address] [port number]\n");
        return 1;
    }
    address = argv[1];
    portNumber = atoi(argv[2]);
    setUpClient(&clientSocket, &serverAddress, address, portNumber);
    connectToServer(clientSocket, serverAddress);
    sendRequest(clientSocket);
    return 0;
}
