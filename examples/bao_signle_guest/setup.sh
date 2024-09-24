#!/bin/bash

# Clone Bao.
git clone https://github.com/josecm/bao-hypervisor.git --recursive --branch exp/spmp
cd bao-hypervisor
git apply ../patches/bao1.patch
git apply ../patches/bao2.patch
cd ..

# Clone OpenSBI.
git clone https://github.com/riscv-software-src/opensbi.git && git -C opensbi checkout 322b598
cd opensbi
git apply ../patches/opensbi1.patch
git apply ../patches/opensbi2.patch
cd ..

