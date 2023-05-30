#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define SIZE 1024

void handle_ctrlc(int signal){
	printf("Przerwano prace serwera przez uzycie CTRL+C.\n"); 
	exit(0);
}

int main(){

  char *ip="127.0.0.1";
  int port=8080;
  int n;
  int socket_serv;
  int socket_client;
  
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
  
  signal (SIGINT, handle_ctrlc);
  
  socket_serv = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_serv<0){
    printf("BLAD SOCKETU SERWERA");
    exit(1);
  }
  
  printf("Socket serwera utworzony.\n");
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
  
  n = bind(socket_serv, (struct struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n<0){
    printf("BLAD BIND SERWERA");
    exit(1);
  }
  
  printf("Bind przeprowadzony pomyslnie.\n");
  
  n = listen(socket_serv, 10);
  if (n==0){
    printf("Gniazdo serwera nasluchuje...\n");
  }else{
    printf("BLAD NASLUCHIWANIA");
    exit(1);
  }
  
  
  
  return 0;
}
