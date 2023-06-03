#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 100
#define FORBIDDEN_LIST_SIZE 3

char* forbidden_addresses[] = {
    "192.168.0.1",
    "10.0.0.2",
    "172.16.0.3"
};

void handle_client(int client_socket, struct sockaddr_in client_address) {
    char buffer[BUFFER_SIZE];
    char client_ip[INET_ADDRSTRLEN];
    ssize_t bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0);
    FILE* log_file = fopen("server.log", "a");
    int i;
    inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);

    printf("Klient polaczony: %s\n", client_ip);
    
    if (bytes_read <= 0) {
        perror("Blad odbierania danych od klienta");
        return;
    }

    for (i = 0; i < FORBIDDEN_LIST_SIZE; i++) {
        if (strcmp(client_ip, forbidden_addresses[i]) == 0) {
            printf("Dostep zabroniony: %s\n", client_ip);
            close(client_socket);
            return;
        }
    }
    
    if (log_file == NULL) {
        perror("Blad otwierania pliku .log");
        return;
    }

    fprintf(log_file, "Klient polaczony: %s\n", client_ip);
    fclose(log_file);

    send(client_socket, "Hello, world!", 13, 0);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Blad tworzenia gniazda");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Blad laczenia gniazda");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Blad nasluchiwania gniazda");
        exit(EXIT_FAILURE);
    }

    printf("Serwer nasluchuje na porcie 8080...\n");

    while (1) {
        pid_t child_pid = fork();
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket < 0) {
            perror("Blad akceptowania polaczenia");
            exit(EXIT_FAILURE);
        }
        
        if (child_pid < 0) {
            perror("Blad tworzenia procesu potomnego");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            close(server_socket);
            handle_client(client_socket, client_address);
            exit(EXIT_SUCCESS);
        } else {
            close(client_socket);
        }
    }

    close(server_socket);

    return 0;
}
