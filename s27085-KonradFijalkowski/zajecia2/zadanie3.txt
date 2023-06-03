#!/bin/bash

# Zadanie 3:
# Zobacz co przechowują zmienne i opisz jak rozumiesz uzyskany wynik.
# Do czego on jest i kiedy może się wg Ciebie przydać:

echo $PATH
# jest to zmienna ktora zawiera ścieżki do katalogów zawierających pliki wykonywalne używane przez inne programy
# pozwala to programom na dostanie się do innych często używanych programów dzięki zmiennej, a nie okreslonym ścieżkom

echo $RANDOM
# generuje losową liczbę całkowitą
# może przydać się do programu który potrzebuje zmienne różne od siebie mające generować jakiś zestaw danych (wartości rzutów kością etc)

echo $PWD
# wskazuje na ścieżke do katalogu w którym znajduje się wykonywany program
# można użyć do dowiedzenia się gdzie dokładnie skrypt się znajduje
echo $PS1
# nic nie zostalo wyświetlone, więc w tym wypadku musiałem poszukać w Internecie
# zmienna PS1 to zmienna środowiskowa/systemowa (ang. environmental variable), która określa format wiersza poleceń wyświetlanego w terminalu
# oznacza "Prompt String 1", i jest używany do określania wyglądu prompta

echo $USER
# jest przypisany do nazwy obecnego uzytkownika
# mozna uzyc np przy określaniu ścieżka do katalogu domowego obecnie zalogowanego użytkownika

echo $HOSTNAME
# posiada nazwe komputera
# można użyć do poznania w jakiej domenie komputer pracuje

echo $OSTYPE
# przechowuje tym systemu operacyjnego (linux-gnu)
