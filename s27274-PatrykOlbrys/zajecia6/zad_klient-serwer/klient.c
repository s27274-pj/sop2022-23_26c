#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT_NO 32265

void error(char *message)
{
    perror(message);
    exit(1);
}

void cwrite(int sockfd, char *buffer)
{
    if (write(sockfd, buffer, strlen(buffer)) < 0)
        error("ERROR writing to socket");
}

int main(int argc, char *argv[])
{
    int sockfd, n, filesize;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256], filename[256], *file_content;
    FILE *fp;

    if (argc < 2)
    {
        printf("ERROR: Pass the hostname!\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR: No such host\n");
        exit(1);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(PORT_NO);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    printf("Enter the length of the filename: ");
    fgets(buffer, 256, stdin);
    cwrite(sockfd, buffer);

    printf("Enter the filename: ");
    fgets(buffer, 256, stdin);
    cwrite(sockfd, buffer);
    strncpy(filename, buffer, sizeof(filename));

    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");
    filesize = atoi(buffer);
    if (filesize < 0)
        error("ERROR: File doesn't exist");
    file_content = malloc(filesize + 1);

    n = read(sockfd, file_content, filesize);
    if (n < 0)
        error("ERROR reading from socket");

    fp = fopen(filename, "a");
    fwrite(file_content, strlen(file_content), 1, fp);
    fclose(fp);

    free(file_content);
    return 0;
}
