#!/bin/bash

if   [[ "$1" =~ ^[A-Z][a-z]+$ ]]; then
    echo imię
elif [[ "$1" =~ ^[0-9]{2}-[0-9]{3}$ ]]; then
    echo pocztowy
elif [[ "$1" =~ ^[a-z+]+@[a-z]+\.[a-z]+$ ]]; then
    echo email
fi
