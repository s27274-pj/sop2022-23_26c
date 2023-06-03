#!/bin/bash

if [[ $0 =~ .*\.sh ]] ; then
	echo "Poprawne rozszerzenie"
elif [[ $0 != *.sh$ ]] ; then
	echo "Bledne rozszerzenie"
	mv $0 "$0.sh"
	echo "Nowe rozszerzenie to: $0.sh"
fi
