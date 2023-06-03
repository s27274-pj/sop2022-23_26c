#!/bin/bash

fibonacci() {
    if [ $1 -le 1 ]; then
        return $1
    else
        local fib1=0
        local fib2=1
        local i=2
        fibonacci $(( $1 - 1 ))
        fib1=$?
        fibonacci $(( $1 - 2 ))
        fib2=$?
        return $(( fib1 + fib2 ))
    fi
}
