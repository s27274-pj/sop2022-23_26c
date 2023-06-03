#!/bin/bash

arg=$1

if [[ $# == 0 ]]; then
  echo "Nie podano żadnych argumentów!"
elif [[ $# -ge 2 ]]; then
# -ge Greater or equal
  echo "Podaj tylko jeden argument!"
elif [[ "$arg" =~ (?!00-000)^[0-9][0-9]-[0-9][0-9][0-9]$ ]]; then
  echo "kod pocztowy"
elif [[ "$arg" =~ ^[A-PR-UWZĄĆĘŁŃÓŚŹŻ][a-ząćęłńóśźż]+$ ]]; then
  echo "imię"
elif [[ "$arg" =~ ^[a-zA-Z_+-]+[a-zA-Z_+-[0-9.]*@[a-zA-Z0-9.-]+.[a-zA-Z]{2,}$ ]]; then
  echo "email"
fi
