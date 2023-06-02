#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define PORT_NO 55565

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void shutdownsrv (int signum) {
    printf("\nExiting...\n");
    exit(0);
}

void logsrv(char * filename, struct sockaddr_in cli_addr) {
    FILE * fp;
    char adr[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(cli_addr.sin_addr),adr,INET_ADDRSTRLEN);

    fp = fopen("server.log", "a");
    fprintf(fp,"Connect from... IP:%s, Port:%d, File:%s\n",adr,cli_addr.sin_port,filename);
    fclose(fp);
}


int main(int argc, char const *argv[])
{
    int sockfd, newsockfd, clilen, n, filename_len,f_size;
    char buffer[256];
    char *filename = NULL;
    char *file_content = NULL;
    struct sockaddr_in serv_addr, cli_addr;
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd < 0) 
         error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_NO);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd,5);
    signal(SIGINT, &shutdownsrv);

    while (1)
    {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        
        if (newsockfd < 0) 
            error("ERROR on accept");
        
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        filename_len = atoi(buffer);

        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        filename = malloc(filename_len*sizeof(char));
        bcopy(buffer,filename,filename_len*sizeof(char));

        logsrv(filename,cli_addr);
        
        printf("reading from: %s(file length):%d\n",filename,filename_len);

        fp = fopen(filename,"r");
        if (fp == NULL) {
            n = write(newsockfd, "-1", 255);
            if (n < 0) 
                error("ERROR writing to socket");
            continue;
        }
        fseek(fp, 0, SEEK_END); 
        f_size = ftell(fp); 
        fseek(fp, 0, SEEK_SET); 
        
        bzero(buffer, 256);
        sprintf(buffer, "%d", f_size);

        n = write(newsockfd, buffer, 255);
        if (n < 0) 
            error("ERROR writing to socket");

        file_content = malloc(f_size + 1);
        fread(file_content, f_size, 1, fp);
        fclose(fp);

        n = write(newsockfd, file_content, f_size);
        if (n < 0) 
            error("ERROR writing to socket");

        free(filename);
        free(file_content);
        close(newsockfd);
    }
}
