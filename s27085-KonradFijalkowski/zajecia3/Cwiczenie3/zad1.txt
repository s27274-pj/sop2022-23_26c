#!/usr/bin/env bash
function ChangeColors {
  if [[ $2 -ge 1 && $2 -le 7 ]]; then
    text=$1
    color=$2
    echo -e "\e[3${color}m${text}\e[0m"
  else
    echo "Podano zły numer koloru"
  fi
}
ChangeColors "wlazł kotek na płotek" 2
