#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Illegal number of arguments."
    echo "Expected: ./upload.sh <path_to_bitstream>.bit"
    exit 1
fi

openocd -f digilent_arty.cfg -c "init; pld load 0 "$1"; exit"
