#!/usr/bin/env bash

if ! [[ "$1" ]]; then
  echo "Proszę podać tekst do walidacji."
  exit
fi
./zad1.sh "$1"
./zad2.sh "$1"
./zad3.sh "$1"

#włączam każdy skrypt z pierwszym argumentem którym powinien być tekst do sprawdzenia
