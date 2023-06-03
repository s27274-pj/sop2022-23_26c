#!/bin/bash

name=$1

if [[ $name =~ [aAęĘ]$ ]]; then
  echo "$name ma kota, a kot ma ${name%?}ę"
else
  echo "$name ma kota, a kot ma ${name}a"
fi
