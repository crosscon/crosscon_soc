#!/bin/bash

read -p "Do you want to clear the entire setup? [Y/n] " user_input

if [[ "$user_input" == "Y" ]]; then

    set -x

    rm -f maremetal-guest/src/platform/crosscon_soc/crosscon_soc.c
    rm -f maremetal-guest/src/platform/crosscon_soc/inc/crosscon_soc.h
    
    rm -f maremetal-guest2/src/platform/crosscon_soc/crosscon_soc.c
    rm -f maremetal-guest2/src/platform/crosscon_soc/inc/crosscon_soc.h
    
    rm -rf opensbi/ CROSSCON-Hypervisor/

else
    echo "Operation canceled."
fi


