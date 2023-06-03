#!/bin/bash

for arg in "$@"; do
    echo "$arg"
    content="$(cat "$arg")"

    # Normalne wypisanie
    for (( i=0; i<"${#content}"; i++ )); do
        echo -n "${content:$i:1}"
    done
    echo -e "\n"

    # Wypisanie na odwrót
    for (( i="${#content}-1"; i>=0; i-- )); do
        echo -n "${content:$i:1}"
    done
    echo -e "\n\n"
done
