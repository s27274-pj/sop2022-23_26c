#!/bin/bash

for file in *.c; do
    filename="${file%.*}"
    cc "$file" -o "$filename"
done
