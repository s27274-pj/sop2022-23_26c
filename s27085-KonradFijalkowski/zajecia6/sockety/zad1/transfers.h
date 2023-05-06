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
#include <arpa/inet.h>

#define SV_SOCK_PATH "/tmp/chatFile"
#define BUF_SIZE 1023
#define BACKLOG 5

char* buffer;

int sprawdzNumerPortu(int numer){
    if(numer > 65535 || numer < 1){
        printf("Port number out of boundaries - aborting\n");
        exit(1);
    }
    return numer;
}

void checkArgumentNumber(int expectedNumber, int providedNumber){
    if(providedNumber != expectedNumber){
        printf("Insufficient number of parameters given - aborting\n");
        exit(1);
    }
}

void assignSocket(int *socketToAssign){
    if((*socketToAssign = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        close(*socketToAssign);
        switch(errno){
            case ENOMEM:
                printf("Insufficient memory space to create socket - aborting\n");
                exit(1);
            case ENFILE:
                printf("Limit of open files in system reached - aborting\n");
                exit(1);
            default:
                printf("Socket creation error errno: %d\n", errno);
                exit(1);
        }
    }
}
bool writeToFD(int socket, char* content, int contentSize) {
    printf("WRITING Sending size: %d\n", contentSize);
    fflush(stdout);
    if(write(socket, (void *)&contentSize, sizeof(int)) == -1){
        printf("WRITING Couldn't send data size\n");
        return false;
    }
    if(contentSize == -1 || contentSize == -2){
        return false;
    }
    printf("WRITING Sending data\n");
    fflush(stdout);
    if(write(socket, content, contentSize) == -1){
        printf("WRITING Couldn't send data\n");
        return false;
    }
    printf("WRITING Data sent successfully\n");
    return true;
}
int readFromFD(int socket){
    int size = 0;
    if(read(socket, &size, sizeof(int)) == -1){
        printf("READING Couldn't read data size\n");
        return -2;
    }
    printf("READING Received data size: %d\n", size);
    if(size == -1){
        return -1;
    }
    printf("READING Allocating space for data\n");
    fflush(stdout);
    if((buffer = malloc(size+1)) == NULL){
        printf("READING Couldn't allocate buffer");
        return -2;
    }
    bzero(buffer, size+1);
    printf("READING Receiving data\n");
    fflush(stdout);
    if(read(socket, buffer, size) == -1){
        printf("READING Couldn't receive data");
        return -2;
    }
    printf("READING Data received successfully\n");
    return size;
}
