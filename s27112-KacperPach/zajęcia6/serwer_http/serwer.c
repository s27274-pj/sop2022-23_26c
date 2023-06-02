#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define PORT_NO 55566
#define FILENAME "index.html"

void sendHtmlfile (char *filename, int sockfd);
void formatReply(char ** res, char* htmlContent);

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void shutdownsrv (int signum) {
    printf("\nExiting...\n");
    exit(0);
}

int voidedBlacklist(in_addr_t *blacklist, in_addr_t clientAdr) {
    int i;
    for (i = 0; i < sizeof(&blacklist)/sizeof(in_addr_t); i++)
    {
        if (clientAdr == blacklist[i])
        {
            return 1;
        }
    }
    return 0;
}

void logsrv(struct sockaddr_in cli_addr) {
    FILE * fp;
    char adr[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(cli_addr.sin_addr),adr,INET_ADDRSTRLEN);

    fp = fopen("server.log", "a");
    fprintf(fp,"Connect from... IP:%s, Port:%d\n",adr,cli_addr.sin_port);
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    int sockfd, newsockfd;
    unsigned int clilen;
    struct sockaddr_in serv_addr, cli_addr;
    
    in_addr_t blacklist[10] = {0};
    blacklist[0] = inet_addr("127.0.0.2");

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
    signal(SIGCHLD, SIG_IGN);  /*tworzy się dziecko dla kazdego połaczenia,
    chce uniknąc duzej ilosci zombie dzieci*/
    clilen = sizeof(cli_addr);

    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        
        if (fork() == 0) {
            if (voidedBlacklist(blacklist,cli_addr.sin_addr.s_addr)!= 0)
            {
                close(newsockfd);
                continue;
            }
            logsrv(cli_addr);
            sendHtmlfile(FILENAME, newsockfd);
            break;
        }
        close(newsockfd);
    }
}

void sendHtmlfile (char *filename, int sockfd) {
        FILE *fp;
        int n;
        long f_size;
        char * file_content, *reply;
        fp = fopen(filename,"r");
        if (fp == NULL) {
            n = write(sockfd, "-1", 255); 
            if (n < 0) 
                error("ERROR writing to socket");
            return;
        }
        fseek(fp, 0, SEEK_END); 
        f_size = ftell(fp); 
        fseek(fp, 0, SEEK_SET); 
        
        file_content = malloc(f_size + 1);
        fread(file_content, f_size, 1, fp);
        fclose(fp);

        formatReply(&reply,file_content);
        n = write(sockfd, reply, strlen(reply) );
        if (n < 0) 
            error("ERROR writing to socket");

        free(file_content);
        free(reply);
        close(sockfd);
}

void formatReply(char ** res, char* htmlContent) {
    *res = malloc(101*sizeof(char)+ sizeof(htmlContent));
    bzero(*res,sizeof(res));
    sprintf(*res,
        "HTTP/1.1 200 OK\n"
        "Connection: Close\n"
        "Server: KacperTest\n"
        "Content-Type: text/html\n"
        "Content-Length: %lu\n"
        "\n"
        "%s",
        strlen(htmlContent), htmlContent);
}
