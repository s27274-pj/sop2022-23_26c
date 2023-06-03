#!/usr/bin/env bash

# Napisz skrypt, który wczyta listę plików do wypisania z wiersza poleceń,
# a następnie wypisze ich zawartości raz w kolejności od początku do końca, a raz na odwrót.

# Szczerze powiedziawszy, nie do końca rozumiem to zadanie.
# Widzę kilka możliwych zinterpretowań, ale ta którą postanowiłem wykonać to:
# Dla podanej listy plików, np. foo, bar, baz, drukujemy na ekranie najpierw ich zawartości po kolei:
#   *zawartość foo*
#   *zawartość bar*
#   *zawartość baz*
# A następnie robimy to samo, lecz w odwrotnej kolejności (bez odwracania zawartości plików):
#   *zawartość baz*
#   *zawartość bar*
#   *zawartość foo*

# Najpierw ustawiam IFS czyli separator słów na znak nowej linii. Przyda on się później
IFS=$'\n'

# Wypisanie plików po kolei to kwestia wywołania cat z kolejnymi argumentami
cat "$@"

# Wypisanie plików ale w odwrotnej kolejności jest już nieco trudniejsze i tu z pomocą przychodzi nam IFS.
# Naszym celem jest wzięcie listy argumentów foo bar baz i zrobienie z niej listy argumentów baz bar foo.
# Narzędzie tac (odwrócony cat, bardzo sprytne) wypisuje linie w odwrotnej kolejności.
# Jeśli zajrzymy znów do dokumentacji bash-a, możemy znaleźć to:
# *      Expands to the positional parameters, starting from one.
#        [...]
#        That is, "$*" is equivalent to "$1c$2c...", where c is the first character of the value of the IFS
#        variable.
# Czyli eureka, dokładnie to co chcemy zrobić, dlatego też ustawiliśmy IFS na znak nowej linii.
# Przekazujemy do tac $*, które rozszerzone będzie wyglądać tak:
# foo
# bar
# baz
# A tac nam zwróci:
# baz
# bar
# foo
# Gdzie bash to zinterpretuje jako osobne arugmenty i wypisze pliki, od ostatniego do pierwszego.
cat $(tac <<< $*)

# Oczywiście ta metoda nie jest bez wad. Jeśli plik ma już w swojej nazwie znak nowej linii,
# to nasz skrypt sobie z nim niestety nie poradzi, ale dla uproszczenia odpuściłem sobie to rozwiązanie.
# Przynajmniej obsługujemy poprawnie wszystkie inne znaki białe, a do tego jest to bardzo eleganckie rozwiązanie,
# więc unaję to za odpowiedni kompromis.
