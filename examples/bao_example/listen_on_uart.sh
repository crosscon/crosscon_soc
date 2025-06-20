#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Illegal number of arguments."
    echo "Expected: ./listen_on_uart.sh /dev/ttyUSBx"
    exit 1
fi

tio -e --map INLCRNL,ONLCRNL $1
