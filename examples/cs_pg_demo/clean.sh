#!/bin/bash

BUILD_DIR=Debug

set -e // Exit if command has failed.

make -C $BUILD_DIR clean

echo ""
echo "# Done."
echo ""
