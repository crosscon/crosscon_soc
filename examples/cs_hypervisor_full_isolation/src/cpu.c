/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <crossconhyp.h>
#include <cpu.h>
#include <arch/sbi.h>
#include <platform.h>

#include <crosscon_soc.h>

cpuid_t CPU_MASTER __attribute__((section(".data")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{
    if (cpuid == CPU_MASTER) {
        sbi_init();
        for (size_t hartid = 0; hartid < platform.cpu_num; hartid++) {
            if (hartid == cpuid) {
                continue;
            }
            struct sbiret ret = sbi_hart_start(hartid, load_addr, 0);
            if (ret.error < 0) {
                WARNING("failed to wake up hart %d\n", hartid);
            }
        }
    }

#ifdef MEM_PROT_MPU
    spmp_init(&cpu()->arch.spmp_hyp, PRIV_HYP);
    spmp_set_active(&cpu()->arch.spmp_hyp, true);
#endif

    // CROSSCON SoC specific
    // TODO: This is specific for the platform. Find a better place for this.

    // Allow both VM1 (domain 0) to access UART 0 and VM2 (domain 1) to access UART 1.
    set_pg_rspace_entry((unsigned int *) APB_SUB_PG_CSR_ADR, 0, 0, UART_0_BASE_ADR, UART_0_BASE_ADR + 0xfffff, true, true);
    //set_pg_rspace_entry((unsigned int *) APB_SUB_PG_CSR_ADR, 2, 0, UART_1_BASE_ADR, UART_1_BASE_ADR + 0xfffff, true, true);
    //set_pg_rspace_entry((unsigned int *) APB_SUB_PG_CSR_ADR, 4, 1, UART_0_BASE_ADR, UART_0_BASE_ADR + 0xfffff, true, true);
    set_pg_rspace_entry((unsigned int *) APB_SUB_PG_CSR_ADR, 2, 1, UART_1_BASE_ADR, UART_1_BASE_ADR + 0xfffff, true, true);

    // TODO: Needs to be dynamically set.
    // PG's QMEM PG so that AES-GCM can access VM1's and VM2's memory over AHB bus.
    set_pg_rspace_entry((unsigned int *) QMEM_PG_CSR_ADR, 0, 0, 0x68000, 0x74000, true, true);
    set_pg_rspace_entry((unsigned int *) QMEM_PG_CSR_ADR, 2, 1, 0x74000, 0x80000, true, true);
}

void cpu_arch_standby(void)
{
    struct sbiret ret = sbi_hart_suspend(SBI_HSM_SUSPEND_RET_DEFAULT, 0, 0);
    if (ret.error < 0) {
        ERROR("failed to suspend hart %d", cpu()->id);
    }
    __asm__ volatile("mv sp, %0\n\r"
                     "j cpu_standby_wakeup\n\r" ::"r"(&cpu()->stack[STACK_SIZE]));
    ERROR("returned from standby wake up");
}

void cpu_arch_powerdown(void)
{
    __asm__ volatile("wfi\n\t" ::: "memory");
    __asm__ volatile("mv sp, %0\n\r"
                     "j cpu_powerdown_wakeup\n\r" ::"r"(&cpu()->stack[STACK_SIZE]));
    ERROR("returned from powerdown wake up");
}
