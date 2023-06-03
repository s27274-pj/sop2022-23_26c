#!/usr/bin/env bash

# Wykonaj komendę ls -l w podpowłoce i przypisz ją do zmiennej X.
# Wyświetl zawartość tej zmiennej.
# Spraw, aby nie było różnicy (co najwyżej kolorki) między zwykłym wykonaniem komendy:
# ls -l
# a wypisaniem zawartości zmiennej X. Nie będzie dobrego rezultatu gdy zrobimy tak:
X=$(ls -l --color=always)
echo $X
# Zastanów się dlaczego.

# Rozwiązanie:
# Dzieje się tak dlatego, ponieważ jeśli nie weźmiemy zmiennej w cudzysłów,
# wszystkie znaki białe zostaną rozwinięte i będą potraktowane jako separatory argumentów.
# Dlatego też wszystko zostaje wydrukowane na jednej linii,
# gdyż komenda `echo` przechodzi przez wszystkie argumenty,
# które zostały do niej podane i drukuje je ze spacją między każdym z nich.
# Można to również zaobserwować na tym przykładzie:
echo foo             bar
# Który wydrukuje: foo bar
# Aby to naprawić, należy podać nasz tekst jako pojedynczy argument, czyli wziąć go w cudzysłów
echo "$X"
