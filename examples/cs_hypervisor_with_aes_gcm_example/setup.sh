#!/bin/bash

set -x

# Clone Bao.
git clone https://github.com/crosscon/CROSSCON-Hypervisor.git -b feat/crosscon-soc
cd CROSSCON-Hypervisor
patch -p1  < ../patches/cs_hypervisor.patch
#cp ../patches/src/CROSSCON-Hypervisor/boot.S src/arch/riscv/spmp/boot.S
#cp ../patches/src/CROSSCON-Hypervisor/platform.mk src/platform/crosscon_soc/platform.mk
cd ..

# Clone OpenSBI.
git clone https://github.com/riscv-software-src/opensbi.git
cd opensbi
git checkout 322b598
patch -p1  < ../patches/opensbi.patch
cd ..
