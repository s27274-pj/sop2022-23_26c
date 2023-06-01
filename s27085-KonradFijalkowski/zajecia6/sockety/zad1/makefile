CFLAGS=--ansi -Wall --pedantic
CC=gcc
all: client server

client: fileClient.c transfers.h
	$(CC) $(CFLAGS) -o fileClient fileClient.c

server: fileServer.c transfers.h
	$(CC) $(CFLAGS) -o fileServer fileServer.c
