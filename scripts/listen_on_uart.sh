#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Illegal number of arguments."
    echo "Expected: ./listen_on_uart.sh /dev/ttyUSBx"
    exit 1
fi

#tio -b 115200 -e --map INLCRNL,ONLCRNL $1
tio -b 9600 --map INLCRNL,ONLCRNL $1
#screen $1 115200
#screen $1 9600
