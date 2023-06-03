#!/bin/sh

if [[ -f "config.cfg" ]]; then
    ./config.cfg
elif [[ $# > 0 ]]; then
    ./$1
else
    echo "Błąd";
fi
