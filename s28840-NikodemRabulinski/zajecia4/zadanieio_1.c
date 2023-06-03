/* clang-format off */
/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Napisz program wczytujący z pliku tekstowego ciąg liczb.                |
 |  Format pliku jest taki:                                                 |
 |    liczba elementów ciągu (jako liczba naturalna)                        |
 |    kolejne liczby - każda w nowej linii                                  |
 |                                                                          |
 |  Niech program wypisze je w odwrotnej kolejności.                        |
 |  Program powinien przyjmować zero albo jeden argument:                   |
 |    jeśli nie podano argumentu, to ma wczytywać ze standardowego wejścia  |
 |    jeśli podano argument, to jest to nazwa pliku do wczytania            |
 |                                                                          |
\*--------------------------------------------------------------------------*/
/* clang-format on */
#include <stdio.h>
#include <stdlib.h>

void abort(void) {
  fprintf(stderr, "Błąd odczytu\n");
  exit(1);
}

/*
 * Funkcja pomocnicza.
 * Zakłada, że może pobrać liczbę z danego pliku,
 * a jeśli nie jest to możliwe to kończy program.
 */
int getnum(FILE *f) {
  int n, res;
  res = fscanf(f, "%d\n", &n);
  if (res == 0 || res == EOF)
    abort();
  return n;
}

int main(int argc, const char *argv[]) {
  FILE *f = NULL;
  int i, amt, *buf;

  /*
   * Tak samo jak w poprzednim zadaniu, z tym,
   * że tu otwieramy podany plik zamiast czytać liczby
   */
  if (argc >= 2 && !(f = fopen(argv[1], "r")))
    abort();
  /*
   * Lub, jeśli nie został podany argument
   * - używamy standardowego wejścia
   */
  else if (!f)
    f = stdin;

  /* Czytamy ilość liczb, których się spodziewamy */
  amt = getnum(f);
  /* I alokujemy bufor o wymaganym rozmiarze */
  buf = calloc(amt, sizeof(int));
  if (!buf) {
    fprintf(stderr, "Błąd alokacji\n");
    return 1;
  }

  for (i = 0; i < amt; i += 1)
    buf[i] = getnum(f);

  /* Zamykamy jakiś plik jedynie jeśli go otworzyliśmy */
  if (f != stdin)
    fclose(f);

  for (i = amt - 1; i >= 0; i -= 1)
    printf("%d: %d\n", i, buf[i]);

  /* Na koniec zwalniamy bufor */
  free(buf);

  return 0;
}
