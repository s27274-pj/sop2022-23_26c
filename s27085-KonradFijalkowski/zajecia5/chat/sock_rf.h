#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/un.h>
#include <unistd.h>

#define SV_SOCK_PATH "/tmp/chatFile"
#define BUF_SIZE 256
#define BACKLOG 5

char buffer[BUF_SIZE+1];

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void receiveMessage(int portNo){
    int msgLength;
    printf("--Odbieram--\n");
    fflush(stdout);
    while ((msgLength = read(portNo, buffer, BUF_SIZE)) > 0) {
        printf("odebrano: %d bajt\n", msgLength);
        fflush(stdout);
        /*jeżeli nie odebrano żadnego znaku przełącz na wysyłanie*/
        if(buffer[0] == '\n'){
            return;
        }
        write(STDOUT_FILENO, buffer, msgLength);
    }
    return;
}

void sendMessage(int portNo){
    int msgLength;
    printf("--Wysyłam--\n");
    fflush(stdout);
    while ((msgLength = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0){
        write(portNo, buffer, msgLength);
        /*jeżeli nie wysłano żadnego znaku przełącz na odbieranie*/
        if(buffer[0] == '\n'){
            return;
        }
    }
    return;
}