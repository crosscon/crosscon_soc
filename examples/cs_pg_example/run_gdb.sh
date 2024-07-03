#!/bin/bash

set -o xtrace

BUILD_DIR=Debug

$RISCV/riscv32-unknown-elf-gdb $BUILD_DIR/cs_pg_example.elf \
        -ex 'target remote localhost:3333' \
        -ex 'load' \
        -ex 'continue'
