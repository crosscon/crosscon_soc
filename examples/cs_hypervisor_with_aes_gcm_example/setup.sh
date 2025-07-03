#!/bin/bash

set -x

# Clone Bao.
git clone https://github.com/crosscon/CROSSCON-Hypervisor.git -b feat/crosscon-soc
cd CROSSCON-Hypervisor
patch -p1  < ../../../src/patches/cs_hypervisor.patch
cp ../../../src/crosscon_soc.c src/arch/riscv/
cp ../../../src/crosscon_soc.h src/arch/riscv/inc/
cd ..

# Clone OpenSBI.
git clone https://github.com/riscv-software-src/opensbi.git
cd opensbi
git checkout 322b598
patch -p1  < ../../../src/patches/opensbi.patch
#patch -p1  < ../patches/arch/opensbi.patch
cp ../../../src/crosscon_soc.c platform/beyond/ba51_cs/crosscon_soc.c
cp ../../../src/crosscon_soc.h platform/beyond/ba51_cs/crosscon_soc.h
cp ../../../src/crosscon_soc.c lib/sbi
cp ../../../src/crosscon_soc.h lib/sbi
cd ..
