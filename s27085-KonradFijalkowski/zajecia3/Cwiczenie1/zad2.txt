#!/usr/bin/env bash

if [[ -f ./config.cfg ]]; then #-f zwraca true jeśli file istnieje i jest plikiem
  echo "Config.cfg istnieje, wykonywanie"
  ./config.cfg
elif [[ $# -eq 1 ]]; then
  ./"$1"
else
  echo "Błąd"
fi


#https://www.man7.org/linux/man-pages/man1/test.1.html
