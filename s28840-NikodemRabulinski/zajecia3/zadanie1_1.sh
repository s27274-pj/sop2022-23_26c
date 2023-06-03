#!/usr/bin/env bash

# Napisz skrypt, który sprawdzi, czy podano więcej niż jeden parametr.
# Jeśli tak, to niech wyświetli pierwszy parametr. Jeśli nie, to niech wyświetli komunikat, że nie podano parametrów.

# Najpierw wczytuję ilość argumentów podanych do skryptu
LEN=${#@}

# A później sprawdzam czy jest ona większa od 0
if [[ "$LEN" > 0 ]]; then
  echo "$1"
else
  echo Nie podano parametrów
fi

# To zadanie można jednak zinterpretować w inny sposób - uznając, że argument zerowy skryptu zalicza się do przekazanych argumentów.
# Z dokumentacji basha możemy wyczytać:
#     @      Expands to the positional parameters, starting from one.  When the expansion occurs within double quotes, each
#            parameter expands to a separate word.  That is, "$@" is equivalent to "$1" "$2" ...  If the double-quoted
#            expansion occurs within a word, the expansion of the first parameter is joined with the beginning part of the
#            original word, and the expansion of the last parameter is joined with the last part of the original word.
#            When there are no positional parameters, "$@" and $@ expand to nothing (i.e., they are removed).
# Z czego dla nas najważniejsze jest to, że argument zerowy nie jest wliczany gdy używamy @.
# Jeśli jednak chcemy uznać, że arg0 jest pierwszym argumentem skryptu możemy pozbyć się instrukcji warunkowej i po prostu drukować $0,
# gdyż argument 0 zawsze[1] jest dostępny.
#
# [1]: Teoretycznie nie zawsze, gdyż na upartego możemy wywołać exec* i dać pusty string jako argv[0] albo nawet NULL, ale nawet wtedy 
# możemy zobaczyć w źródle linuxa, że argument zerowy *zawsze* jest dostępny, nawet jeśli chcemy żeby go nie było,
# to i tak co najmniej będzie to pusty string: https://github.com/torvalds/linux/blob/c337b23f32c87320dffd389e4f0f793db35f0a9b/fs/exec.c#L1947-L1952
