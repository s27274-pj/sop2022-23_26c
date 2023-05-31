#include "sock_rf.h"



int main(int argc, char** argv){
    int listenSocket, newSock;
    struct sockaddr_un addr;
    listenSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if(listenSocket == -1){
        error("wrong socket");
    }
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
        error("clear path");
    }
    /*zerujemy strukture adresu i dajemy jej rodzaj domeny i adres dla pliku socketu */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
    /*adres jest gotowy, czas na przypisanie go do socketu*/
    if(bind(listenSocket, (const struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1){
        error("bind");
    }
    printf("SERVER Socket z sukcesem otrzymał nazwę\n");
    if (listen(listenSocket, BACKLOG) == -1)
        error("listen");
    printf("SERVER Socket rozpoczął nasłuchiwanie\n");
    while(1) {
        newSock = accept(listenSocket, NULL, NULL);
        printf("SERVER Połączenie otwarte z %d\n", newSock);
        for (;;) {
            receiveMessage(newSock);
            sendMessage(newSock);
        }
    }
}
