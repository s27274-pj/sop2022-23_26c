#define _POSIX_C_SOURCE 200112L

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <netdb.h>
#include <stdbool.h>

#define SV_SOCK_PATH "/tmp/chatFile"
#define BUF_SIZE 1023
#define BACKLOG 5

char* buffer;

int sprawdzNumerPortu(int numer){
    if(numer > 65535 || numer < 1){
        printf("Niepoprawny numer portu. Zamykanie programu.\n");
        exit(1);
    }
    return numer;
}

void checkArgumentNumber(int expectedNumber, int providedNumber){
    if(providedNumber != expectedNumber){
        printf("Nieodpowiednia ilość argumentów. Zamykanie.\n");
        exit(1);
    }
}

void assignSocket(int *socketToAssign){
    if((*socketToAssign = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        switch(errno){
            case ENOMEM:
                printf("Brak pamięci systemowej na stworzenie deskryptora socketu. Zamykanie.\n");
                exit(1);
            case ENFILE:
                printf("Osiągnięto limit otwartych plików w sytemie. Zamykanie\n");
                exit(1);
            default:
                printf("Błąd tworzenia socketu. Zamykanie\n");
                exit(1);
        }
    }
}
bool writeToFD(int socket, char* content, size_t contentSize) {
    printf("WRITING Sending size: %ld\n", contentSize);
    fflush(stdout);
    if(write(socket, (void *)&contentSize, sizeof(size_t)) == -1){
        printf("WRITING Couldnt send data size\n");
        return false;
    }
    printf("WRITING Sending data\n");
    fflush(stdout);
    if(write(socket, content, contentSize) == -1){
        printf("WRITING Couldnt send data\n");
        return false;
    }
    printf("WRITING Data sent successfully\n");
    return true;
}
bool readFromFD(int socket){
    size_t size = 0L;
    printf("READING Receiving size:\n");
    fflush(stdout);
    if(read(socket, &size, sizeof(size_t)) == -1){
        printf("READING Couldnt read data size:\n");
        return false;
    }
    printf("READING Received data size:%ld\n", size);
    printf("READING Allocating space for data\n");
    fflush(stdout);
    if((buffer = malloc(size+1)) == NULL){
        printf("READING Couldnt allocate buffer");
        exit(1);
    }
    bzero(buffer, size+1);
    printf("READING Receiving data:\n");
    fflush(stdout);
    if(read(socket, buffer, size) == -1){
        printf("READING Couldnt receive data");
        exit(1);
    }
    printf("READING Data received successfully\n");
    return true;
}
