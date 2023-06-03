#!/bin/bash

if [ $# > 0 ]; then
    echo "$1"
else
    echo "Nie podano żadnych argumentów"
    exit 1
fi
