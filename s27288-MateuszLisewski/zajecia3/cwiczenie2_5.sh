#!/bin/bash

# pobierz listę plików z wiersza poleceń
files=("$@")

for file in "${files[@]}"; do
	echo "==== $file (od początku do końca) ===="

	input=$(<"$file")

	echo "$input"

	#Seperator
	echo -e "\n--------------------------------------\n"

	echo "==== $file (od końca do początku) ===="

	size=$(stat -c%s "$file")

	for (( i=size-1; i>=0; i-- )); do

		c="${input:$i:1}"

		echo -n "$c"
	done

	echo -e "\n======================================\n"
done
