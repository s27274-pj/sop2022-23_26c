#!/bin/bash

# Funkcja obliczająca rekurencyjnie ciąg Fibonacciego
# Argument: $1 - numer wyrazu ciągu do obliczenia
function fibonacci {
  local n="$1"
  
  # Warunek kończący rekurencję
  if (($1 <= 0)); then
    return "Błąd: argument musi być dodatni."
  elif (($1 == 1 || $1 == 2)); then
    return "1"
  else
  # Obliczenie wartości rekurencyjnie
  local a=$(fibonacci $((n - 1)))
  local b=$(fibonacci $((n - 2)))
  local result=$((a + b))
  
  # Zwrócenie wyniku
  return "$result"
  fi
}

# Przykładowe użycie
fibonacci 7
