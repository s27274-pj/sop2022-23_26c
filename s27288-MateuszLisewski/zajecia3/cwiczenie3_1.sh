#!/bin/bash

# argumenty: $1 - tekst, $2 - kolor (0-7)
function koloruj {
  echo -e "\033[3${2}m$1\033[0m"
}
