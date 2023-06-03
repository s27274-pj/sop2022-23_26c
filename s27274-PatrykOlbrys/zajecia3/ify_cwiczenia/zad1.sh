#!/bin/sh

if [[ $# > 1 ]]; then
    echo $1
else
	echo "Nie podano żadnych argumentów"
    exit 1
fi
