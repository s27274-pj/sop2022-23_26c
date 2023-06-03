#!/usr/bin/env bash

for i in *.c; do
  [[ -e $i ]] || break
  echo "$i"
  cc "$i" -o "${i%%.*}"
done
