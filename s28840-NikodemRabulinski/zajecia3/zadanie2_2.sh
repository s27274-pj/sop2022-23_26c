#!/usr/bin/env bash

# Napisz skrypt, który będzie wypisywał wszystkie argumenty wywołania skryptu
# (pamiętaj o tym, że argument może w sobie zawierać jakieś spacje)
# napisane w cudzysłowach.

# Jak wrócimy do dokumentacji, którą przywołałem w zadaniu 1 to zobaczymy, że "$@" robi dokładnie to,
# czego chcemy w tej sytuacji - każdy argument wstawia w cudzysłów co oznacza, że każdy argument,
# niezależnie czy ma w sobie spacje czy nie, będzie osobnym wywołaniem pętli
for arg in "${@}"
do
  echo '"'"$arg"'"'
done

# Alternatywnie, możemy w ogóle nie używać pętli i zrobić to w taki prosty sposób:
#   printf '"%s"\n' "$@"
# Co sprawi, że do każdego argumentu podanego do skryptu zostanie zaaplikowany string formatujący "%s",
# który robi dokładnie to czego chcemy - wyświetla zawartość arugmentu w cudzysłowach
