#!/usr/bin/env bash

echo === Podpunkt 1. ===
# Pamiętasz jedno z zadań poprzednich?
## A=Ala
## echo $A ma kota, a kot ma ${A}ę
# Przerób je tak, aby tekst wypisywał się poprawnie.
# Napisz skrypt, który będzie wypisywał taki tekst także dla imion męskich.
# Pomijamy zdrobnienia i imiona które się dziwnie odmieniają (na przykład Marek).
# Niech skrypt ten przyjmuje jeden argument - imię. Przykładowe wywołanie:
## $ ./pszetżkole Ala
## Ala ma kota, a kot ma Alę
## $ ./pszetżkole Justyna
## Justyna ma kota, a kot ma Justynę
## $ ./pszetżkole Stefan
## Stefan ma kota, a kot ma Stefana
# Czy jest to możliwe w czystym bash-u?

# Oczywiście, że jest
# Najpierw zakładamy, że imię jest męskie - dodajemy po prostu 'a' na koniec
# np. Nikodem -> Nikodema
MESKIE="${1}a"
# Jeśli imię już się kończyło na 'a' to znaczy,
# że powinniśmy je odmienić przez zamianę końcówki na 'ę'.
# Wiemy więc, że jeśli nasz argument kończy się 'aa' to znaczy,
# że wystarczy, że zamienimy to na 'ę'.
IMIE="${MESKIE/%aa/ę}"

echo "$1" ma kota, a kot ma "$IMIE"

echo === Podpunkt 2. ===
# Napisz skrypt, który wczyta jako argument jakiś tekst. Skrypt ten wypisze kolejno:
# Pierwszy znak z argumentu
# Ostatni znak z argumentu
# Zamieni w argumencie każdy tekst SOP na tekst poniżej (zastosuj echo z przełącznikiem -e):
# \e[32mSOP\e[0m

LEN=${#1}
echo Pierwszy znak: "${1:0:1}"
echo Ostatni znak: "${1:LEN-1:1}"
echo -e "${1//SOP/\\e[32mSOP\\e[0m}"
