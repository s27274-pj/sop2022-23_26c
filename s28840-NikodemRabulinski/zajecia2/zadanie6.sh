#!/usr/bin/env bash

# Teraz postaraj się zrobić to zadanie z haczykiem i podmianą fragmentu zmiennej (Ala ma ...)

# Jeśli dobrze rozumiem, przez haczyk mamy na myśli tu zdrobnienia i imiona, które się "dziwnie" odmianiają?
# Mamy więc kilka zasad do przestrzegania:
# - Jeśli imię kończy się na 'a', zamieniamy to na 'ę' (Olga -> Olgę, Ala -> Alę, Kuba -> Kubę)
# - Jeśli imię posiada tzw. 'e ruchome' to w bierniku najczęśniej znika (Kacper -> Kacpra, Marek -> Marka)
#   - Dla uproszczenia założę, że e ruchome występuje w każdym imieniu zakończonym na:
#     -er, -ek, -ec, -ew
# - Jeśli imię kończy się na 'o', zamieniamy to na 'a' (Apollo -> Apolla)
# - W każdym innym wypadku tylko dopisujemy 'a'

E_RUCH=$(sed 's,e\([rkcw]\)$,\1,' <<< "$1") # Najpierw zajmujemy się e ruchomym
                                            # Usuwamy je zanim zaczniemy inne transformacje
A_KON="${E_RUCH}a"                          # Następnie dopisujemy 'a'
AA="${A_KON/%aa/ę}"                         # Zamieniamy 'aa' na 'ę'
OA="${AA/%oa/a}"                            # I 'oa' na 'a'
echo "$1" ma kota, a kot ma "$OA"           # Czyli tak jak to robiłem w poprzednim zadaniu

# Dałoby się to zrobić w samym bashu, ale byłoby to znacznie mniej czytelne i bardziej nieporęczne,
# więc zdecydowałem się na użycie 'sed' do pierwszego kroku :)
