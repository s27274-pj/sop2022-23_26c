#!/bin/bash

if [[ "$(find -type f | wc -l)" -gt 5 ]]; then
    echo "W katalogu jest więcej niż 5 plików"
fi
