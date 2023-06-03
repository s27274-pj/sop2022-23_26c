/* clang-format off */
/*--------------------------------------------------------------------------------------------------------------*\
 |                                                                                                              |
 | Napisz program, który uruchomi 100 procesów potomnych w taki sposób, że będzie jeden rodzic i 100 potomków.  |
 | Proces główny niech oczekuje na zakończenie wszystkich procesów potomnych.                                   |
 |                                                                                                              |
\*--------------------------------------------------------------------------------------------------------------*/
/* clang-format on */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROCESSES_TO_SPAWN 10

int child() {
  printf("PID: %d\tPPID: %d\n", getpid(), getppid());
  while (1)
    pause();
  return 0;
}

int main() {
  int status, i;

  for (i = 0; i < PROCESSES_TO_SPAWN; i += 1)
    switch (fork()) {
    case -1:
      fprintf(stderr, "Fork się nie powiódł\n");
      return 1;
    case 0:
      return child();
    }

  waitpid(0, &status, 0);

  return 0;
}
