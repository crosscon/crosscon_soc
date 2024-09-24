# Bao hypervisor with a single guest example

Here you can find an example setup that allows you to run Bao with a single guest on top of the CROSSCON SoC.

## Prerequisites

Follow the instruction in [README.md](../../README.md) to setup the cross-compilation toolchain, connect the Arty-A7 board and upload the CROSSCON SoC bitstream.

Note that the path to the RISC-V cross-compilation toolchain should be available through `RISCV` variable as described in Setup the RISC-V toolchain section of [README.md](../../README.md).

## Setup and compile

Move to the directory in which this file is located and run 
```
./setup.sh
```
to setup the source files. Compile the source files by running
```
./build.sh
```

## Upload and run

Connect to the CROSSCON SoC's UART port as described in Listen on UART section of [README.md](../../README.md).

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
Reading symbols from opensbi/build/platform/beyond/ba51_cs/firmware/fw_payload.elf...
Remote debugging using localhost:3333
_start () at .../opensbi/firmware/fw_base.S:51
51      MOV_3R  s0, a0, s1, a1, s2, a2
Loading section .text, size 0x1a8f0 lma 0x0
Loading section .rodata, size 0x3ff8 lma 0x1b000
Loading section .srodata, size 0x14 lma 0x1eff8
Loading section .data, size 0x5d8 lma 0x20000
Loading section .payload, size 0xb5a8 lma 0x40000
Start address 0x00000000, load size 173180
Transfer rate: 12 KB/sec, 12370 bytes/write.
Continuing.
```

Now the program was executed and if you setup everything correctly, you should see the following output on UART
```
OpenSBI v1.4-31-g322b598
   ____                    _____ ____ _____
  / __ \                  / ____|  _ \_   _|
 | |  | |_ __   ___ _ __ | (___ | |_) || |
 | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
 | |__| | |_) |  __/ | | |____) | |_) || |_
  \____/| .__/ \___|_| |_|_____/|____/_____|
        | |
        |_|

Platform Name             : Beyond BA51
Platform Features         : medeleg
Platform HART Count       : 1
Platform IPI Device       : aclint-mswi
Platform Timer Device     : aclint-mtimer @ 10000000Hz
Platform Console Device   : xlnx-uartlite
Platform HSM Device       : ---
Platform PMU Device       : ---
Platform Reboot Device    : ---
Platform Shutdown Device  : ---
Platform Suspend Device   : ---
Platform CPPC Device      : ---
Firmware Base             : 0x0
Firmware Size             : 178 KB
Firmware RW Offset        : 0x20000
Firmware RW Size          : 50 KB
Firmware Heap Offset      : 0x24000
Firmware Heap Size        : 34 KB (total), 2 KB (reserved), 9 KB (used), 22 KB (free)
Firmware Scratch Size     : 4096 B (total), 172 B (used), 3924 B (free)
Runtime SBI Version       : 2.0

Domain0 Name              : root
Domain0 Boot HART         : 0
Domain0 HARTs             : 0*
Domain0 Region00          : 0x02008000-0x0200bfff M: (I,R,W) S/U: ()
Domain0 Region01          : 0x02000000-0x02007fff M: (I,R,W) S/U: ()
Domain0 Region02          : 0x00020000-0x0002ffff M: (R,W) S/U: ()
Domain0 Region03          : 0x00000000-0x0001ffff M: (R,X) S/U: ()
Domain0 Region04          : 0x00000000-0xffffffff M: () S/U: (R,W,X)
Domain0 Next Address      : 0x00040000
Domain0 Next Arg1         : 0x00000000
Domain0 Next Mode         : S-mode
Domain0 SysReset          : yes
Domain0 SysSuspend        : yes

Boot HART ID              : 0
Boot HART Domain          : root
Boot HART Priv Version    : v1.12
Boot HART Base ISA        : rv32imafch
Boot HART ISA Extensions  : sstc,zicntr,sdtrig
Boot HART PMP Count       : 16
Boot HART PMP Granularity : 2 bits
Boot HART PMP Address Bits: 32
Boot HART MHPM Info       : 0 (0x00000000)
Boot HART Debug Triggers  : 8 triggers
Boot HART MIDELEG         : 0x00001666
Boot HART MEDELEG         : 0x00f0b509
Bao Hypervisor
BAO INFO: Initializing VM 0 ... 

BAO WARNING: trying to flush caches but the operation is not defined for this platform
[guest 0] Bao bare-metal test guest
[guest 0] cpu 0 up
[guest 0] cpu0: timer_handler
[guest 0] cpu0: timer_handler
[guest 0] cpu0: timer_handler
[guest 0] cpu0: timer_handler
[guest 0] cpu0: timer_handler
[guest 0] cpu0: timer_handler
[guest 0] cpu0: timer_handler
[guest 0] cpu0: timer_handler
...
```