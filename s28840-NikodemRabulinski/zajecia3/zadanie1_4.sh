#!/usr/bin/env bash

# Napisz skrypt, który 
# sprawdzi, czy w bieżącym katalogu jest więcej niż 5 plików. 
# Jeśli tak, to wypisze odpowiedni komunikat z informacją że tak jest. 
# Podpowiem:
# ls - wyświetla listę plików
# wc - word count - zlicza znaki, słowa i linie
# grep ma parametr który też może podawać ilość wystąpień wzorca w strumieniu - poszukać w manualu jaki to parametr
# może warto użyć także innego polecenia by znaleźć pliki?

# Jako że mamy sprawdzić czy w bieżącym katalogu jest więcej niż 5 *plików* uznałem,
# iż prostszym będzie użycie polecenia find, które wypisuje każdy plik w osobnej linii
CNT=$(find . -depth 1 -type f | wc -l)

# Jak już mamy ilość linii to wystarczy proste porównanie
if [[ "$CNT" > 5 ]]; then
  echo W aktywnym katalogu jest więcej niż 5 plików
fi
