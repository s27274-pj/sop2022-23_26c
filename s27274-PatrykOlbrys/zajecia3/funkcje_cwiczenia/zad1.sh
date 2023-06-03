#!/bin/bash

# Colors are in SGR parameters: 0 = black, 1 = red, 2 = green, 3 = brown, 4 = blue, 5 = magenta, 6 = cyan, 7 = white.

# Funkcja wypisująca tekst pokolorowany na zadany kolor
# Argumenty: $1 - tekst, $2 - kolor (od 0 do 7)
function print_color_text {
  local text="$1"
  local color="$2"
  
  # Ustaw kod koloru
  local color_code="3${color}"
  
  # Wypisz tekst w odpowiednim kolorze
  echo -e "\033[${color_code}m${text}\033[0m"
}

print_color_text $1 $2
