#!/bin/bash
if [ $# -eq 0 ]; then
  echo "Brak argumentu"
  exit 1
fi
first_char=${1:0:1}
last_char=${1: -1}

echo $first_char
echo $last_char
name=$1

GREEN=$(printf '\e[32m')
NC=$(printf '\e[0m')

name=$(echo -e $name | sed "s/SOP/${GREEN}SOP${NC}/g")
echo -e $name
