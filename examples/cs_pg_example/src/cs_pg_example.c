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

#define SRAM_BASE_ADR 0x20000000
#define PG_LOCK_RELASE_ADR 0x21000000
#define PG_ADD_SIG_DRV_ADR 0x23100000
#define PG_CSR_ADR 0x23200000

#define CROSSCON_SOC_IRQ_PG_FOR_SRAM 12

#define PG_LOCK_REG 0
#define PG_RELEASE_REG 1

#define PG_CFG_REG_ADDR 1
#define PG_INTERRUPT_SRC_REG_ADDR 2
#define PG_INTERRUPT_CAUSE_REG_ADDR 3

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

int main(void) {
    printf("CROSSCON SoC: Running basic PG test ...\n");

    //
    // Try to read and write to SRAM.
    //

    printf("Trying to read and write to SRAM ...\n");

    // Acquire lock on SRAM.
    uint32_t *pg_lr_csrs = (uint32_t*) PG_LOCK_RELASE_ADR;
    if (pg_lr_csrs[PG_LOCK_REG] != 1) {
        printf("Error: SRAM could not be lock.\n");
        return -1;
    }

    uint32_t *buf32 = (uint32_t*) SRAM_BASE_ADR;
    buf32[0] = 0x12345678;
    buf32[1] = 0x9abcdef0;
    buf32[2] = 0x6ab9cef1;
    buf32[3] = 0x13def547;

    if ((buf32[0] != 0x12345678) || (buf32[1] != 0x9abcdef0)
            || (buf32[2] != 0x6ab9cef1) || (buf32[3] != 0x13def547)) {
        printf("Error: Unexpected value read from SRAM.\n");
        return -1;
    }

    //
    // Test that interrupt is raised when wrong domain tries to access SRAM.
    //

    printf("Trying to access SRAM with the wrong DID ...\n");

    pic_enable_irq(CROSSCON_SOC_IRQ_PG_FOR_SRAM);
    csr_set_mie(CSR_MIE_F_MEIE);
    csr_set_mstatus(CSR_MSTATUS_F_MIE); // Enable global machine exceptions.

    // Change the DID of the core.
    uint32_t *pg_add_sig_drv = (uint32_t*) PG_ADD_SIG_DRV_ADR;
    pg_add_sig_drv[0] = NEW_DID;
    if (pg_add_sig_drv[0] != NEW_DID) {
        printf("Error: Could not set new DID.\n");
        return -1;
    }

    // The following write should trigger an interrupt.
    buf32[0] = 0x12345678;

    // Wait for the interrupt to be handled.
    unsigned int cnt = 0;
    while (!interrupt_raised) {
        if (10000 < cnt) {
            printf("Error: Interrupt was not raised.\n");
            return -1;
        }

        cnt++;
    }

    printf("Interrupt was raised.\n");

    uint32_t *pg_csrs = (uint32_t*) PG_CSR_ADR;
    if (pg_csrs[PG_INTERRUPT_SRC_REG_ADDR] != 0) {
        printf("Error: Source bit was not cleared.\n");
        return -1;
    }

    if (pg_csrs[PG_INTERRUPT_CAUSE_REG_ADDR] != NEW_DID) {
        printf("Error: Unexpected cause of the interrupt.\n");
        return -1;
    }

    // Change the DID of the core.
    pg_add_sig_drv[0] = 0;
    if (pg_add_sig_drv[0] != 0) {
        printf("Error: DID was not changed.\n");
        return -1;
    }

    // Release lock on SRAM.
    if (!pg_lr_csrs[PG_RELEASE_REG]) {
        printf("Error: SRAM was not released.\n");
        return -1;
    }

    // When the lock is released, SRAM is reset.

    //
    // Try to read and write to SRAM with a different HDID.
    //

    printf("Trying to read and write to SRAM with a different DID ...\n");

    // Change the HDID.
    uint32_t *pg_add_sig_drv_csrs = (uint32_t*) PG_ADD_SIG_DRV_ADR;
    pg_add_sig_drv_csrs[0] = NEW_DID;

    // SRAM cannot be locked while it is being reset. Because of that, we
    // are just requesting the lock until is reset has been completed.
    cnt = 0;
    while (!pg_lr_csrs[PG_LOCK_REG]) {
        if (10000 < cnt) {
            printf("Error: SRAM could not be relocked.\n");
            return -1;
        }

        cnt++;
    }

    // Check that SRAM was reset.
    if (buf32[0] != 0 && buf32[1] != 0 && buf32[2] != 0 && buf32[3] != 0) {
        printf("Error: SRAM entries were not zeroized.\n");
        return -1;
    }

    //
    // Try to read and write to SRAM.
    //

    buf32[0] = 0x12345678;
    buf32[1] = 0x9abcdef0;
    buf32[2] = 0x6ab9cef1;
    buf32[3] = 0x13def547;

    if ((buf32[0] != 0x12345678) || (buf32[1] != 0x9abcdef0)
            || (buf32[2] != 0x6ab9cef1) || (buf32[3] != 0x13def547)) {
        printf("Error: Read unexpected values from SRAM.\n");
        return -1;
    }

    printf("Test completed successfully.\n");

    return 0;
}
