/* clang-format off */
/*-------------------------------------------------------------------------------------*\
 |                                                                                     |
 |  Przerób ten program tak, aby wartość była zwracana jako kod zakończenia programu.  |
 |  Wyświetl tą wartość z linii komend.                                                |
 |                                                                                     |
\*-------------------------------------------------------------------------------------*/
/* clang-format on */

#include <stdio.h>
#include <stdlib.h>

void abort() {
  fprintf(stderr, "Nie podano liczby\n");
  exit(1);
}

int main() {
  int a, b;
  if (scanf("%d %d", &a, &b) != 2)
    abort();
  /*
   * Zadanie identyczne jak poprzednie,
   * jedyna różnica znajduje się w tym miejscu
   */
  return a + b;
}
