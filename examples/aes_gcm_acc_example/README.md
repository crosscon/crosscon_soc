# AES-GCM example

Here you can find an example of how the AES-GCM accelerator can be used on the CROSSCON SoC. See the [main.c](src/main.c) file.

## Prerequisites

Follow the instruction in [README.md](../../README.md) to setup the cross-compilation toolchain, connect the Arty-A7 board and upload the CROSSCON SoC bitstream.

Note that the path to the RISC-V cross-compilation toolchain should be available through `RISCV` variable as described in Setup the RISC-V toolchain section of [README.md](../../README.md).

## Setup and compile

Move into the example's directory and run
```
./setup.sh
```
to setup the source files. You can compile the code by running
```
./build.sh 
```

## Upload and run

Connect to the CROSSCON SoC's UART port as described in Listen on UART section of [README.md](../../README.md).

Run
```
./run_gdb.sh
```

If you setup everything correctly, you should see the following output on UART
```
Encrypting ...
Done passing initial parameters.
Waiting for output data ...
data_out[0] (hex) = 0x07d2ecaff8bb29e4c4ffbff7633b19f1
Waiting for output data ...
data_out[16] (hex) = 0x9375a290dcee4e17ed5373933c57a28e
Waiting for output data ...
data_out[32] (hex) = 0x455e988e0655bd8ae962a6ca11146afc
tag (hex) = 0x2e1662fa693edac41db19aaadacb6fd6

Decrypting ...
Done passing initial parameters.
Waiting for output data ...
data_out[0] (hex) = 0x5468697320617265206e6f7420746865
Waiting for output data ...
data_out[16] (hex) = 0x2064726f69647320796f752061726520
Waiting for output data ...
data_out[32] (hex) = 0x6c6f6f6b696e6720666f722111146afc
tag (hex) = 0x2e1662fa693edac41db19aaadacb6fd6
decrypted msg = This are not the droids you are looking for!
Done.
```
