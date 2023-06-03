#!/bin/bash

Filecount=$(find . -maxdepth 1 -type f | wc -l)
if [ "$Filecount" -gt 5 ] ; then
	echo "poprawne"
else 
	echo "blad"
fi
