#!/bin/bash

text=$1

if [[ $text =~ ^[A-ZĄĆĘŁŃÓŚŹŻ][a-ząćęłńóśźż]+$ ]]; then
  echo "Podany tekst: $text to imię."
elif [[ $text =~ ^[0-9]{2}[-][0-9]{3}$ ]]; then
  echo "Podany tekst: $text to kod pocztowy."
elif [[ $text =~ ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$ ]]; then
  echo "Podany tekst: $text to adres e-mail."
else
  echo "Podany tekst: $text nie jest ani imieniem, ani kodem pocztowym, ani adresem e-mail."
fi
