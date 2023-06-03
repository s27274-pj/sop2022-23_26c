CFLAGS=--ansi -Wall --pedantic
CC=gcc
all: client server

client: client.c sock_rf.h
	$(CC) $(CFLAGS) -o client client.c

server: server.c sock_rf.h
	$(CC) $(CFLAGS) -o server server.c
