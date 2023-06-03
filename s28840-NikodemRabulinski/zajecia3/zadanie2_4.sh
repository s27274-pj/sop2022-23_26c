#!/usr/bin/env bash

# Napisz skrypt, który dla każdego pliku w bieżącym katalogu, który ma rozszerzenie .c wykona taką komendę:
#  cc (tu_nazwa_pliku) -o (tu_nazwa_pliku_bez_rozszerzenia)

# Tu wykorzystujemy to samo co w poprzednim poleceniu, z tą różnicą, że chcemy tylko pliki, które kończą się na .c
for f in *.c
do
  # I dla każdego z nich używamy manipulacji zmiennych aby pozbyć się rozszerzenia
  cc "$f" -o "${f/%.c/}"
done