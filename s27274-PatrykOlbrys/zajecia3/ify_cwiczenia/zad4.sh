#!/bin/sh

if [[ $(ls -p | grep -v / | wc -l) > 5 ]]; then
    echo "W bieżącym katalogu znajduje się więcej niż 5 plików"
fi

# ls -p dodaje do wszystkich katalogów na końcu znak "/"
# A grep -v zwraca tylko linie nie zawierające znaku "/"
