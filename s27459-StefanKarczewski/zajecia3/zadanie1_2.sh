#!/bin/bash

if [ -e "config.cfg" ]; then
    ./config.cfg
elif [ $# == 1 ]; then
    exec $1
else
    echo "'config.cfg' nie istnieje lub nie podano żadnych argumentów"
    exit 1
fi
