#!/bin/bash

read -p "Do you want to clear the entire setup? [Y/n] " user_input

if [[ "$user_input" == "Y" ]]; then

    set -x

    rm src/crosscon_soc.c
    rm src/crosscon_soc.h
    
else
    echo "Operation canceled."
fi


