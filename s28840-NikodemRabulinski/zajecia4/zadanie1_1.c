/* clang-format off */
/*----------------------------------------------------------------------------------------------------*\
 |                                                                                                    |
 |  Napisz program obliczający sumę liczb wprowadzonych przez użytkownika (ze standardowego wejścia)  |
 |  i wypisujący wynik na standardowe wyjście.                                                        |
 |                                                                                                    |
\*----------------------------------------------------------------------------------------------------*/

/*
 * Pierwsze co robimy w pliku to importujemy wymagane pliki nagłówkowe.
 * Jako, że będą one się powtarzać w każdym zadaniu wyjaśnię je raz tutaj i nie
 * będę o nich więcej wspominać. Zakładam również, że nie muszę wyjaśniać co to
 * pliki nagłówkowe.
 *
 * Najczęściej będą pojawiać się w moich rozwiązaniach następujące nagłówki:
 *   stdio.h - Wszelaka funkcjonalność I/O, pliki, czytanie, pisanie, itd.
 *   stdlib.h - Różne funkcje narzędziowe od atoi po rand po zarządzanie pamięcią
 *   stdbool.h - Zawiera definicję typu logicznego i wartości prawda i fałsz
 *   stdint.h - Zawiera definicje typów numerycznych o stałych szerokościach,
 *              ich minimalne i maksymalne wartości, oraz makra ułatwiające tworzenie nich
 *   inttypes.h - Pokrewny z poprzednim, zawiera funkcje i makra usprawniające pracę z tymi typami,
 *                np. PRIxN, które wydrukuje odpowiednik %x, ale dla typu o szerokości N
 *   string.h - Funkcje służące do manipulacji ciągami znaków i listami.
 *   stddef.h - Standardowe definicje jak size_t, offsetof, NULL itp.
 *
 * Jeśli pojawi się jakiś inny nagłówek, to uzasadnię jego uwzględnienie.
 *
 * Oprócz tego też opiszę ten plik bardzo dokładnie aby móc korzystać ze skrótów
 * myślowych w kolejnych plikach i pomijać wyjaśnianie pewnych rozwiązań.
 */
/* clang-format on */
#include <stdio.h>
#include <stdlib.h>

/*
 * Funkcja drukująca błąd i kończąca wykonywanie programu.
 * Nie przyjmuje i nigdy nie przyjmie żadnych parametrów,
 * dlatego ma listę argumentów void.
 *
 * Tę lub podobną funkcję również będę bardzo często definiował w zadaniach.
 */
void abort(void) {
  fprintf(stderr, "Nie podano liczby\n");
  exit(1);
}

int main() {
  /*
   * Najpierw deklarujemy zmienne.
   * Jako iż korzystamy z flagi -ansi (która jest równa c_std=c89 lub
   * c_std=c90), wszystkie zmienne musimy zadeklarować na początku funkcji, w
   * przeciwnym razie kompilator na nas nakrzyczy.
   */
  int a, b;

  /* clang-format off */
  /*
   * Tu wykorzystujemy dwa fakty:
   *
   * Pierwszy to fakt, że funkcje z rodziny scanf jako wynik zwracają
   * ~ilość poprawnie odczytanych formatów~.
   * Co to znaczy?
   * To znaczy tyle, że jeśli jako argument do scanf damy "%d %d",
   * a na standardowym wejściu pojawi się "10 foo" to scanf zwróci 1.
   * Jeśli z takim samym argumentem pojawi się "10 20" to scanf zwróci 2.
   * Natomiast jeśli znów z tym samym argumentem poajwi się "foo bar" to scanf zwróci 0.
   *
   * Drugi to fakt, że w pewnym sensie w C każdy typ jest typem logicznym.
   * To znaczy, każda wartość równa 0 jest traktowana jako fałsz,
   * a każda wartość różna od 0 jest traktowana jako prawda.
   *
   * Biorąc pod uwagę te oba fakty możemy wywnioskować,
   * że poniższe scanf może jedynie zwrócić wartość 2 jeśli zostały podane 2
   * prawidłowe liczby, a w przeciwnym razie 0 lub 1. Dlatego też używam
   * konstrukcji JEŚLI scanf różne od 2 TO przerwij wykonywanie programu.
   *
   * Ale teraz możemy się zastanawiać - skąd wiemy,
   * że dostaniemy kolejno dwie liczby niezależnie jak będą rozdzielone?
   * Wynika to z tego jak scanf jest zaimplementowane i jak działają strumienie
   * wejścia/wyjścia. Bez zgłębiania się w detale, możemy znaleźć ten fragment w
   * dokumentacji rodziny funkcji scanf
   *
   *> The format string consists of a sequence of directives which
   *> describe how to process the sequence of input characters.
   *> [...]
   *> A directive is one of the following:
   *>   A sequence of white-space characters (space, tab, newline,
   *>   etc.; see isspace(3)). This directive matches any amount
   *>   of white space, including none, in the input.
   *> [...]
   *
   * Co dla nas znaczy tyle, że jak w scanf damy spację (lub jakikolwiek inny znak biały)
   * to tak naprawdę może on oznaczać dowolny ciąg znaków białych (w tym zero).
   * Ale czy zero nie oznacza, że ktoś może podać "35" na wejścu i
   * dostaniemy a = 3, b = 5? Nie, gdyż %d i inne dyrektywy zczytujące liczby są
   * tzw. "zachłanne" lub "chciwe" tj. czytają ~jak najwięcej~ pasujących znaków.
   * (swoją drugą algorytmy, które czytają jak najmniej są zwane "leniwymi")
   *
   * Ma to różnicę jedynie przy podawaniu różnych dyrektyw.
   * Np. dla argumentu "%d %s" jeśli na wejściu pojawi się "5foo" scanf I TAK
   * zwróci 2 i I TAK przypisze 5 do pierwszego argumentu, a "foo" do drugiego.
   */
  /* clang-format on */
  if (scanf("%d %d", &a, &b) != 2)
    abort();

  /*
   * Na koniec drukujemy wynik.
   * I kończymy program bez żadnego błędu (kod wyjścia 0)
   */
  printf("%d + %d = %d\n", a, b, a + b);
  return 0;
}
