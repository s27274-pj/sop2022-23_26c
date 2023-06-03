#!/bin/bash
for arg in *.c; do
noext="${arg%.*}" 
    cc $arg -o "$noext"
done