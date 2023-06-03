#!/usr/bin/env bash

# Napisz skrypt, który wypisze listę plików i katalogów bieżącego katalogu
# poprzedzając każdą nazwę pliku tekstem "Patrzcie Państwo, oto plik: ". 

# Wykorzystujemy tu fakt, iż * jest rozwijana na poziomie basha do wszystkich plików i katalogów bieżącego katalogu
for f in *
do
  echo "Patrzcie Państwo, oto plik:" "$f"
done

# Tak samo jak wcześniej, moglibyśmy to rozwiązać jednym poleceniem, beż użycia pętl:
#   printf 'Patrzcie Państwo, oto plik: %s\n' *
# I efekt byłby dokładnie taki sam. Bierze to też pod uwagę spacje w nazwach plików czy inne znaki białe.
