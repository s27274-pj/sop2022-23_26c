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

#define SIZE 1024

void write_file(int socket_serv){
  int m;
  FILE *plik;
  char *nazwa_pliku = "write.txt";
  char buffer[SIZE];
  plik = fopen(nazwa_pliku, "wb");
  
  if(plik==NULL){
    int file_size = -1;
    send(socket_serv, &file_size, sizeof(file_size), 0);
    printf("BLAD otwierania pliku.\n");
    exit(1);
  }
	
  while (1) {
    m = recv(socket_serv, buffer, SIZE, 0);
    if (m <= 0){
      break;
    }
    fwrite(buffer, 1, m, plik);
    bzero(buffer, SIZE);
  }
  fclose(plik);
  return;
}

void handle_ctrlc(int signal){
	printf("Przerwano prace serwera przez uzycie CTRL+C.\n"); 
	exit(0);
}

int main(){

  char *ip="127.0.0.1";
  int port=8080;
  pid_t pid;
  int n;
  int socket_serv;
  int socket_client;
  FILE *plik_log;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  plik_log = fopen("plik_log.txt", "a");
  
  signal (SIGINT, handle_ctrlc);
  
  if (plik_log == NULL){
    printf("BLAD otwierania pliku z logami.\n");
    exit(1);
  }
  
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
    socket_client = accept(socket_serv, (struct sockaddr*)&new_addr, &addr_size);
    addr_size = sizeof(new_addr);
		
    if (socket_client<0){
    printf("BLAD SOCKETU SERWERA.");
    exit(1);
    }
	  
    pid = fork();

    if(pid == 0){
        printf("Nawiazano polaczenie z klientem.\n");
        
        fprintf(plik_log, "Polaczony klient: IP=%s, Port=%d, Plik:%s\n", ip, port, "write.txt");
        
  	write_file(socket_client);
  	printf("Pomyslnie zapisano plik.\n");
	
        if(close(socket_client) == 0){
            printf("Polaczenie z klientem zakonczono.\n");
        }else{
            printf("BLAD - nie zakonczono polaczenia\n");
        }
        break;
    }
  }
  fclose(plik_log);
  return 0;
}
