# Test: CROSSCON Hypervisor with two guest VM's where each is using its own UART

Here you can find a test that runs two guest VMs on top of CROSSCON Hypervisor where each VM prints to a different UART.

Note that you need to listen on two different UART's to see the output; one on Arty-a7's JB and JD Pmod port. 

## Prerequisites

Follow the instruction in [README.md](../../../README.md) to setup the cross-compilation toolchain, connect the Arty-A7 board and upload the CROSSCON SoC bitstream.

Note that the path to the RISC-V cross-compilation toolchain should be available through `RISCV` variable as described in Setup the RISC-V toolchain section of [README.md](../../../README.md).

## Setup and compile

Run
```
./setup.sh
```
and then
```
./build.sh 
```
to setup and build the source files.

