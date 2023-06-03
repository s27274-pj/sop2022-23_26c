#!/usr/bin/env bash
if [[ $1 =~ ^[A-Z][a-złżćśóąę]*$ ]]; then
  echo "Tekst jest poprawnie zapisanym polskim imieniem."
fi