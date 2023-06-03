/*defining global consts*/
#define READ_BUFFER_SIZE 256
#define WRITE_BUFFER_SIZE 256
#define EMPTY_RESPONSE_BUFFER_SIZE 128
#define MAX_LOG_SIZE 256
#define LOG_PATH "server.log"
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <arpa/inet.h>

int serverSocket = 0; /*this is global so we can close the socket when handling SIGINT*/
const char* forbiddenFiles[] = {"forbidden1.txt", "forbidden2.txt", "forbidden3.txt"}; /*list of files forbidden for access*/

void error(char* message) {
    perror(message);
    if (serverSocket != 0) {
        close(serverSocket);
    }
    exit(1);
}

void printLog(char* message, ...) {
    int logLength;
    time_t rawtime;
    struct tm * timeinfo;
    va_list args;
    FILE* filePtr;
    char* timeString;
    char* formattedMessage = calloc(MAX_LOG_SIZE, sizeof(char));
    char* formattedLog = calloc(MAX_LOG_SIZE+128, sizeof(char));

    if (formattedMessage == NULL || formattedLog == NULL) {
        error("Error, failed to allocate memory");
    }
    time ( &rawtime );
    timeinfo = localtime ( &rawtime ); /*gets local time info*/

    va_start(args, message);
    vsprintf(formattedMessage, message, args); /*prints formatted string, this is used so we 
                                                can do stuff like printLog("Number: %d", number)*/
    va_end(args);

    timeString = asctime(timeinfo);
    timeString[strlen(timeString) - 1] = 0;

    logLength = sprintf(formattedLog, "[%s]: %s\n", timeString, formattedMessage); /*saves log in [time]: message format to buffer*/
    filePtr = fopen(LOG_PATH, "a+");
    if (filePtr == NULL) {
        error("Error, failed to open file");
    }
    fwrite(formattedLog, logLength, sizeof(char), filePtr); /*writes log to file, closes file, and prints log to console*/
    fclose(filePtr);
    printf("%s", formattedLog);
}

void handleSignal(int sigId) {
    close(serverSocket);
    printLog("Closed server socket");
    exit(0);
}

void setUpServer(int * serverSocket, int portNumber) {
    struct sockaddr_in serverAddress;
    printLog("Starting server on port %d", portNumber);
    *serverSocket = socket(AF_INET, SOCK_STREAM, 0); /*AF_INET - communication over the internet,
                                                SOCK_STREAM - TCP will be used (the other option is UDP)*/
    if (*serverSocket < 0) {
        error("Error, failed to open socket");
    }
    printLog("Opened socket");
    memset(&serverAddress, 0, sizeof(serverAddress)); /*allocating memory for server address - fills the buffer 
                                                      with zeroes*/
    /*setting up server parameters*/
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber); /*converts number to network byte order (big-endian, 
                                                most significant byte at smallest address)*/
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    if(bind(*serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        error("Error, failed to bind socket");
    }
    printLog("Bound to socket");
}

int listenForClients(int serverSocket) {
    int clientSocket;
    struct sockaddr_in clientAddress;
    unsigned int clientSize;

    listen(serverSocket, 5);
    printLog("Waiting for connection...");
    clientSize = sizeof(clientAddress);
    while(1){
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientSize); /*waits till any client connects*/
        if (clientSocket < 0) {
            error("Error, failed on accept");
        }
        if(fork() == 0) { /*if client connects, the process is forked and the child process prints information about connection
                          and then moves on to sending response (see main function)*/
            char ipAddress[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddress.sin_addr, ipAddress, INET_ADDRSTRLEN); /*converts ip address to string*/
            printLog("Client %d connected from ip address: %s", clientSocket, ipAddress);
            return clientSocket;
        }
    }
}

/*reads raw data from the socket*/
char* readRequest(int clientSocket){
    char* buffer;
    char* output;
    int readBytes;

    buffer = calloc(READ_BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        error("Error, failed to allocate memory");
    }
    readBytes = read(clientSocket, buffer, READ_BUFFER_SIZE);
    output = calloc(readBytes, sizeof(char));
    if (output == NULL) {
        error("Error, failed to allocate memory");
    }
    memcpy(output, buffer, readBytes); /*copies only actually read bytes to bufffer - this way we won't pass the entire buffer but only
                                        necessary information*/
    free(buffer);
    return output;
}

void sendEmptyResponse(int clientSocket, int statusCode){
    char* responseBuffer;
    int responseSize;
    responseBuffer = calloc(EMPTY_RESPONSE_BUFFER_SIZE, sizeof(char));
    if (responseBuffer == NULL) {
        error("Error, failed to allocate memory");
    }
    responseSize = sprintf(responseBuffer, "HTTP/1.1 %d\r\nContent-Length: 0\r\n\r\n", statusCode);
    if(write(clientSocket, responseBuffer, responseSize) < 0) {
        error("Error, failed to write to socket");
    }
}

void sendFileResponse(int clientSocket, char* filePath){
    char* responseBuffer;
    int headerSize, fileSize, bytesToWrite, bytesToRead;
    FILE* filePtr = fopen(filePath, "rb");

    if (filePtr == NULL) {
        error("Error, failed to open file");
    }
    fseek(filePtr, 0, SEEK_END); /*moving pointer to end of file*/
    fileSize = ftell(filePtr); /*ftell returns the position of the file pointer (if it's the end of file position = size)*/
    rewind(filePtr);

    responseBuffer = calloc(WRITE_BUFFER_SIZE, sizeof(char));
    if (responseBuffer == NULL) {
        error("Error, failed to allocate memory");
    }
    headerSize = sprintf(responseBuffer, "HTTP/1.1 200\r\nContent-Length: %d\r\nContent-Type: text/plain; charset=utf-8\r\n\r\n", fileSize);
    bytesToWrite = headerSize;
    while(ftell(filePtr) < fileSize) { /*iterating over file until pointer position reaches end of file*/
        /*we read the data in parts until the leftover data is smaller than buffer size 
        (which means we've reached the end of file). Each part is sent to client separately*/
        int n;
        if(fileSize - ftell(filePtr) > WRITE_BUFFER_SIZE - bytesToWrite) {
            bytesToRead = WRITE_BUFFER_SIZE - bytesToWrite;
        }else {
            bytesToRead = fileSize - ftell(filePtr);
        }
        n = fread(responseBuffer + bytesToWrite, bytesToRead, sizeof(char), filePtr);
        if (n < 0) {
            error("Error, failed to read from file");
        }
        bytesToWrite += bytesToRead;
        if (write(clientSocket, responseBuffer, bytesToWrite) < 0) {
            error("Error, failed to write to socket");
        }
        bytesToWrite = 0;
    }
    fclose(filePtr);
}

/*processes raw data and sends back response accordingly*/
void processRequest(int clientSocket, char* requestData){
    int i;
    char* pathStart = strchr(requestData, ' ') + 1; /*strchr searches for first occurence of given character in string*/
    char* pathEnd = strchr(pathStart, ' ');
    *pathEnd = '\0'; /*replace space at the end of path with null character, that way it can be used as a string later*/
    if(*pathStart == '/'){ /*remove leading "/" from path*/
        pathStart++;
    }

    if(pathStart == NULL || pathEnd == NULL) {
        printLog("Received invalid request from client %d", clientSocket);
        sendEmptyResponse(clientSocket, 400);
        return;
    }
    if(strncmp(requestData, "GET ", 4) != 0) { /*checks if http request is GET*/
        printLog("Received request with unhandled method from client %d", clientSocket);
        sendEmptyResponse(clientSocket, 405);
        return;
    }
    for(i = 0; i < sizeof(forbiddenFiles)/sizeof(forbiddenFiles[0]); i++) { /*checks if client is asking for forbidden files*/
        if(strcmp(pathStart, forbiddenFiles[i]) == 0){
            printLog("Received request for forbidden file %s from client %d", pathStart, clientSocket);
            sendEmptyResponse(clientSocket, 401);
            return;
        }
    }
    if (access(pathStart, F_OK) != 0) { /*checks if file exists*/
        printLog("Received request for missing file %s from client %d", pathStart, clientSocket);
        sendEmptyResponse(clientSocket, 404);
        return;
    }
    printLog("Sending file %s to client %d", pathStart, clientSocket);
    sendFileResponse(clientSocket, pathStart);
}

int main(int argc, char *argv[]) {
    int clientSocket, portNumber;
    char* requestData;
    signal(SIGINT, handleSignal);
    if (argc < 2) {
        fprintf(stderr, "Error, no port has been provided");
        return 1;
    }
    portNumber = atoi(argv[1]);
    setUpServer(&serverSocket, portNumber);
    clientSocket = listenForClients(serverSocket);
    requestData = readRequest(clientSocket);
    processRequest(clientSocket, requestData);
    return 0;
}
