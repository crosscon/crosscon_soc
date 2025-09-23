# Test: CROSSCON Hypervisor with two guest VM's where VMs tries to access the memory of the other VM

Here you can find a test setup where one guest VM tries to access the memory of another VM but the access is prevented by hSPMP.

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

## Upload and run

Connect to the CROSSCON SoC's UART port as described in Listen on UART section of [README.md](../../README.md).

Run
```
./run_gdb.sh
```

You should see something similar to

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
         |___/|_| 11:41:50

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
CROSSCONHYP ERROR: hSPMP access violation at address 0x6a13c. Halting execution.

```
