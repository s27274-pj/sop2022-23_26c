#!/bin/bash

IFS=$'\n'

for file in $(ls -1); do
  if [[ -e "$file" ]]; then
    echo "Patrzcie Państwo, oto plik: $file"
  fi
done
