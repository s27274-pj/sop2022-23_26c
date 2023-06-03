#!/bin/bash

function colorthetext {
    tekst=$1
    kolor=$2
    echo -e "\e[${kolor}m$tekst\e[0m"
}

colorthetext "Siema" 31