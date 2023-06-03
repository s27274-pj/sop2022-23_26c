/* clang-format off */
/*--------------------------------------------------------------------*\
 |                                                                    |
 |  Napisz program, który uruchomi podproces za pomocą komendy fork.  |
 |  Niech proces rodzica oczekuje na proces potomka.                  |
 |  Oba procesy powinny wypisać swój PID oraz PPID.                   |
 |                                                                    |
\*--------------------------------------------------------------------*/
/* clang-format on */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int parent() {
  int status;
  waitpid(0, &status, 0);

  printf("-- Rodzic --\n"
         "PID:  %d\n"
         "PPID: %d\n",
         getpid(), getppid());
  return 0;
}

int child() {
  printf("-- Dziecko --\n"
         "PID:  %d\n"
         "PPID: %d\n",
         getpid(), getppid());
  return 0;
}

int main() {
  switch (fork()) {
  case -1:
    fprintf(stderr, "Fork się nie powiódł\n");
    return 1;
  case 0:
    return child();
  default:
    return parent();
  }
}
