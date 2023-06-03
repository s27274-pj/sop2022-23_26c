/* clang-format off */
/*----------------------------------------------------------------------------------------------------------*\
 |                                                                                                          |
 |  Napisz program, który będzie pozwalał na wyświetlenie dowolnego pliku w postaci takiej,                 |
 |  jak w heksedytorach. Program powinien wypisać zawartość pliku w postaci liczb szesnastkowych            |
 |  będących wartościami kolejnych bajtów tego pliku.                                                       |
 |                                                                                                          |
 |  Warto zrobić tak, aby kolejne wartości były pogrupowane po 16, 8 albo po 4 w celu poprawy czytelności.  |
 |                                                                                                          |
\*----------------------------------------------------------------------------------------------------------*/
/* clang-format on */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void abort(void) {
  fprintf(stderr, "Błąd odczytu\n");
  exit(1);
}

uint8_t to_ascii_char(uint8_t v) { return (v >= 0x20 && v <= 0x73) ? v : '.'; }

uint64_t print_row(FILE *f, uint64_t base) {
  uint64_t i, len;
  char buf[0x10];

  len = fread(buf, 1, 0x10, f);

  printf("%016llX: ", base);
  for (i = 0; i < len; i += 1)
    printf("%02hhX ", buf[i]);

  for (i = 0; i < 0x10 - len; i += 1)
    printf("   ");

  for (i = 0; i < len; i += 1)
    putchar(to_ascii_char(buf[i]));

  printf("\n");

  return len;
}

int main(int argc, const char *argv[]) {
  FILE *f = NULL;
  uint64_t base;

  /* Dokładnie taki sam mechanizm jak w poprzednim zadaniu */
  if (argc >= 2 && !(f = fopen(argv[1], "r")))
    abort();
  else if (!f)
    f = stdin;

  printf("Loading file: %s\n", argv[1] ? argv[1] : "stdin");
  /* Dla każdego rzędu 0x10 znaków */
  for (base = 0;; base += 0x10)
    /* Drukujemy ten rząd,
     i jeśli jest krótszy niż 0x10 to wychodzimy z pętli */
    if (print_row(f, base) < 0x10)
      break;

  if (f != stdin) {
    printf("Closing file: %s\n", argv[1]);
    fclose(f);
  }

  return 0;
}
