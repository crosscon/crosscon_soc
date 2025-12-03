#!/bin/bash

set -x

# Clone Bao.
git clone https://github.com/crosscon/CROSSCON-Hypervisor.git -b feat/crosscon-soc
cd CROSSCON-Hypervisor
git checkout 8f2e2a4ef6992ebb7a825e2e000b93b94b506cea
patch -p1  < ../../../src/patches/cs_hypervisor.patch
cp ../../../src/crosscon_soc.c src/arch/riscv/
cp ../../../src/crosscon_soc.h src/arch/riscv/inc/
# We adjust QMEM's PG because of the different layout of software in memory.
cp ../src/cpu.c src/arch/riscv/cpu.c
# We adjust the slice given to each VM on a core.
cp ../src/sched.c src/core/sched.c
cd ..

# Clone OpenSBI.
git clone https://github.com/riscv-software-src/opensbi.git
cd opensbi
git checkout 322b598
patch -p1  < ../../../src/patches/opensbi.patch
cp ../../../src/crosscon_soc.c platform/beyond/ba51_cs/crosscon_soc.c
cp ../../../src/crosscon_soc.h platform/beyond/ba51_cs/crosscon_soc.h
cp ../../../src/crosscon_soc.c lib/sbi
cp ../../../src/crosscon_soc.h lib/sbi
# We need to adjust UART speed.
cp ../src/platform.c platform/beyond/ba51_cs/platform.c
cd ..

# Setup guests.

cp ../../src/crosscon_soc.c baremetal-guest2/src/platform/crosscon_soc/
cp ../../src/crosscon_soc.h baremetal-guest2/src/platform/crosscon_soc/inc/

cp ../../src/crosscon_soc.c baremetal-guest/src/platform/crosscon_soc/
cp ../../src/crosscon_soc.h baremetal-guest/src/platform/crosscon_soc/inc/
