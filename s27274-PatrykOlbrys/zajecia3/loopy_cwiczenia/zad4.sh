#!/bin/sh

pattern="*.c"

for f in * ;
do
  if [[ $f == $pattern ]]; then
  cc $f -o ${f%.c}
  fi
done
