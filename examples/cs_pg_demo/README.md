# Perimeter guard demo

Here you can find a demo program that allows you to interact with SRAM hardware module protected by PG.

## Prerequisites

Follow the instruction in [README.md](../../README.md) to setup the cross-compilation toolchain, connect the Arty-A7 board and upload the CROSSCON SoC bitstream.

Note that the path to the RISC-V cross-compilation toolchain should be available through `RISCV` variable as described in Setup the RISC-V toolchain section of [README.md](../../README.md).

## Compile

Compile the program by running
```
./build.sh
```

## Upload and run

Connect to the CROSSCON SoC's UART port, as described in Listen on UART section of [README.md](../../README.md), using local `./listen_on_uart.sh` script.

Run
```
./run_gdb.sh
```

You should see something similar to
```
GNU gdb (GDB) 15.0.50.20240107-git
Copyright (C) 2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=x86_64-pc-linux-gnu --target=riscv32-unknown-elf".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from Debug/cs_pg_example.elf...
Remote debugging using localhost:3333
_alldone () at ../src/entry.S:114
114     wfi
TAP riscv.cpu does not have valid IDCODE (idcode=0xfffffffe)
Loading section .init, size 0x196 lma 0x0
Loading section .rodata, size 0x1758 lma 0x198
Loading section .text, size 0x1fe0c lma 0x18f0
Loading section .data, size 0x6c6 lma 0x21700
Start address 0x00000000, load size 138688
Transfer rate: 11 KB/sec, 11557 bytes/write.
(gdb) continue
```

Now the program is running and you are able to interact with the SRAM module protected by PG using UART port. For example, you can perform the following sequence of commands. Note that the SRAM is memory mapped to 0x20xxxxxx address range.
```
---------------------------------------------
CROSSCON SoC: Perimeter guard (PG) demo setup
---------------------------------------------


[APP1]$ read 0x20000004

PG raised an interrupt. Access not allowed.

[APP1]$ lock

SRAM lock acquired.

[APP1]$ read 0x20000004

*(0x20000004) = 0x0

[APP1]$ write 0x20000004 0x1234

[APP1]$ write 0x20000008 0x5678

[APP1]$ read 0x20000004

*(0x20000004) = 0x1234

[APP1]$ read 0x20000008

*(0x20000008) = 0x5678

[APP1]$ release

SRAM lock released.

[APP1]$ setid 9

[APP9]$ SRAM lock acquired.

[APP9]$ read 0x20000004

*(0x20000004) = 0x0

[APP9] read 0x20000008

*(0x20000004) = 0x0
```

You need to reset the CROSSCON SoC, by pressing the RESET button on the Arty-A7 board, in order to run the program multiple times in a row.

