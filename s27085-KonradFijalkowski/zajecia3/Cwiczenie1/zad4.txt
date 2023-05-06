#!/usr/bin/env bash

#metoda z ls
if [[ "$(ls | wc -l)" -gt 5 ]]; then
  echo "W katalogu jest więcej niż 5 plików"
fi

#metoda z findem
if [[ "$(find . -maxdepth 1 -type f | wc -l)" -gt 5 ]]; then
 echo "W katalogu jest więcej niż 5 plików"
fi
