# Test: AES-GCM speed test

Here you can find an AES-GCM accelerator speedtest.

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
data_len = 2961
Encrypting with 128-bit key ...
Done passing initial parameters.
# of cycles to process data = 45792
# of processed blocks = 186
# of cycles per block = 246
encryption / decryption speed = 12703 Kbps
tag (hex) = 0x8f53848fde84d30bbf8954f326f084e2
Encrypting with 256-bit key ...
Done passing initial parameters.
# of cycles to process data = 46536
# of processed blocks = 186
# of cycles per block = 250
encryption / decryption speed = 12500 Kbps
tag (hex) = 0x0389161a2a221d640b4225317503cc1d

Decrypting with 256-bit key ...
Done passing initial parameters.
# of cycles to process data = 46536
# of processed blocks = 186
# of cycles per block = 250
encryption / decryption speed = 12500 Kbps
tag (hex) = 0x0389161a2a221d640b4225317503cc1d
decrypted msg = <...>
Done.
```
where <...> is replaced with decrypted message.
