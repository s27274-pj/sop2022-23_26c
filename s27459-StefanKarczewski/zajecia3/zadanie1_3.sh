#!/bin/bash

# Sprawdzam, czy nazwa pliku kończy się ".sh" za pomocą regexpa
if [[ ! "$0" =~ \.sh$ ]]; then
    echo "This file's extension is not .sh"
    mv "$0" "${0}.sh"
fi

