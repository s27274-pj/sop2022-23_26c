#include <stdio.h>
#include <signal.h>

void handle_signal(int signal){
  if (signal == SIGUSR1){
    printf("Otrzymano sygnał SIGUSR1. Program zakończony.\n");
        exit(0);
  }
}

int main(){

  printf("PID - %d \n", getpid());

  signal(SIGUSR1, handle_signal);

  while (1){
    
  }

  return 0;
}


==============
Aby sprawdzic dzialanie, otwieram drugi terminal, i przy uzyciu "kill -10 pid_programu" wysylam sygnal SIGUSR1.
W poprzednim terminalu dostaje to:
"PID - pid_programu, Otrzymano sygnał SIGUSR1. Program zakończony."
