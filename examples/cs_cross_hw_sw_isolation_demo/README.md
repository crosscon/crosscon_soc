# Cross Hardware-Software Isolation Demo

Here you can find a demonstrator that demonstrate how AES-GCM accelerator can be used from two TEEs at the same time while leveraging cross hardware-software isolation through the entire stack.

TEEs are fully isolated including UART's used to communicate with the outside world.

The demonstrator is interactive and allows you to enter key, IV, additional data and data that will be used for encryption.

## Prerequisites

Follow the instruction in [README.md](../../../README.md) to setup the cross-compilation toolchain, connect the Arty-A7 board and upload the CROSSCON SoC bitstream.

Note that the path to the RISC-V cross-compilation toolchain should be available through `RISCV` variable as described in Setup the RISC-V toolchain section of [README.md](../../../README.md).

Note that you need to listen on two different UART ports to see the output; one UART is available on Arty-a7's JD Pmod port, alongside the JTAG interface, and the other on the JB Pmod port. Figure 1 shows a basic setup with two Beyond debug keys. On JD Pmod port the TX and RX pins are available on F3 and G2 pins, and on the JB Pmod port on C16 and J15 respectively. Note that, you can listen on the UART ports with a standard UART-to-USB serial adapter.
 
<p align="center">
    <img src="../../imgs/arty_a7_debuger_setup_with_two_debug_keys.jpeg" width=70% height=70%>
</p>
<p align="center">Figure 1: Development setup with two debug key</p>

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

Run
```
./run_gdb.sh
```

Now the program was executed. If you setup everything correctly, you should see something similar to the following output after interactively stepping through the example.

Output from UART available on JD Pmod port:
```
...
----------------------------------------------------------
---       Cross Hardware-Software Isolation Demo       ---
----------------------------------------------------------

[guest 0] Bare-metal test guest

[guest 0] Enter key: key1
[guest 0] Enter IV: iv1
[guest 0] Enter additional data: add data 1
[guest 0] Enter data: This are not the droids you are looking for.

[guest 0] Encrypting with key 'key1' and IV 'iv1'.
[guest 0] additional data (length 10B): add data 1
[guest 0] data (length 44B): This are not the droids you are looking for.

[guest 0] Waiting for for data to be entered for the other VM ...

[guest 0] Encrypting ...

[guest 0] Pass initial parameters?
[guest 0] Done passing initial parameters.

[guest 0] Pass additional blocks?
[guest 0] Done passing additional data.

[guest 0] Pass next block?
[guest 0] block_out[0] (hex) = 0x2aac4d19e0dfba01761420d804860936
[guest 0] Pass next block?
[guest 0] block_out[1] (hex) = 0x01afb7d4140f84ed0aee5e686957d18a
[guest 0] Pass next block?
[guest 0] block_out[2] (hex) = 0x504e817d7e948b1d54d1c2939d5b657a

[guest 0] Read tag?
[guest 0] tag (hex) = 0xb539335ca9d32b3c95bcb887c6f97d69

[guest 0] Decrypting ...

[guest 0] Pass initial parameters?
[guest 0] Done passing initial parameters.

[guest 0] Pass additional blocks?
[guest 0] Done passing additional data.

[guest 0] Pass next block?
[guest 0] block_out[0] (hex) = 0x5468697320617265206e6f7420746865
[guest 0] Pass next block?
[guest 0] block_out[1] (hex) = 0x2064726f69647320796f752061726520
[guest 0] Pass next block?
[guest 0] block_out[2] (hex) = 0x6c6f6f6b696e6720666f722e9d5b657a

[guest 0] Read tag?
[guest 0] tag (hex) = 0xb539335ca9d32b3c95bcb887c6f97d69

[guest 0] decrypted msg: 'This are not the droids you are looking for.'
[guest 0] Tags match.

[guest 0] Done.
```

Output from UART available on JB Pmod port:
```
...
----------------------------------------------------------
---       Cross Hardware-Software Isolation Demo       ---
----------------------------------------------------------

[guest 1] Bare-metal test guest

[guest 1] Enter key: key2
[guest 1] Enter IV: iv2
[guest 1] Enter additional data: add data 2
[guest 1] Enter data: This are not the droids you are looking for.

[guest 1] Encrypting with key 'key2' and IV 'iv2'.
[guest 1] additional data (length 10B): add data 2
[guest 1] data (length 34B): This are not the droids you are lo



[guest 1] Encrypting ...


[guest 1] Done passing initial parameters.


[guest 1] Done passing additional data.


[guest 1] block_out[0] (hex) = 0x96e99e623fbe092310eb941a7d1899e5

[guest 1] block_out[1] (hex) = 0x2bd5462f73c02b09df92330d4c86aecd

[guest 1] block_out[2] (hex) = 0xcaf455e0f7d16f5822c6df70ec4caba5


[guest 1] tag (hex) = 0x247c1fc26397fb57485a30d6c68add1c

[guest 1] Decrypting ...


[guest 1] Done passing initial parameters.


[guest 1] Done passing additional data.


[guest 1] block_out[0] (hex) = 0x5468697320617265206e6f7420746865

[guest 1] block_out[1] (hex) = 0x2064726f69647320796f752061726520

[guest 1] block_out[2] (hex) = 0x6c6f55e0f7d16f5822c6df70ec4caba5


[guest 1] tag (hex) = 0x247c1fc26397fb57485a30d6c68add1c

[guest 1] decrypted msg = 'This are not the droids you are lo'
[guest 1] Tags match.

[guest 1] Done.
```
