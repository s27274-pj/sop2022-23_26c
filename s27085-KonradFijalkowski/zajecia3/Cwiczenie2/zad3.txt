#!/usr/bin/env bash

#to zadanie nie wymaga akurat użycia zmiennej środowiskowej IFS,
# jako że LF (\n) jest już w niej zawarty
IFS=$'\n'
for i in *.txt; do
  [[ -e $i ]] || break
  echo "Patrzcie Państwo, oto plik: $i"
done
