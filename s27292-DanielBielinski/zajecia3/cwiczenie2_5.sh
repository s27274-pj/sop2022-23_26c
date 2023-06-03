#!/bin/bash
pliki=("$@")
for plik in ${pliki[@]}; do
    echo "$plik w normalnej kolejnosci"
    cat $plik
    echo "$plik w odwrotnej kolejnosci"
    tac $plik
done