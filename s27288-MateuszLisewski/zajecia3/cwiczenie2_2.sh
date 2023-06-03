#!/bin/bash

args=("$@")

for arg in "${args[@]}"
do
    echo "\"$arg\""
done
