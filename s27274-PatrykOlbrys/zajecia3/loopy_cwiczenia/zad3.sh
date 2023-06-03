#!/bin/sh

IFS=$'\n' # Ustawienie separatora pól wewnętrznych na znak nowej linii

for f in * ;
do
  echo "Patrzcie Państwo, oto plik: " $f
done
