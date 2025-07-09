/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <core.h>
#include <stdlib.h>
#include <stdio.h>
#include <cpu.h>
#include <wfi.h>
#include <spinlock.h>
#include <plat.h>
#include <irq.h>
#include <uart.h>
#include <timer.h>
#include <string.h>

#include <crosscon_soc.h>

// SRAM address space: 0x20000000 - 0x20FFFFFF
#define SRAM_BASE_ADR 0x20000000
// SRAM's PG lock-release interface
#define PG_LOCK_RELASE_ADR 0x21000000
// SRAM's PG configuration interface
#define PG_CSR_ADR 0x23400000

#define PG_LOCK_REG 0
#define PG_RELEASE_REG 1

void on_error() {
    while(1) wfi();
}

void main(void){

    printf("[guest 0] Bare-metal test guest\n");

    // Acquire lock on the SRAM.
    uint32_t *pg_lr_csrs = (uint32_t*) PG_LOCK_RELASE_ADR;

    // Lock the SRAM.,
    volatile uint32_t x = pg_lr_csrs[PG_LOCK_REG];

    // We do not check if the lock was acquire.

    // Try to access the SRAM. If lock was not acquitted, one of the access will raise an exception.
    uint32_t *buf32 = (uint32_t*) SRAM_BASE_ADR;
    buf32[0] = 0x12345678;
    buf32[1] = 0x9abcdef0;
    buf32[2] = 0x6ab9cef1;
    buf32[3] = 0x13def547;

    printf("[guest 0] 0 =  %x, 1 = %x, 2 =  %x, 3 =  %x\n",
        buf32[0], buf32[1], buf32[2], buf32[3]);

    if ((buf32[0] != 0x12345678) || (buf32[1] != 0x9abcdef0)
            || (buf32[2] != 0x6ab9cef1) || (buf32[3] != 0x13def547)) {
        printf("[guest 0] Error: Unexpected value read from SRAM.\n");
        on_error();
    }


    printf("[guest 0] Done.\n");
   
    while(1) wfi();
}
