#include "sock_rf.h"

int main() {
    struct sockaddr_un addr;
    int connectionSocket;
    if ((connectionSocket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        error("socket creation failure");
    }
    printf("CLIENT Utworzono socket nr: %d\n", connectionSocket);
    /*zerujemy strukture adresu i dajemy jej rodzaj domeny i adres dla pliku socketu */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path));
    /*adres jest gotowy, czas na przypisanie go do socketu*/
    if (connect(connectionSocket, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1){
        error("connection to server failed");
    }
    printf("CLIENT Połączenie nawiązane\n");
    for(;;){
        sendMessage(connectionSocket);
        receiveMessage(connectionSocket);
    }
}
