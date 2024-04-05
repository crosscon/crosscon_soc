# CROSSCON SoC

In this repository you can find the initial version of _CROSSCON SoC_: a SoC developed as part of [CROSSCON project](https://crosscon.eu/), which is part of the deliverable 4.2 (CROSSCON Extension Primitives to Domain Specific Hardware Architectures — Initial Version). It contains on overview of the CROSSCON SoC, its bitstream and instructions on how it can be used with the Arty-A7 100T board. For detailed description of the SoC, please refer to the deliverable 4.1 (ROSSCON Extensions to Domain Specific Hardware Architectures Documentation — Draft) of the CROSSCON project.

## Overview

The _CROSSCON SoC_ is a (soft) system on chip (SoC) design, developed as part of the [CROSSCON project](https://crosscon.eu/), that provides secure RISC-V execution environment for mixed criticality IoT devices that require strong security guarantees, flexibility, small code size and low power consumption. The guarantees that the CROSSCON SoC can provide are strong software isolation (hardware-enforced, software-defined virtualization-based TEEs) with the ability to share HW modules connected to SoC interconnect between TEEs without compromising isolation guarantees.

<p align="center">
    <img src="./imgs/soc_initial_architecture.drawio.png" width=50% height=50%>
</p>
<p align="center">Figure 1: The initial architecture of the CROSSCON SoC<p align="center">

Figure 1 shows a high level architecture of the current version of the CROSSCON SoC. The CROSSCON SoC is build around an extended version of [Beyond Semiconductor's](https://www.beyondsemi.com/) [BA51](https://www.cast-inc.com/processors/risc-v/ba51) RISC-V core and includes all the necessary infrastructure that one needs to develop embedded applications on top of a SoC (e.g. JTAG support and UART). The _extended BA51 core_, also called _BA51-H_, is a highly configurable, low-power, deeply embedded 32-bit RISC-V processor IP core extended with unified (2-stage) SPMP, Sstc, and APLIC extensions that allow the CROSSCON hypervisor [?] to establish  hardware-enforced, software-defined virtualization-based trusted execution environments (TEEs), called _Trusted VMs_ in the context of CROSSCON hypervisor; that provide strong hardware-enforced isolation between software running in different VMs.

The BA51-H core supports RISV-V 32-bit ISA with integer instruction set (I), integer multiplication and division (M), atomic instructions (A), single-precision floating-point instructions (F), compressed instructions (C and Zc), hypervisor-extension (H) without virtual memory support, a unified (two stage) memory protection unit (PMP, SPMP and vSPMP), high-precision base counters and timers (Zicntr), S-mod timers (Sstc) and advance platform-level interrupt controller (APLIC). BA51-H supports rv32imafch_spmp_sstc_zc_zicntr ISA. To the best of our knowledge, the extended BA51 is the smallest silicon area RISC-V core with hardware virtualization support featuring unified SPMP, Sstc, and APLIC. 

The BA51-H contains the fist implementation of the unified (2-stage) S-mode Physical Memory Protection (SPMP) unit which is one of the possible SPMP candidates for the standardization as part of the [RISC-V SPMP standardization effort](https://github.com/riscv/riscv-spmp?tab=readme-ov-file). We have extended Spike simulator, considered as the golden-model of the RISC-V specification, with the unified (2-stage) SPMP extensions witch servers a reference implementation of the unified SPMP model and allows us to obtain a reference execution environment for the BA51-H core. The extended Spike can be configured to simulate rv32imafch_spmp_sstc_zc_zicntr ISA and is available as a [separate repository](https://github.com/crosscon/riscv-isa-sim).

Furthermore, the CORSSCON SoC also contains the first prototype of _Perimeter guard (PG)_: a mechanism that allows a system to share HW modules across different VMs while preserving the isolation between them. A PG is a HW module that, when placed between the SoC interconnect and the HW module that we want to share (for example, cryptographic accelerator), provides a better control of which VMs and bus masters can use the module and allows the HW module to be "reset" before giving access to the module to a new VM / master. The PG can support several modes of operation, where current prototype only supports time-sharing with reset-mode with lock-release arbitration mode. In the current version of the CROSSCON SoC, as shown by the Figure 1, we use PG to control access to SRAM so that can be shared between different VMs without compromising isolation between them.

A more detailed description of CROSSCON SoC and Perimeter guard can be found in deliverable 4.1 of the [CROSSCON project](https://crosscon.eu/).

## How to upload the bitstream
	                        
The CROSSCON SoC bitstream can be uploaded to the Arty-A7 100T board aither through Vivado Lab GUI or via terminal using Tool Command Language (TCL). Here we cover the letter option and describe how to program the Arty-A7 over terminal (without the GUI). For how to program Arity-A7 over GUI see [the reference manual](https://digilent.com/reference/programmable-logic/arty-a7/reference-manual).

### Prerequisite
        
We assume that you are following the instructions on an PC with a working setup of Ubuntu or Debian OS.

In order to upload the CROSSCON SoC bitstream to the FPGA, you need to install Vivado Lab that is available [here](https://www.xilinx.com/support/download.html).

After instaslling Vivado Lab, make sure that `vivado_lab` command is available in your terminal.

### Uploading the bitstream

Plug in the Arty-A7 board to your PC using an USB-to-micro-USB cable via USB-JTAG port and then execute the following commands. (See [the Arty-A7 reference manual](https://digilent.com/reference/programmable-logic/arty-a7/reference-manual) for the overview of the Arty-A7 board.)

Note, we assume that only one FPGA board is plugged into the PC, otherwise `program_fpga.tcl` might not program the right board.

```bash
# Check out the repostory.
$git clone https://github.com/crosscon/crosscon_soc.git

$cd crosscon_soc
 
# Run the program_fpga.ctl script with crosscon_soc_a1_xc_a7.bit bitstream.
$vivado_lab -mode tcl -source program_fpga.tcl -tclargs crosscon_soc_a1_xc_a7.bit
```
When Arty-A7 100T was configured successfully:
- the last line of the previous command should be similar to `INFO: [Labtools 27-3164] End of startup status: HIGH` and
- the "DONE" LED of the Arty-A7 board should be illuminated green.

Note, if the last line of the previous command is similar to `ERROR: [Labtools 27-3165] End of startup status: LOW`, the board was not programmed correctly.

## How to run a program

A program can be run on the CROSSCON SoC by using:
- JTAG compatible debug key, as for example Beyond Semuconductor's [Beyond Debug Key](https://www.beyondsemi.com/beyond-debug-key/), and
- [BeyondStudio](https://www.beyondsemi.com/86/beyondstudio-integrated-development-environment/) IDE.

In order to obtain a copy of BeyondStudio, please create an account on Beyond Semiconductor's [webpage](https://www.beyondsemi.com/bstudio/) and request access to BeyondStudio. Once the access is granted to you, you can download BeyondStudio and BeyondStudio Manual.

### Setting up BeyondStudion and Beyond Debug Key

We assume that you are following the instructions on an PC with a working setup of Ubuntu or Debian OS.

First, connect Beyond Debug Key with to the Arity A7's JD port, as shown by the picture below, and connect the Beyond Debug Key to your PC via macro USB to USB cable.

TODO: Add picture.

Second, follow the instructions in the BeyondStudio Manual on how to setup BeyondStudion and run your fist program on the BA51 core. Note, you need to use the following information specific to the CROSSCON SoC board when creating a project.

- ...

## Running a Perimeter guard example

You can find an example of how the PG can be used in ? file.

In order to run the program, create a basic Hello Bare Metal project for RISC-V (BA5x) in BeyondStudio, copy the code in the main file and run the program.

If program was executed successfully you should see an output similar to the following:
```
Running basic PG test ...

Test successfully completed.
```

## Acknowledgments

The work presented in this repository is part of the [CROSSCON project](https://crosscon.eu/) that received funding from the European Union’s Horizon Europe research and innovation programme under grant agreement No 101070537.

