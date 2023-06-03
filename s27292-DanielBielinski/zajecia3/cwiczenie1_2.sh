#!/bin/bash
if [[ -a $PWD/config.cfg ]]
then
	bash config.cfg
elif [[ $1 ]]
then
	bash $1
else
	echo "blad"
fi