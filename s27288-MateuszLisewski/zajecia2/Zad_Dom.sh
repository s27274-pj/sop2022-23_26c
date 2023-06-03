#!/bin/bash

filename="$1" # file cw6data.txt
name="$2"

while read -r line; do
    if echo "$line" | grep -q "$name"; then
        echo "$line" | grep -E --color=always "$name|\b$name\b"
    else
        echo "$line"
    fi
done < "$filename"
