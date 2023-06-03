#!/usr/bin/env bash

# W przypadku bardzo podobnych rozwiazań nie będę ich uznawał.
# - Przygotuj wyrażenie regularne, które będzie sprawdzało,
# czy tekst jest poprawnie napisanym polskim imieniem
# (od wielkiej litery, może mieć tylko litery i zawierać polskie znaki).
# - Przygotuj wyrażenie regularne sprawdzające czy tekst jest kodem pocztowym
# (cały tekst, czyli zaczyna się od cyfry i kończy się cyfrą).
# - Przygotuj wyrażenie regularne sprawdzające e-mail.
# 
# Napisz skrypt który będzie pobierał jeden argument z linii komend
# i wypisywał informację o tym, czy jest to imie, kod pocztowy, czy też email.

# Najpierw sprawdzamy czy jest to imię.
# Oczywiście pierwszym znakiem może być jedynie wielka litera od A do Z
# (wydaje mi się, że polskie imiona nie zaczynają się od polskich znaków?
# Jeśli się mylę to przepraszam).
# A każda następna to mała litera między a i z lub którykolwiek z polskich znaków.
if [[ "$1" =~ ^[A-Z][a-ząćęłóńś]+$ ]]; then
  echo imie
# Jeśli to nie imię to sprawdzamy czy jest to kod pocztowy.
# Bardzo trywialny schemat, najpierw dwie cyfry, myślnik, i trzy cyfry.
elif [[ "$1" =~ ^[0-9]{2}-[0-9]{3}$ ]]; then
  echo kod pocztowy
# Jeśli to nie kod pocztowy to naszą ostatnią deską ratunku jest email.
# Tu jestem dość liberalny nie sprawdzam dokładnie formatu według RFC,
# po prostu sprawdzam czy jest to słowo, które składa się z dozwolonych znaków,
# znaku "małpy" i kolejnego ciągu dozwolonych znaków.
elif [[ "$1" =~ ^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$ ]]; then
  echo email
fi
