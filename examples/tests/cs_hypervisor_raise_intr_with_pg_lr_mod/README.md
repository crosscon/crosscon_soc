# Test: CROSSCON Hypervisor with two guests that try to access SRAM at the same time

Here you can find a test that checks that, if two guest VMs, running on the CROSSCON Hypervisor, try to access SRAM protected by PG at the same time, one of the guests will not be able to access it.

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

## Expected result

When the test is executed you should see something similar to the following output from the guests
```
...
   _____ _____   ____   _____ _____  _____ ____  _   _
  / ____|  __ \ / __ \ / ____/ ____|/ ____/ __ \| \ | |
 | |    | |__) | |  | | (___| (___ | |   | |  | |  \| |
 | |    |  _  /| |  | |\___ \\___ \| |   | |  | | . ` |
 | |____| | \ \| |__| |____) |___) | |___| |__| | |\  |
  \_____|_|  \_\\____/|_____/_____/ \_____\____/|_| \_|
  _    _                             _
 | |  | |                           (_)
 | |__| |_   _ _ __   ___ _ ____   ___ ___  ___  _ __
 |  __  | | | | '_ \ / _ \ '__\ \ / / / __|/ _ \| '__|
 | |  | | |_| | |_) |  __/ |   \ V /| \__ \ (_) | |
 |_|  |_|\__, | .__/ \___|_|    \_/ |_|___/\___/|_|
          __/ | |
         |___/|_| 16:56:26

CROSSCONHYP INFO: Initializing VM 0
CROSSCONHYP WARNING: trying to flush caches but the operation is not defined for this platform
CROSSCONHYP INFO: VM 0 adding MMIO region, VA: 0x10700000 size: 0xfffff mapped at 0x10700000
CROSSCONHYP INFO: VM 0 adding MMIO region, VA: 0x24000000 size: 0xfffff mapped at 0x24000000
CROSSCONHYP INFO: VM 0 adding MMIO region, VA: 0x20000000 size: 0xffffff mapped at 0x20000000
CROSSCONHYP INFO: VM 0 adding MMIO region, VA: 0x21000000 size: 0xffffff mapped at 0x21000000
CROSSCONHYP INFO: VM 0 is sdGPOS (normal VM)
CROSSCONHYP INFO: Initializing VM 1
CROSSCONHYP WARNING: trying to flush caches but the operation is not defined for this platform
CROSSCONHYP INFO: VM 1 adding MMIO region, VA: 0x10700000 size: 0xfffff mapped at 0x10700000
CROSSCONHYP INFO: VM 1 adding MMIO region, VA: 0x24000000 size: 0xfffff mapped at 0x24000000
CROSSCONHYP INFO: VM 1 adding MMIO region, VA: 0x20000000 size: 0xffffff mapped at 0x20000000
CROSSCONHYP INFO: VM 1 adding MMIO region, VA: 0x21000000 size: 0xffffff mapped at 0x21000000
CROSSCONHYP INFO: VM 1 is sdGPOS (normal VM)
[guest 0] Bare-metal test guest
[guest 0] 0 =  12345678, 1 = 9abcdef0, 2 =  6ab9cef1, 3 =  13def547
[gu[guest 1] Bare-metal test guest
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x20000000
est 0] Done.
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x20000004
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x20000008
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x2000000c
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x20000000
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x20000004
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x20000008
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x2000000c
[guest 1] 0 =  0, 1 = 0, 2 =  0, 3 =  0
OpenSBI: External interrupt: SRAM subsystem's PG access violation: domain = 1, address = 0x20000000
[guest 1] Error: Unexpected value read from SRAM.
```
