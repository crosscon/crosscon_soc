#!/bin/bash

# Fail the entire script on error.
set -e

export CROSS_COMPILE=$RISCV/riscv32-unknown-elf-

export ARCH_SUB=riscv32

PLATFORM_RISCV_ISA=rv32imafc_zicsr_zifencei_zca
PLATFORM_RISCV_ABI=ilp32f

echo ""
echo "#"
echo "# Building 1st guest ..."
echo "#"
echo ""

make -C baremetal-guest PLATFORM=crosscon_soc ARCH_SUB=$ARCH_SUB MEM_BASE=0x60000 riscv_march=$PLATFORM_RISCV_ISA riscv_mabi=$PLATFORM_RISCV_ABI

echo ""
echo "#"
echo "# Building 2nd guest ..."
echo "#"
echo ""

make -C baremetal-guest2 PLATFORM=crosscon_soc ARCH_SUB=$ARCH_SUB MEM_BASE=0x70000 riscv_march=$PLATFORM_RISCV_ISA riscv_mabi=$PLATFORM_RISCV_ABI

echo ""
echo "#"
echo "# Building Bao ..."
echo "#"
echo ""

export CONFIG=cs_two_guest_vms
export BAO_PLATFORM=crosscon_soc

make -C CROSSCON-Hypervisor PLATFORM=$BAO_PLATFORM ARCH_SUB=$ARCH_SUB CONFIG_REPO=$(realpath configs) CONFIG=$CONFIG SDEES="sdSGX sdTZ" riscv_march=$PLATFORM_RISCV_ISA riscv_mabi=$PLATFORM_RISCV_ABI

echo ""
echo "#"
echo "# Building opensbi ..."
echo "#"
echo ""

PLATFORM_RISCV_ISA=rv32imac_zicsr_zifencei_zca
PLATFORM_RISCV_ABI=ilp32

OPENSBI_PLATFORM=beyond/ba51_cs

make -C opensbi V=1 DEBUG=1 PLATFORM=${OPENSBI_PLATFORM} FW_PAYLOAD_PATH=$(realpath CROSSCON-Hypervisor/bin/$BAO_PLATFORM/$CONFIG/crossconhyp.bin) -j12 PLATFORM_RISCV_ISA=$PLATFORM_RISCV_ISA PLATFORM_RISCV_ABI=$PLATFORM_RISCV_ABI 

${CROSS_COMPILE}objdump -S opensbi/build/platform/${OPENSBI_PLATFORM}/firmware/fw_payload.elf > opensbi/build/platform/${OPENSBI_PLATFORM}/firmware/fw_payload.elf.asm

echo ""
echo "#"
echo "# Done."
echo "#"
echo ""

