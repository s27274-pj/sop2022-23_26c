#!/bin/bash
pliki=$(ls)
count=$(echo $pliki | wc -w)
if [ $count > 5 ]
then
    echo "Jest tu wiecej niz 5 plikow"
fi