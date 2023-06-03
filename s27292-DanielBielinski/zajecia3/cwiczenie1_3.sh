#!/bin/bash
name=$0
if [[ $0 != *.sh ]]
then
echo $0
text=$(sed -i 's/\.[^.]+$/.sh/' $0)
echo "$text"
else
	echo "jest git"
fi