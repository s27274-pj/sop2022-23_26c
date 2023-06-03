#!/bin/bash

if [ $# -gt 1 ]; then
  echo "Pierwszy parametr: $1"
else
  echo "Nie podano żadnych parametrów."
fi
