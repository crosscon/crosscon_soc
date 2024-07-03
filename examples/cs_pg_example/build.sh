#!/bin/bash

BUILD_DIR=Debug

set -e // Exit if command has failed.

export PATH=$PATH:$RISCV

export ARCH=rv32ima_zicsr_zifencei_zca
export ABI=ilp32

make -C $BUILD_DIR all

echo ""
echo "# Done."
echo ""
