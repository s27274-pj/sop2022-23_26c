#!/bin/bash

#Zadanie 4:

#Wykonaj komendę ls -l w podpowłoce i przypisz ją do zmiennej X.
#Wyświetl zawartość tej zmiennej.
#Spraw, aby nie było różnicy (co najwyżej kolorki) między zwykłym wykonaniem komendy:
#ls -l
#a wypisaniem zawartości zmiennej X. Nie będzie dobrego rezultatu gdy zrobimy tak:
#echo $X
#Zastanów się dlaczego.

X=$(ls -l)
echo "$X"


# W tym zadaniu próbowałem użyć cudzysłowów i apostrofów w każdy możliwy sposób, co dało ciekawe wyniki
# cała trudność polega na otrzymaniu ładnej listy, a nie ściany tekstu bez znaków nowej linii
# rozwiązaniem jest więc otoczenie zmiennej cudzysłowami, wtedy dopiero znaki specjalne są interpretowane tak jak chcemy
# sądzę że przez takie właśnie małe różnice linux nigdy nie będzie popularniejszym systemem operacyjnym,
# rozumiem że ma to swoje zastosowania i wynika to pewnie z działania samej powłoki (?)
# ale szczerze mówiąc nie jest to przyjazne dla nowego użytkownika, nie jest też dosyć intuicyjne aby szybko to zrozumieć

# EDIT
# wszystko przez "Word splitting", okazuje się że powłoka skanuje wyniki Command Expansion [$(ls -l)] i wszystkie znaki <newline> zamienia na delimiter oddzielający poszczególne wyrazy (https://www.gnu.org/software/bash/manual/html_node/Word-Splitting.html)
