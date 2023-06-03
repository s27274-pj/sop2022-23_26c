#!/bin/sh

if [ $# == 0 ]; then
    echo "nie podano żadnych argumentów"
    exit 1
fi

file="$1"
out=`sed 's/Stefan/\\\\e[31mStefan\\\\e[0m/g' $file`
echo -e "$out"
