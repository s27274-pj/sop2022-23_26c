#!/bin/bash

#zadanie domowe:

zmienionyTekst=$(sed s/Konrad/\\\\\\e[31mKonrad\\\\\e[39m/g $1)		#jako drugi parametr sed podaje ścieżke do pliku na którym wykona on operacje podmiany
echo -e "$zmienionyTekst"	#używam cudzysłowów aby uniknąć word splittingu, oraz parametru -e aby echo mogło interpretować znaki modyfikacji (/)

#Bardzo fajna zdolność i właściwie szybka w stworzeniu
#Pod warunkiem oczywiście że zna się jaki escape sequence określa kolor czerwony
