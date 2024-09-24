#!/bin/bash

# Fail the entire script on error.
set -e

export CROSS_COMPILE=$RISCV/riscv32-unknown-elf-

export ARCH_SUB=riscv32

PLATFORM_RISCV_ISA=rv32imafc_zicsr_zifencei_zca_sstc
PLATFORM_RISCV_ABI=ilp32f

echo ""
echo "#"
echo "# Building guest ..."
echo "#"
echo ""

rm -fr bao-baremetal-guest/build
make -C bao-baremetal-guest PLATFORM=crosscon_soc ARCH_SUB=$ARCH_SUB MEM_BASE=0x70000 riscv_march=$PLATFORM_RISCV_ISA riscv_mabi=$PLATFORM_RISCV_ABI

echo ""
echo "#"
echo "# Building Bao ..."
echo "#"
echo ""

export CONFIG=spike-spmp-single
export BAO_PLATFORM=crosscon_soc

rm -fr bao-hypervisor/build
rm -fr bao-hypervisor/bin
make -C bao-hypervisor PLATFORM=$BAO_PLATFORM ARCH_SUB=$ARCH_SUB CONFIG_REPO=$(realpath configs) CONFIG=$CONFIG riscv_march=$PLATFORM_RISCV_ISA riscv_mabi=$PLATFORM_RISCV_ABI

echo ""
echo "#"
echo "# Building opensbi ..."
echo "#"
echo ""

PLATFORM_RISCV_ISA=rv32imac_zicsr_zifencei_zca
PLATFORM_RISCV_ABI=ilp32

make -C opensbi V=1 DEBUG=1 PLATFORM=beyond/ba51_cs FW_PAYLOAD_PATH=$(realpath bao-hypervisor/bin/$BAO_PLATFORM/$CONFIG/bao.bin) -j12 PLATFORM_RISCV_ISA=$PLATFORM_RISCV_ISA PLATFORM_RISCV_ABI=$PLATFORM_RISCV_ABI 

${CROSS_COMPILE}objdump -S opensbi/build/platform/beyond/ba51_cs/firmware/fw_payload.elf > opensbi/build/platform/beyond/ba51_cs/firmware/fw_payload.elf.asm

echo ""
echo "#"
echo "# Done."
echo "#"
echo ""

