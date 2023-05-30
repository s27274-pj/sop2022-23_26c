#include "sock_rf.h"

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char** argv){
    int socketd, occupiedSocketd, portNumber, msgLength;
    char *buffer = malloc(BUF_SIZE);
    struct sockaddr_un addr;

    if(buffer == NULL){
        error("malloc failure");
    }

    socketd = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("Server socket = %d\n", socketd);
    if(socketd == -1){
        error("wrong socket");
    }
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
        error("clear path");
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
    if(bind(socketd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1){
        error("bind");
    }
    printf("Socket z sukcesem otrzymał nazwę\n");
    if (listen(socketd, BACKLOG) == -1)
        error("listen");
    printf("Socket rozpoczął nasłuchiwanie\n");
    return 0;
}