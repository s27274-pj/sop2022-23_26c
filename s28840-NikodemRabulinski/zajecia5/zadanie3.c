/* clang-format off */
/*------------------------------------------------------------------------------------------------------------------------------*\
 |                                                                                                                              |
 |  Napisz program, który będzie pobierał jeden argument z wiersza poleceń i będzie obliczał w 2 procesach:                     |
 |  Proces rodzica: Wartość sumy liczb od 0 do wartości zadanej jako pierwszy argument wykonania programu.                      |
 |  Proces potomny: Wypisujący liczby nieparzyste od 1 do wartości zadanej jako pierwszy argument wykonania programu.           |
 |  Program powinien wypisać wyniki w kolejności takiej, że najpierw wypisze wynik proces potomny, a następnie proces rodzica.  |
 |                                                                                                                              |
\*------------------------------------------------------------------------------------------------------------------------------*/
/* clang-format on */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int arg;

int child() {
  int i;

  printf("-- Dziecko --\n");
  for (i = 1; i <= arg; i += 2)
    printf("%d\n", i);

  return 0;
}

int parent() {
  int status, i, sum;
  waitpid(0, &status, 0);

  printf("-- Rodzic --\n");
  for (sum = 0, i = 1; i <= arg; i += 1) {
    sum += i;
    printf("%d\n", sum);
  }

  return 0;
}

int main(int argc, const char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Nieprawidłowa ilość argumentów\n");
    return 1;
  }

  arg = atoi(argv[1]);

  switch (fork()) {
  case -1:
    fprintf(stderr, "Fork nie powiódł się\n");
    return 1;
  case 0:
    return child();
  default:
    return parent();
  }
}
