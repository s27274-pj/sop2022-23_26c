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

void send_file(FILE *plik, int socket_serv){
  char data[SIZE] = {0};
  size_t bytesRead;

  while((bytesRead = fread(data, 1, sizeof(data), plik)) > 0) {
    if (send(socket_serv, data, bytesRead, 0) == -1) {
      printf("BLAD wysylania pliku.\n");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

int main(){
  
  char *ip="127.0.0.1";
  int port=8080;
  int e;
  int socket_serv;
  
  struct sockaddr_in server_addr;
  FILE *plik;
  char *nazwa_pliku = "send.txt";

  socket_serv = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_serv<0){
    printf("BLAD SOCKETU SERWERA.");
    exit(1);
  }
  
  printf("Socket serwera utworzony.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(socket_serv, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e == -1){
    printf("BLAD SOCKETU SERWERA.");
    exit(1);
  }
	printf("Polaczono z serwerem.\n");

  plik = fopen(nazwa_pliku, "r");
  if (plik == NULL) {
    printf("BLAD odczytu pliku.");
    exit(1);
  }

  send_file(plik, socket_serv);
  printf("Transfer pliku ukonczony pomyslnie.\n");

	printf("Zamykanie polaczenia...\n");
  close(socket_serv);

  return 0;
}
