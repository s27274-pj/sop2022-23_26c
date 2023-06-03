#!/bin/sh

# wczytanie listy plików
files=("$@")

# wypisanie zawartości plików w kolejności od początku do końca
for ((i=0; i<${#files[@]}; i++))
do
  echo "Zawartość pliku ${files[i]} w kolejności od początku do końca:"
  printf '%s\n' "$(cat "${files[i]}")"
done

# wypisanie zawartości plików w kolejności od końca do początku
for (( i=${#files[@]}-1; i>=0; i-- ))
do
    echo "Zawartość pliku ${files[i]} w kolejności od końca do początku:"
    length=$(wc -c < "${files[i]}")
    for (( j=length-1; j>=0; j-- ))
    do
        char=$(dd bs=1 count=1 skip=$j if="${files[i]}" 2>/dev/null)
        # 2>/dev/null to przekierowanie ewentualnych błędów do dev/null
        # sprawi to, że nie będą wyświetlane żadne komunikaty o błędach
        # dd - Wczytywanie pojedynczego bajtu z pliku
        
        echo -n "$char"
    done
    echo ""
done
