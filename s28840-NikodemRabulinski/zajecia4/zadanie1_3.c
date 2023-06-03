/* clang-format off */
/*------------------------------------------------------------------------*\
 |                                                                        |
 |  Napisz program wyświetlający tradycyjną choinkę o zadanej wysokości.  |
 |  Wysokość niech będzie podana jako parametr wywołania programu.        |
 |                                                                        |
\*------------------------------------------------------------------------*/
/* clang-format on */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abort(void) {
  fprintf(stderr, "Nie podano liczby\n");
  exit(1);
}

int main(int argc, const char *argv[]) {
  size_t pos;
  int h, i, j;

  /*
   * Jedyne co tu robię inaczej to odczytywanie z argumentów
   * zamiast standardowego wejścia.
   *
   * Najpierw sprawdzam, czy podane zostały co najmniej dwa argumenty
   * (z zajęć z bash-a pamiętamy, że pierwszy argument to nazwa programu, który
   * wywołujemy).
   *
   * Następnie używam sscanf, które działa tak samo jak scanf tylko na ciągach
   * znaków. Używam też dyrektywy %n (w tym przypadku %zn aby odczytać jako
   * size_t, lecz to nie jest ważne), która zapisuje w podanej zmiennej ilość
   * znaków do tej pory odczytanych. Przyda nam się to za moment.
   *
   * Na koniec sprawdzam, czy ilość odczytanych znaków równa jest długości
   * argumentu. Nie jest to bardzo ważne, natomiast sprawia to, że jeśli ktoś
   * wywoła ten program z argumentem 5foo, to dostanie błąd zamiast
   * potraktowania tego jako po prostu 5 i zignorowaniu reszty.
   */
  if (argc < 2 || !sscanf(argv[1], "%d%zn", &h, &pos) || pos != strlen(argv[1]))
    abort();

  /*
   * Standardowy algorytm na drukowanie "tradycyjnej choinki".
   *
   * Zewnętrzna pętla przechodzi przez każdy rząd choinki,
   * a wewnętrzne pętle przez każdą z kolumn.
   */
  for (i = 0; i < h; i += 1) {
    /* Najpierw drukujemy odpowiednią ilość spacji aby choinka była wyśrodkowana
     */
    for (j = 0; j < h - i - 1; j += 1)
      printf(" ");
    /* A następnie samą choinkę */
    for (j = 0; j < i * 2 + 1; j += 1)
      printf("*");
    printf("\n");
  }

  return 0;
}
