#!/bin/bash

function print_color() {
    text="$1"
    color_name="$2"

    color_names=(black red green yellow blue magenta cyan white)
    color_codes=(30 31 32 33 34 35 36 37)

    # Szukam indeksu koloru po jego nazwie
    index=-1
    # !tablica[@] zwraca jej długość
    for i in ${!color_names[@]}; do
        if [[ "${color_names[$i]}" == "${color_name}" ]]; then
            index=$i
            break
        fi
    done

    # Sprawdzam na wszelki wypadek, czy podano dobry kolor
    if [[ $index == -1 ]]; then
        echo "Invalid color: $color_name"
        exit 1
    fi

    color_code="${color_codes[$index]}"
    echo -e "\033[${color_code}m${text}\033[0m"
}

# Wywołuję funkcję z argumentami tego skryptu
print_color "$1" "$2"
