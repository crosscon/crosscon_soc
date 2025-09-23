#!/bin/bash

set -o xtrace

$RISCV/riscv32-unknown-elf-gdb  opensbi/build/platform/beyond/ba51_cs/firmware/fw_payload.elf \
        -ex 'target remote localhost:3333' \
        -ex 'load' \
        -ex 'add-symbol-file CROSSCON-Hypervisor/bin/crosscon_soc/cs_two_guest_vms/crossconhyp.elf' \
        -ex 'add-symbol-file baremetal-guest/build/crosscon_soc/baremetal.elf' \
        -ex 'add-symbol-file baremetal-guest2/build/crosscon_soc/baremetal.elf'
        #-ex 'continue'
