/* clang-format off */
/*-----------------------------------------------------------------------------------------------------------------------*\
 |                                                                                                                       |
 |  Napisz program, który uruchomi 100 procesów w taki sposób, że każdy kolejny potomek stworzy potomka.                 |
 |  Niech każdy proces poczeka na zakończenie procesu potomka.                                                           |
 |                                                                                                                       |
 |  Możesz korzystać z oczekiwania na wejście lub z komendy sleep i zobacz czy drzewko procesów jest takie,              |
 |  jak się spodziewasz (możesz w tym celu ograniczyć liczbę procesów do 10). Zobacz podpowiedź na początku tej strony.  |
 |                                                                                                                       |
 |  Czyli drzewo procesów ma wynikowo wyglądać tak: główny -> potomek1 -> potomek2 -> ... -> potomek99 -> potomek100     |
 |  Przydatne przy sprawdzaniu: Drzewo procesów można wydrukować poleceniem pstree                                       |
 |                                                                                                                       |
\*-----------------------------------------------------------------------------------------------------------------------*/
/* clang-format on */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int processes_to_spawn = 10, status;

  while (processes_to_spawn)
    switch (fork()) {
    case -1:
      fprintf(stderr, "Fork się nie powiódł\n");
      return 1;
    case 0:
      printf("PID: %d\tPPID: %d\n", getpid(), getppid());
      processes_to_spawn -= 1;
      break;
    default:
      printf("Procesów do stworzenia: %d\n", processes_to_spawn - 1);
      waitpid(0, &status, 0);
      return 0;
    }

  return 0;
}
