#!/bin/bash

for file in *.c; do
    cc "$file" -o "${file%.*}"
done
