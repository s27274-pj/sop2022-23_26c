#!/bin/bash

#Zadanie 2

#Zobacz taką serię poleceń:

X=tekst
echo $X
bash
echo $X

# Polecenie "bash" utworzylo podpowloke, i w niej wypisalo wartosc zmiennej $X
# Warto zaznaczyc ze slowo "tekst" ktore uzytkownik zobaczy na ekranie jest spowodowane poleceniem w 
# lini nr 4, a zas by zobaczyc wczesniejszy "teksty" nalezy oposcic obecna powloke poleceniem "exit"

#Zobacz:

X='Tekst dłuższy'
echo $X

# Dodanie zarowno apostrofow jak i cudzyslowow rozwiazuje problem, bez nich slowo dluzszy jest interpretowane jako kolejna komenda
# Co ciekawe patrzac na dzialanie pierwszej czesci tego zadania (uzycia polecenia bash) wyglada na to,
# ze system zatrzymuje calkowicie dzialania poprzedniej powloki,
# a wiec string "Tekst dluzszy" jest wyswietlany dopiero po zamknieciu otwartej powloki.

#Zobacz:

X="Tekst 1"
Y="tekst:$X"
echo "$Y"
Y='tekst:$X'
echo "$Y"
Y=tekst:$X
echo "$Y"

# Przypadki echa 1 i 3 (a wiec z cudzyslowami oraz bez zadnych znakow) zostaly przetlumaczone na wartosci zmiennych
# za to przypadek 2 (z apostrofami) zostal potraktowany jako literal
# na poczatku bylem zdziwiony, ze w trzecim przypadku nie zostal wyrzucony blad
# ale po chwili stwierdzam, ze ma to sens, w koncu bez znakow bialych caly string moze zostal przypisany do zmiennej

A=Ala
echo $A ma kota, a kot ma ${A}ę

# Polecenie wyświetli słowo "Alaę" ponieważ zadziała tutaj Parameter Substitution/Variable Interpolation
# użycie nawiasów klamrowych będzie konkatenować wartość zmiennej do litery 'ę', zamiast zamieniać ją pod miejsce litery 'a'
