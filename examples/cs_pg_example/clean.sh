#!/bin/bash

BUILD_DIR=Debug

set -e // Exit if command has failed.

export PATH=$PATH:$RISCV

make -C $BUILD_DIR clean

echo ""
echo "# Done."
echo ""
