#!/usr/bin/env bash

# Przygotuj skrypt z funkcją która będzie wypisywała tekst pokolorowany na zadany kolor.
# Niech funkcja ta przyjmuje dwa argumenty - tekst i kolor. 
# Zobacz man console_codes oraz składnię komendy echo (lub przykład z poprzednich zajęć).

# Fragment man console_codes:
# 30 - set black foreground
# 31 - set red foreground
# 32 - set green foreground
# 33 - set brown foreground
# 34 - set blue foreground
# 35 - set magenta foreground
# 36 - set cyan foreground
# 37 - set white foreground

# cout - color out
# (bardzo sprytna nazwa, wiem, zwłaszcza w kontekście tego, że będziemy mieli C++ na tych zajęciach)
# Pierwszy argument to kolor, drugi to teskt do wypisania
# Dostępne kolory: black red green brown blue magenta cyan white
function cout (
  # Robimy z tą funkcją coś bardzo ciekawego - a mianowicie dzięki użyciu () zamiast {}
  # wykonujemy ją w tzw subshell-u.
  # Co nam to daje? A mianowicie możemy dzięki temu użyć polecenia set i nie wpłynąć na resztę skryptu,
  # czego raczej nie chcemy.
  # Oznacza to w uproszczeniu tyle, że nasza funkcja wykona się w nowej instancji bash-a,
  # zamiast tej w której wykonuje się reszta skryptu.
  # set -e sprawia, że skrypt zostanie przerwany jeśli którekolwiek polecenie nie wykona się poprawnie
  # set -o pipefail sprawia, że jeśli którekolwiek polecenie wśród przekierowań nie wykona się poprawnie,
  # całe polecenie zwróci kod błędu.
  # Dzięki temu nie muszę sprawdzać czy podany przez użytkownika kolor jest prawidłowy,
  # tylko wykonywanie funkcji zostanie przerwane kiedy grep nie znajdzie koloru w tablicy (przez co zwróci status 1)
  set -eo pipefail
  # Tworzę tablicę ze wszystkimi dostępnymi kolorami
  COLORS=(black red green brown blue magenta cyan white)
  # Następnie wypisuje je wszystkie, każdy w osobnej linii
  # i używam polecenia grep z przełącznikiem -n aby znaleźć numer koloru, który został podany
  N=$(printf '%s\n' "${COLORS[@]}" | grep -n -e "$2" | head -n1 | cut -d':' -f1)
  # Następnie zwiększam tę wartość o 29 (gdyż pierwsza to linia ma numer 1, a pierwszy kolor ma numer 30)
  CN=$((N + 29))

  # I wyświetlam pokolorowany tekst, tak jak to robiliśmy na pierwszych zajęciach
  echo -e "\e[${CN}m${1}\e[0m"
)

# Proste sprawdzenie
cout "Tekst na zielono" 'green'
cout "Tekst na błękitno" 'cyan'
cout "Tekst na czerwono" 'red'
cout "Tekst na ???" '???'
# ^ Powyższy tekst nie zostanie wyświetlony
cout "Teskt na niebiesko" 'blue'
