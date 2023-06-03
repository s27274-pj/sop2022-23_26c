#!/bin/bash

function fib() {
    local n="$1"

    if [[ $n -lt 2 ]]; then
        return $n
    else
        fib $((n - 2))
        local a=$?
        fib $((n - 1))
        local b=$?

        return $((a + b))
    fi
}

# Wywołuję funkcję z argumentami tego skryptu
fib "$1"
# Wartość zwrócona z funkcji jest w $?
echo "$?"
