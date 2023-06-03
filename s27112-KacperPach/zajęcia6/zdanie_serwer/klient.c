#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>


#define PORT_NO 55565

void error(char *msg)
{
    perror(msg);
    exit(0);
}

void cwrite(int sockfd, char *buffer) {
    int n;
    n = write(sockfd,buffer,strlen(buffer)); 
    if (n < 0) 
         error("ERROR writing to socket");
}

int main(int argc, char *argv[])
{
    int sockfd, n, filesize;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256], filename[256], *file_content;
    FILE *fp;

    if (argc < 1) {
        printf("ERROR pass hostname!");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(PORT_NO);

    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    printf("Podaj długosc nazwy pliku: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    cwrite(sockfd, buffer);

    printf("Podaj nazwe pliku: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    cwrite(sockfd, buffer);
    bcopy(buffer,filename,256);

    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
        error("ERROR reading from socket");
    filesize = atoi(buffer);
    if (filesize < 0) 
        error("ERROR file does't exist");
    file_content = malloc(filesize+1);

    n = read(sockfd,file_content,filesize);
    if (n < 0) 
         error("ERROR reading from socket");    

    fp = fopen(filename,"a");
    fwrite(file_content,strlen(file_content),1,fp);

    free(file_content);
    return 0;
}
