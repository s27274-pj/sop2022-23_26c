#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <strings.h>
#include <sys/socket.h>
#include <wait.h>

#define MESS 256

void handle_ctrlc(int signal){
	printf("Przerwano prace serwera przez uzycie CTRL+C.\n"); 
	exit(0);
}

int main(){

  char *ip="127.0.0.1";
  int port=8080;
  pid_t pid;
  int n;
  char wiadomosc[MESS];
  int socket_serv;
  int socket_client;
  
  struct sockaddr_in server_addr;

  
  signal (SIGINT, handle_ctrlc);
  
  socket_serv = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_serv<0){
    printf("BLAD SOCKETU SERWERA.");
    exit(1);
  }
  
  printf("Socket serwera utworzony.\n");
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
  
  n = bind(socket_serv, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n<0){
    printf("BLAD BIND SERWERA.");
    exit(1);
  }
  
  printf("Bind przeprowadzony pomyslnie.\n");
  
  n = listen(socket_serv, 10);
  if (n==0){
    printf("Gniazdo serwera nasluchuje...\n");
  }else{
    printf("BLAD NASLUCHIWANIA.");
    exit(1);
  }
  
  while(1){
    printf("Server oczekuje...\n");
    socket_client = accept(socket_serv, (struct sockaddr*) NULL, NULL);
		
    if (socket_client<0){
    printf("BLAD SOCKETU SERWERA.");
    exit(1);
    }
	  
    pid = fork();
    if(pid == 0){
        printf("Nawiazano polaczenie z klientem.\n");
        printf("Odbieranie wiadomosci...\n");
        bzero(wiadomosc, MESS);
        n = read(socket_client, wiadomosc, MESS - 1);
	
        if(n > 0){
            printf("Odebrano wiadomosc o dlugosci %d znakow.\n", n);
        }else{
	    printf("BLAD - nie odebrano wiadomosci.\n");
        }
			
        printf("Wiadomosc: %s\n", wiadomosc);
	
        if(close(socket_client) == 0){
            printf("Polaczenie z klientem zakonczono.\n");
        }else{
            printf("BLAD - nie zakonczono polaczenia\n");
        }
        break;
    }
  }
  return 0;
}
