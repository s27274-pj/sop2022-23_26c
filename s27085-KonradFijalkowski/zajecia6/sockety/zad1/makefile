CFLAGS=--ansi -Wall --pedantic
CC=gcc
all: client server

client: fileClient.c transfers.h
	$(CC) $(CFLAGS) -o fileClient.exe fileClient.c

server: fileServer.c transfers.h
	$(CC) $(CFLAGS) -o fileServer.exe fileServer.c
