#!/bin/bash

fib() {
    local n=$1
    if [[ $n -lt 2 ]]; then
        echo $n
        return
    fi
    local a=$(fib $((n-1)))
    local b=$(fib $((n-2)))
    echo $((a + b))
    return
}

result=$(fib 10)
echo $result