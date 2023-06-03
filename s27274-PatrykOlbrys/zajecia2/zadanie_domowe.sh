#!/bin/sh

if [ $# == 0 ]; then
    echo "Podaj argument"
    exit 1
fi

arg="$1"
output=`sed 's/Patryk/\\\\e[31mPatryk\\\\e[0m/g' $arg`
echo -e "$output"
