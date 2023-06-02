CFLAGS=--ansi -Wall --pedantic
CC=gcc
all: client server

client: httpClient.c transfers.h
	$(CC) $(CFLAGS) -o httpClient.exe httpClient.c

server: httpServer.c transfers.h
	$(CC) $(CFLAGS) -o httpServer.exe httpServer.c
