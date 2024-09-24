/*
 * Copyright (c) 2014-2024 Beyond Semiconductor
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the company may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BEYOND SEMICONDUCTOR ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL BEYOND SEMICONDUCTOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * ===========================================================================
 * Perimeter guard example
 *
 * Program tries to access SRAM protected by the PG with different DID.
 *
 * This sample is compatible with crosscon_soc_with_pg_a7.
 * ===========================================================================
 */

#include "sys.h"
#include "csr_defs.h"

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

// SRAM's base address
#define SRAM_BASE_ADR 0x20000000

// SRAM's PG base address for the lock and release CSRs
#define SRAM_PG_LOCK_RELASE_CSR_BASE 0x21000000

// Lock release registers
#define PG_LOCK_REG 0
#define PG_RELEASE_REG 1

// PG's configuration registers base address
#define PG_CSR_ADR 0x23200000

// PG's configuration registers
#define PG_CFG_REG_ADDR 1
#define PG_INTERRUPT_SRC_REG_ADDR 2
#define PG_INTERRUPT_CAUSE_REG_ADDR 3

// SRAM's PG interrupt number
#define CROSSCON_SOC_IRQ_PG_FOR_SRAM 12

// BA51-H DID register address base
#define PG_DRV_CSR_BASE 0x23100000

#define NEW_DID 0xa

static uint64_t pic_enable_irq_line(uint64_t line, int enabled) {

    SET_CSR(mstatus, 0x00000008);

    if (enabled) {
        csr_set_picmr0((uint32_t) line);
        csr_set_picmr1((uint32_t) (line >> 32));
    } else {
        csr_set_picmr0((uint32_t) line);
        csr_set_picmr1((uint32_t) (line >> 32));
    }

    return (((uint64_t) csr_read_picmr1() << 32) | (uint64_t) csr_read_picmr0())
            & line;
}

void pic_enable_irq(unsigned int irq) {

    pic_enable_irq_line(1 << irq, 1);
}

bool interrupt_raised = false;

void bpg_irq_handler() {

    uint32_t *pg_csrs = (uint32_t*) PG_CSR_ADR;
    pg_csrs[PG_INTERRUPT_SRC_REG_ADDR] = 1;

    interrupt_raised = true;
}

void handle_external_interrupt() {

    uint64_t picsr;
    int irq_line = 0;

    picsr = ((uint64_t) csr_read_picsr1() << 32) | (uint64_t) csr_read_picsr0();

    while (picsr) {
        uint64_t t = picsr;
        while (!(t & (1 << irq_line))) {
            ++irq_line;
        }

        if (irq_line == CROSSCON_SOC_IRQ_PG_FOR_SRAM) {
            bpg_irq_handler();
        } else {
            // Unexpected interrupt received.
            while (1)
                ;
        }

        picsr &= ~(1ULL << irq_line);
    }
}

//
// Utilities
//

int str_to_uint32_hex(char *str, size_t len, uint32_t *val) {
    *val = (uint32_t) strtoul(str, NULL, 16);
    return errno;
}

int str_to_uint32(char *str, size_t len, uint32_t *val) {
    *val = (uint32_t) strtoul(str, NULL, 10);
    return errno;
}

#define AS_STR(x) __STRINGIFY(x)

#define COMMAND_MAX_SIZE 7 // characters
#define DESTINATION_MAX_SIZE 10 // characters
#define VALUE_MAX_SIZE 10 // characters
#define ITERATION_MAX_SIZE 10 // characters

void  __attribute__((optimize("O0")))  delay(size_t t) {
    for(size_t i=0; i<t; i++){__asm__("nop");}
}

//
// SRAM related functionality
//

void set_did(uint32_t did) {
    uint32_t *pg_add_sig_drv = (uint32_t*) PG_DRV_CSR_BASE;
    pg_add_sig_drv[0] = did;
}

uint32_t get_did() {
    return *((uint32_t*) PG_DRV_CSR_BASE);
}

// Request a lock on a HW module with lock and release registers at base 'pg_lr_base'.
bool lock(uint32_t pg_lr_base) {
    return ((uint32_t *)pg_lr_base)[PG_LOCK_REG];
}

// Release a lock on a HW module with lock and release registers at base 'pg_lr_base'.
bool release(uint32_t pg_lr_base) {
    return ((uint32_t *)pg_lr_base)[PG_RELEASE_REG];
}

int main(void) {

    // Enable interrupts
    pic_enable_irq(CROSSCON_SOC_IRQ_PG_FOR_SRAM);
    csr_set_mie(CSR_MIE_F_MEIE);
    csr_set_mstatus(CSR_MSTATUS_F_MIE); // Enable global machine exceptions.

    printf("---------------------------------------------\n");
    printf("CROSSCON SoC: Perimeter guard (PG) demo setup\n");
    printf("---------------------------------------------\n");
    printf("\n");

    char buf_cmd[COMMAND_MAX_SIZE + 1];
    char buf_dest[DESTINATION_MAX_SIZE + 1];
    char buf_val[VALUE_MAX_SIZE + 1];
    char buf_iter[ITERATION_MAX_SIZE + 1];

    while (1) {

        // Clear the buffers.
        memset(buf_cmd, 0, sizeof buf_cmd);
        memset(buf_dest, 0, sizeof buf_dest);
        memset(buf_val, 0, sizeof buf_val);
        memset(buf_iter, 0, sizeof buf_val);

        printf("\n");
        printf("[APP%"PRIu32"]$ ", get_did());
        fflush(stdout);

        // TODO: Find a better way to read a command.

        // Read command.
        int rs = scanf("%"AS_STR(COMMAND_MAX_SIZE)"s", buf_cmd);
        if (rs < 0) {
            printf("Error: A command could not be read.\n");
            goto _cleanup;
        }
        int size = strlen(buf_cmd);

        if (strncmp(buf_cmd, "setid", size) == 0) {
            // Handle SETID command.

            // Read the DID parameter.
            rs = scanf("%"AS_STR(VALUE_MAX_SIZE)"s", buf_val);
            if (rs < 0) {
                printf("Error: The DID parameter could not be read.\n");
                goto _cleanup;
            }
            uint32_t val = 0;
            if (str_to_uint32(buf_val, VALUE_MAX_SIZE, &val) < 0) {
                printf("Error: The DID parameter has invalid format.\n");
                goto _cleanup;
            }

            set_did(val);

        } else if (strncmp(buf_cmd, "lock", size) == 0) {
            // Handle LOCK command.

            if (lock(SRAM_PG_LOCK_RELASE_CSR_BASE)) {
                printf("SRAM lock acquired.\n");
            } else {
                printf("Error: SRAM could not be lock.\n");
            }

        } else if (strncmp(buf_cmd, "release", size) == 0) {
            // Handle RELEASE command.

            if (release(SRAM_PG_LOCK_RELASE_CSR_BASE)) {
                printf("SRAM lock released.\n");
            } else {
                printf("Error: SRAM lock could not be released.\n");
            }

        } else if (strncmp(buf_cmd, "read", size) == 0) {
            // Handle READ command.

            // Read the destination parameter.
            rs = scanf("%"AS_STR(DESTINATION_MAX_SIZE)"s", buf_dest);
            if (rs < 0) {
                printf("Error: The destination parameter could not be read.\n");
                goto _cleanup;
            }
            uint32_t dest = 0;
            if (str_to_uint32_hex(buf_dest, DESTINATION_MAX_SIZE, &dest) < 0) {
                printf("Error: The destination parameter has invalid format.\n");
                goto _cleanup;
            }
            if (dest % 4 != 0) {
                printf("Error: The destination address is not aligned.\n");
                goto _cleanup;
            }

            uint32_t val = *((uint32_t *) dest);
            delay(1000); // Wait for the interrupt to trigger the interrupt handler.
            if (interrupt_raised) {
                printf("PG raised an interrupt. Access not allowed.\n");
                interrupt_raised = false;
            } else {
                printf("*(0x%"PRIx32") = 0x%"PRIx32"\n", dest, val);
            }


        } else if (strncmp(buf_cmd, "readn", size) == 0) {
            // Handle READN command.

            // Read the destination parameter.
            rs = scanf("%"AS_STR(DESTINATION_MAX_SIZE)"s", buf_dest);
            if (rs < 0) {
                printf("Error: The destination parameter could not be read.\n");
                goto _cleanup;
            }
            uint32_t dest = 0;
            if (str_to_uint32_hex(buf_dest, DESTINATION_MAX_SIZE, &dest) < 0) {
                printf("Error: The destination parameter has invalid format.\n");
                goto _cleanup;
            }
            if (dest % 4 != 0) {
                printf("Error: The destination address is not aligned.\n");
                goto _cleanup;
            }

            // Read the number of iterations.
            rs = scanf("%"AS_STR(ITERATION_MAX_SIZE)"s", buf_iter);
            if (rs < 0) {
                printf("Error: The iterations parameter could not be read.\n");
                goto _cleanup;
            }
            uint32_t iter = 0;
            if (str_to_uint32(buf_iter, ITERATION_MAX_SIZE, &iter) < 0) {
                printf("Error: The iterations parameter has invalid format.\n");
                goto _cleanup;
            }

            for (size_t i = 0; i < iter; i++) {

                uint32_t val = *((uint32_t *) dest);
                delay(1000); // Wait for the interrupt to trigger the interrupt handler.
                if (interrupt_raised) {
                    printf("PG raised an interrupt. Access not allowed.\n");
                    interrupt_raised = false;
                } else {
                    printf("*(0x%"PRIx32") = 0x%"PRIx32"\n", dest, val);
                }

                dest += 4;
            }

        } else if (strncmp(buf_cmd, "write", size) == 0) {

            // Read the destination parameter.
            rs = scanf("%"AS_STR(DESTINATION_MAX_SIZE)"s", buf_dest);
            if (rs < 0) {
                printf("Error: The destination parameter could not be read.\n");
                goto _cleanup;
            }
            uint32_t dest = 0;
            if (str_to_uint32_hex(buf_dest, DESTINATION_MAX_SIZE, &dest) < 0) {
                printf("Error: The destination parameter has invalid format.\n");
                goto _cleanup;
            }
            if (dest % 4 != 0) {
                printf("Error: The destination address is not aligned.\n");
                goto _cleanup;
            }


            // Read the value parameter.
            rs = scanf("%"AS_STR(VALUE_MAX_SIZE)"s", buf_val);
            if (rs < 0) {
                printf("Error: The value parameter could not be read.\n");
                goto _cleanup;
            }
            uint32_t val = 0;
            if (str_to_uint32_hex(buf_val, VALUE_MAX_SIZE, &val) < 0) {
                printf("Error: The value parameter has invalid format.\n");
                goto _cleanup;
            }

            ((uint32_t *) dest)[0] = val;
            delay(1000); // Wait for the interrupt to trigger the interrupt handler.
            if (interrupt_raised) {
                printf("PG raised an interrupt. Access not allowed.\n");
                interrupt_raised = false;
            } else {
                printf("*(0x%"PRIx32") = 0x%"PRIx32"\n", dest, val);
            }

        } else {
            printf("Unknown command\n");
        }

        _cleanup:
        // Perform the necessary cleanup before the next command is read.

        scanf("%[^\n]c"); // Skip the rest of the characters in the current line.
    }

    return 0;
}
