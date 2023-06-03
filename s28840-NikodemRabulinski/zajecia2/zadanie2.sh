#!/usr/bin/env bash

echo === Podpunkt 1. ===
# Zobacz taką serię poleceń:
# X=tekst
# echo $X
# bash
# echo $X
# Co się stało? Czy potrafisz wyjaśnić?

X=tekst # Przypisanie do zmiennej X
echo $X # Wypisanie zmiennej X
bash    # Uruchomienie nowej instancji basha
echo $X # Wypisanie zmiennej X

# Ale co to znaczy "uruchomienie nowej instancji basha"?
# No, to samo co wpisanie "bash" w terminalu, czy też po prostu otwarcie nowego terminala.
# Po prostu otwiera nam się nowy proces powłoki
# Można to bardzo łatwo zobaczyć wpisując exit kiedy zobaczymy znak zachęty i zmienna X zostanie wypisana ponownie!
# 
# Tak to wygląda na moim systemie
# bash-5.2$ zajecia2/zadanie2.sh
# === Podpunkt 1. ===
# tekst             <- Pierwsze wypisanie zmiennej X
# bash-5.2$ exit    <- Wywołanie bash (którego zamykamy przez wywołanie exit)
# exit
# tekst             <- Drugie wypisanie zmiennej X
# bash-5.2$         <- Zakończenie skryptu

echo === Podpunkt 2. ===
# Zobacz:
X=Tekst dłuższy
echo $X
# Co jest nie tak? jak to naprawić? Zobacz czy pomoże zastosowanie cudzysłowów i apostrofów.

# zajecia2/zadanie2.sh: line 32: dłuższy: command not found
# Dlaczego tak się dzieje?
# Ponieważ syntax FOO=a BAR=b BAZ
# oznacza ustawianie zmiennych środowiskowych tymczasowo na czas wykonywania danej komendy.
# To znaczy, że to co napisaliśmy bash zrozumiał jako ustawienie wartości X na 'Tekst'
# i wywołaniu komendy 'dłuższy' z tą zmienną.
# Możemy to łatwo pokazać wykonując
X=tEkSt printenv X
# Które pokaże nam 'tEkSt' w terminalu gdyż polecenie printenv zbiera zmienne środowiskowe
# i wypisuje zmienną o danej nazwie, jeśli istnieje.

# Czy pomoże zastosowanie cudzysłowów i apostrofów?
A="Teskt dłuższy w zmiennej A"
B='Teskt dłuższy w zmiennej B'
C=Możemy' mieszać'" cudzysłowy i apostrofy!?"
D=Ale 'tylko' "bez spacji pomiędzy nimi"

echo $A
echo $B
echo $C
echo $D
# Odpowiedź brzmi: pomoże. Pomogą nam zarówno cudzysłowa, apostrofy, jak i jedne i drugie?
# Ale dlaczego zmienna C działa, a zmienna D powoduje ten sam błąd:
# zajecia2/zadanie2.sh: line 51: tylko: command not found
# Odpowiedź jest prosta: Bash pozwala nam na używanie cudzysłowów i apostrofów
# aby połączyć wiele słow w jeden argument.
# Jeśli ktoś nie jest zaznajomiony z powłokami jak bash może to brzmieć dziwnie i dezorientująco,
# ale można to przedstawić w bardzo łatwy sposób:

test_argumenty () {
  echo Pierwszy argument: $1
}

test_argumenty to" będzie "'jeden argument' "a to już będzie osobny"

# I widzimy w terminalu
# Pierwszy argument: to będzie jeden argument
# Co pokazuje, że słowa posklejane cudzysłowami czy apostrofami są traktowane jako jedno słowo.

echo === Podpunkt 3. ===
# Zobacz:
X="Tekst 1"
Y="tekst:$X"
echo "$Y"
Y='tekst:$X'
echo "$Y"
Y=tekst:$X
echo "$Y"
# Jaka jest różnica między " a ' ?

# Różnica jest prosta:
# cudzysłowy pozwalają na używanie zmiennych w nich (i nie tylko),
# a apostrofy dają nam 'surowy' teskt, tj. dokładnie taki jaki damy dostajemy z powrotem

echo == Podpunkt 4. ===
A=Ala
echo $A ma kota, a kot ma ${A}ę
# Tak, tu coś będzie nie tak, zaraz to naprawimy.
