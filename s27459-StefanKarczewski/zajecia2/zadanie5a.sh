#!/bin/bash

if [ $# == 0 ]; then
    echo "nie podano żadnych argumentów"
    exit 1
fi

name="$1"
# Muszę postawić spację przed `-1`, bo ${$zmienna:wartosc}
# to składnia na pobranie zmiennej z domyślną wartością, a tego nie chcemy zrobić.
last_char="${name: -1}"

# Możemy założyć, że imie jest żeńskie jeśli ostatnia litera imienia to 'a'
if [ $last_char == 'a' ]; then
    # Tutaj sama podmiana 'a' na 'ę' nie wystarczy, bo imię może mieć 'a' nie tylko na końcu
    # Dodatkowo, zapis substytucji (${var/from/to}) zamienia tylko pierwszy napotkany przypadek
    # Np. 'Małgorzata'/a/e -> 'Męłgorzata'
    # Zamiast substytucji wypiszę imię do przedostatniej litery i dodam na koniec 'ę'
    echo "${name} ma kota, a kot ma ${name:0:-1}ę"
else
    last_two_chars=${name: -2}

    # Dla męskich imion zakładamy specjalny przypadek, gdzie imię kończy się na 'ek'
    # Wtedy zamieniamy 'ek' -> 'ka'
    # Dla reszty męskich imion dodajemy na końcu 'a'
    if [ $last_two_chars == 'ek' ]; then
        # Np. Marek -> Marka, Jarek -> Jarka
        echo "${name} ma kota, a kot ma ${name:0:-2}ka"
    else
        # Np. Janusz -> Janusza, Przemysław -> Przemysława
        echo "${name} ma kota, a kot ma ${name}a"
    fi
fi
