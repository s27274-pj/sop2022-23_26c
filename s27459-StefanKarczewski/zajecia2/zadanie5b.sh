#!/bin/bash

if [ $# == 0 ]; then
    echo "Nie podano żadnych argumentów"
    exit 1
fi

arg="$*"
arg_len=${#arg}

echo "Pierwszy znak: '${arg:0:1}'"
echo "Ostatni znak:  '${arg:$arg_len-1}'"

out=`echo $arg | sed 's/SOP/\\\\e[32mSOP\\\\e[0m/g'`
echo -e "$out"
