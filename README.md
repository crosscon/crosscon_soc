# CROSSCON SoC

Here you can find the initial version of the _CROSSCON SoC_: a costume system-on-chip (SoC) developed as part of the [CROSSCON project](https://crosscon.eu/). The repository contains on overview of the CROSSCON SoC, its bitstream and instructions on how it can be used with the Arty-A7 100T board. For detailed description of the CROSSCON SoC, please refer to the deliverable 4.1: ROSSCON Extensions to Domain Specific Hardware Architectures Documentation — Draft. This repository is part of the deliverable 4.2: CROSSCON Extension Primitives to Domain Specific Hardware Architectures — Initial Version. 

## Overview

**CROSSCON SoC** is an SoC design, developed as part of the [CROSSCON project](https://crosscon.eu/), that provides a secure RISC-V execution environment for mixed criticality IoT devices that require strong security guarantees, flexibility, small code size and low power consumption. The guarantees that the CROSSCON SoC can provide are strong software isolation (through virtualization-based trusted execution environments (TEEs)) with the ability to share HW modules connected to the SoC interconnect between TEEs without compromising isolation guarantees.

<p align="center">
    <img src="./imgs/soc_initial_architecture.drawio.png" width=70% height=70%>
</p>
<p align="center">Figure 1: The current architecture of the CROSSCON SoC<p align="center">

Figure 1 shows a high level architecture of the current version of the CROSSCON SoC. The CROSSCON SoC is build around the [Beyond Semiconductor's](https://www.beyondsemi.com/) [BA51](https://www.cast-inc.com/processors/risc-v/ba51) RISC-V core and includes all the necessary infrastructure that one needs to develop embedded applications on top of a SoC (e.g. JTAG support and UART).

The extended BA51 core, called **BA51-H**, is highly configurable, low-power, deeply embedded 32-bit RISC-V process with efficient virtualization support without virtual memory. BA51-H allows the [CROSSCON Hypervisor](https://github.com/crosscon/CROSSCON-Hypervisor) to establish  hardware-enforced, software-defined, virtualization-based TEEs that provide isolated execution environments for the applications / RTOSs running on top the hypervisor. The BA51-H core supports RISV-V 32-bit ISA with integer instruction set (I), integer multiplication and division (M), atomic instructions (A), single-precision floating-point instructions (F), compressed instructions (C and Zc), high-precision base counters and timers (Zicntr) extensions and Hypervisor-extension (H) without virtual memory support, a unified (2-stage) S-mode Physical Memory Protection (SPMP), S-mod timers (Sstc), and Advance Platform-Level Interrupt Controller (APLIC) extension for efficient virtualization. To the best of our knowledge, the extended BA51 is the smallest silicon area RISC-V core with hardware virtualization support featuring unified SPMP, Sstc, and APLIC. 

The BA51-H contains the fist implementation of the unified (2-stage) S-mode Physical Memory Protection (SPMP) unit which is one of the possible SPMP candidates for the standardization as part of the [RISC-V SPMP standardization effort](https://github.com/riscv/riscv-spmp?tab=readme-ov-file). We have extended Spike simulator, considered as the golden-model of the RISC-V specification, with the unified (2-stage) SPMP extensions witch servers a reference implementation of the unified SPMP model and allows us to obtain a reference execution environment for the BA51-H core. The extended Spike can be configured to simulate rv32imafch_spmp_sstc_zc_zicntr ISA and is available as a [separate repository](https://github.com/crosscon/riscv-isa-sim).

Furthermore, the CROSSCON SoC contains the first prototype implementation of **Perimeter guard (PG)**: a mechanism that allows a system to share HW modules across different VMs while preserving the isolation between them. A PG is a HW module that, when placed between the SoC interconnect and the HW module that we want to share (for example, cryptographic accelerator), provides a better control of which VMs and bus masters can use the module and allows the HW module to be "reset" before giving access to the module to a new VM / master. The PG can support several modes of operation, where the current prototype only supports time-sharing with reset-mode with lock-release arbitration mode. In the current version of the CROSSCON SoC, as shown by the Figure 1, we use PG to control access to SRAM so that it can be shared between different VMs without compromising isolation between them.

A more detailed description of CROSSCON SoC, BA51-H and Perimeter guard can be found in deliverable 4.1 of the [CROSSCON project](https://crosscon.eu/).

## How to upload the bitstream
	                        
The CROSSCON SoC bitstream can be uploaded to the Arty-A7 100T board aither through Vivado Lab GUI or via terminal using Tool Command Language (TCL). Here we cover the letter and describe how to program the Arty-A7 over terminal (without the GUI). For how to program Arity-A7 over GUI see [the reference manual](https://digilent.com/reference/programmable-logic/arty-a7/reference-manual).

### Prerequisite
        
We assume that you are following the instructions on a PC with a working setup of Ubuntu or Debian OS.

In order to upload the CROSSCON SoC bitstream to the FPGA, you need to install Vivado Lab that is available [here](https://www.xilinx.com/support/download.html).

After installing Vivado Lab, make sure that `vivado_lab` command is available in your terminal.

### Uploading the bitstream

Plug in the Arty-A7 board to your PC using an USB-to-micro-USB cable via USB-JTAG port and then execute the following commands. See [the Arty-A7 reference manual](https://digilent.com/reference/programmable-logic/arty-a7/reference-manual) for the overview of the Arty-A7 board.

Note we assume that only one FPGA board is plugged into the PC, otherwise `bits/program_fpga.tcl` might not program the right board.

```bash
# Check out the repostory.
$git clone https://github.com/crosscon/crosscon_soc.git

$cd crosscon_soc
 
# Run vivado_lab with the program_fpga.ctl script and crosscon_soc_a7 bitstream.
$vivado_lab -mode tcl -source bits/program_fpga.tcl -tclargs bits/crosscon_soc_a7_v0.1.bit
```

CROSSCON SoC bistream is available in `bits` folder.

When Arty-A7 100T was configured successfully:
- the last line of the previous command should be similar to `INFO: [Labtools 27-3164] End of startup status: HIGH` and
- the "DONE" LED of the Arty-A7 board should be illuminated green.

Note, if the last line of the previous command is similar to `ERROR: [Labtools 27-3165] End of startup status: LOW`, the board was not programmed correctly.

## How to run a Hello Bare Metal project example

Please run this example first just to be sure that everything is working as expected.

A program can be run on the CROSSCON SoC by using:
- JTAG compatible debug key, as for example Beyond Semuconductor's [Beyond Debug Key](https://www.beyondsemi.com/beyond-debug-key/), and
- [BeyondStudio](https://www.beyondsemi.com/86/beyondstudio-integrated-development-environment/) IDE.

In order to obtain a copy of BeyondStudio, please create an account on Beyond Semiconductor's [webpage](https://www.beyondsemi.com/bstudio/) and request access to BeyondStudio. Once the access is granted to you, you can download BeyondStudio and BeyondStudio Manual.

We assume that you are following the instructions on a PC with a working setup of Ubuntu or Debian OS.

First, connect Beyond Debug Key with to the Arity-A7's JD port, as shown by the picture below, and connect the Beyond Debug Key to your PC via USB-to-micro-USB cable.

<p align="center">
    <img src="./imgs/arty_a7_debuger_setup.jpeg" width=50% height=50%>
</p>

Second, follow the instructions in the BeyondStudio Manual on how to setup BeyondStudion and setup your fist Hello Bare Metal project. When you create a new project and you need to select the 'Initial RISC-V (BA5x) target platform configuration', select `CPU: Beyond BA51`, `Endianness : little`, `Base ISA: RV32I (32 bits, 32 registers)`, and the following extensions `Zicsr`, `Zicntr`, `Zifencei`, `M`, `A` and `Zca`. All other configuration options should stay the same as provided by the project creation wizard.

## Running a Perimeter guard example

In this example, we demonstrate how the PG can be used in time-sharing with reset and lock-release arbitration mode to protect the SRAM module. You can find the example in `examples/cs_pg_example/src/cs_pg_example.c` file.

As part of the example, the program tries to access the SRAM module with different DIDs and demonstrate that an interrupt is raised if a domain that did not lock the SRAM tries to access it. Furthermore, the program shows that the SRAM is reset after the SRAM is released by the program. This is a basic example where the program is allowed to select its own DID. Later on, we plan to provide an example that demonstrates how PG can be used in the context of CROSSCON Hypervisor, where the CROSSCON Hypervisor provides the DID of the VM that is currently running.

In order to run the program on Arty-A7 board, you need to first connect the Arity-A7 and the Beyond Debug Key, as described in 'How to run a Hello Bare Metal project example' section, and upload the `crosscon_soc_with_pg_a7.bit` bitstream to the Arty-A7 board.

Second, import the `examples/cs_pg_example` repository into BeyondStudio, as described in chapter 8.1. 'Importing existing BeyondStudio projects' in BeyondStudio Manual and run the example.

If program was executed successfully you should see an output similar to the following:
```
CROSSCON SoC: Running basic PG test ...

Trying to read and write to SRAM ...

Trying to access SRAM with the wrong DID ...

Trying to read and write to SRAM with a different HDID ...

Test completed successfully.

```

## Running a CROSSCON Hypervisor example

...

## Licence

See LICENCE file.

## Acknowledgments

The work presented in this repository is part of the [CROSSCON project](https://crosscon.eu/) that received funding from the European Union’s Horizon Europe research and innovation programme under grant agreement No 101070537.

<p align="center">
    <img src="https://crosscon.eu/sites/crosscon/themes/crosscon/images/eu.svg" width=10% height=10%>
</p>

<p align="center">
    <img src="https://crosscon.eu/sites/crosscon/files/public/styles/large_1080_/public/content-images/media/2023/crosscon_logo.png?itok=LUH3ejzO" width=25% height=25%>
</p>

