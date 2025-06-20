#!/bin/bash

# Clone Bao.
git clone https://github.com/josecm/bao-hypervisor.git --recursive --branch exp/spmp
cd bao-hypervisor
patch -p1 < ../patches/bao.patch
cd ..

# Clone OpenSBI.
git clone https://github.com/riscv-software-src/opensbi.git && git -C opensbi checkout 322b598
cd opensbi
patch -p1  < ../patches/opensbi.patch
cd ..
