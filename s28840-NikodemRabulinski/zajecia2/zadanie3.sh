#!/usr/bin/env bash

# Zobacz co przechowują zmienne i opisz jak rozumiesz uzyskany wynik.
# Do czego on jest i kiedy może się wg Ciebie przydać:
# PATH
# RANDOM
# PWD
# PS1
# USER
# HOSTNAME
# OSTYPE

echo PATH: "$PATH"
echo RANDOM: "$RANDOM"
echo PWD: "$PWD"
echo PS1: "$PS1"
echo USER: "$USER"
echo HOSTNAME: "$HOSTNAME"
echo OSTYPE: "$OSTYPE"

# PATH - zawiera ścieżki, które będą przeszukiwane
# jeśli wykonywane polecenie nie jest ścieżką względną lub poleceniem wbudowanym
#
# RANDOM - zwraca losowy numer za każdym razem kiedy jest odczytana.
# Jest to wbudowana zmienna bash-a,
# więc próba użycia jej w innej powłoce lub odczytanie jej przez polecenie jak printenv nie zadziała!
#
# PWD - Folder w którym się znajdujemy
#
# PS1 - Definiuje znak zachęty i co jest przed nim napisane
#
# USER - Aktualnie zalogowany użytkownik / Użytkownik wykonujący polecenie
#
# HOSTNAME - Nazwa komputera w sieci (Wyjaśnione dokładniej w opisie instalacji Debian-a)
#
# OSTYPE - Typ systemu, na którym jest wykonywany bash
# To również jest zmienna wbudowana w bash więc może nie być dostępna w innych powłokach,
# lub inne powłoki mogą mieć nieco inną wartość dla tego samego typu systemu.
