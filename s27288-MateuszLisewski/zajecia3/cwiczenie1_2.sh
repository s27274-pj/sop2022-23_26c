#!/bin/bash

File="config.cfg"
if [ -f $File ]; then
	./$File
elif [[ -n "$1" ]]; then
	./$1
else
	echo "ERROR!"
fi
