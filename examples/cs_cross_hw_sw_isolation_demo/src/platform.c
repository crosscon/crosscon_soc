/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_platform.h>

#include <sbi_utils/serial/uart8250.h>
#include <crosscon_soc.h>

/*
 * Include these files as needed.
 * See objects.mk BEYOND_BA51_xxx configuration parameters.
 */
#include <sbi_utils/ipi/aclint_mswi.h>
#include <sbi_utils/irqchip/aplic.h>
#include <sbi_utils/timer/aclint_mtimer.h>

#define BEYOND_BA51_HART_COUNT          1

#define BEYOND_BA51_APLIC_ADDR          0x0c000000
#define BEYOND_BA51_APLIC_SIZE          (0x00200000 + (BEYOND_BA51_HART_COUNT * 0x00001000))
#define BEYOND_BA51_APLIC_NUM_IDC       1
#define BEYOND_BA51_APLIC_NUM_SOURCES   32

#define BEYOND_BA51_CLINT_ADDR          0x02000000
#define BEYOND_BA51_ACLINT_MTIMER_FREQ  10000000
#define BEYOND_BA51_ACLINT_MSWI_ADDR    (BEYOND_BA51_CLINT_ADDR + CLINT_MSWI_OFFSET)
#define BEYOND_BA51_ACLINT_MTIMER_ADDR  (BEYOND_BA51_CLINT_ADDR + CLINT_MTIMER_OFFSET)

// PG restricted address range mode: register information

#define PG_RAS_NUM_OF_RANGES 8
#define PG_RAS_ADDR_FIRST_REG_ADDR 0x10
#define PG_RAS_ACC_PRM_FIRST_REG_ADDR (PG_RAS_ADDR_FIRST_REG_ADDR + PG_RAS_NUM_OF_RANGES + 1)

#define PG_RAS_ACC_PRM_REG_R_BIT 0
#define PG_RAS_ACC_PRM_REG_W_BIT 1
#define PG_RAS_ACC_PRM_REG_DID_SIZE 29
#define PG_RAS_ACC_PRM_REG_DID_LOW 2
#define PG_RAS_ACC_PRM_REG_DID_HIGH (PG_RAS_ACC_PRM_REG_DID_LOW + PG_RAS_ACC_PRM_REG_DID_SIZE)
#define PG_RAS_ACC_PRM_REG_A_BIT 31

//static struct aplic_data aplic = {
//	.addr = BEYOND_BA51_APLIC_ADDR,
//	.size = BEYOND_BA51_APLIC_SIZE,
//	.num_idc = BEYOND_BA51_APLIC_NUM_IDC,
//	.num_source = BEYOND_BA51_APLIC_NUM_SOURCES,
//	.targets_mmode = false,
//	.has_msicfg_mmode = false,
//	//struct aplic_msicfg_data msicfg_mmode;
//	.has_msicfg_smode = false
//	//struct aplic_msicfg_data msicfg_smode;
//	//struct aplic_delegate_data delegate[APLIC_MAX_DELEGATE];
//};

static struct aclint_mswi_data mswi = {
    .addr = BEYOND_BA51_ACLINT_MSWI_ADDR,
    .size = ACLINT_MSWI_SIZE,
    .first_hartid = 0,
    .hart_count = BEYOND_BA51_HART_COUNT,
};

static struct aclint_mtimer_data mtimer = {
    .mtime_freq = BEYOND_BA51_ACLINT_MTIMER_FREQ,
    .mtime_addr = BEYOND_BA51_ACLINT_MTIMER_ADDR +
                  ACLINT_DEFAULT_MTIME_OFFSET,
    .mtime_size = ACLINT_DEFAULT_MTIME_SIZE,
    .mtimecmp_addr = BEYOND_BA51_ACLINT_MTIMER_ADDR +
                     ACLINT_DEFAULT_MTIMECMP_OFFSET,
    .mtimecmp_size = ACLINT_DEFAULT_MTIMECMP_SIZE,
    .first_hartid = 0,
    .hart_count = BEYOND_BA51_HART_COUNT,
    .has_64bit_mmio = true,
};

/*
 * Platform early initialization.
 */
static int beyond_ba51_early_init(bool cold_boot)
{

    // Enable wfi instruction wake up on timer and external interrupts.
    __asm__ volatile ("csrw 0x7c0, 0x3"); 

    // Set domain to 0.
    uint32_t *pg_add_sig_drv = (uint32_t*) PG_ADD_SIG_DRV_ADR;
    pg_add_sig_drv[0] = 0;

    // Configure APB subsystem's PG to allow access to UART to domain 0.
    set_pg_rspace_entry(
        (unsigned int *) APB_SUB_PG_CSR_ADR, 0, 0,
        UART_0_BASE_ADR, UART_0_BASE_ADR + 0xfffff,
        true, true);

    return 0;
}

/*
 * Platform final initialization.
 */


#define CSR_MIDELEG_F_MEID 0x00000800
#define CSR_MIE_F_MEIE 0x00000800
#define CSR_MSTATUS_F_SIE 0x00000002
#define CSR_MSTATUS_F_MIE 0x00000008

#define CROSSCON_SOC_PG_IRQ 12

#define CSR_PICMR0 2032
#define CSR_PICMR1 2033

static inline uint32_t csr_set_picmr0(uint32_t setmask)
{
	uint32_t __rv;
	__asm__ volatile ("csrrs %0, %1, %2" : "=r"(__rv) : "I"(CSR_PICMR0), "rK"(setmask));
	return __rv;
}

static inline uint32_t csr_set_picmr1(uint32_t setmask)
{
  uint32_t __rv;
	__asm__ volatile ("csrrs %0, %1, %2" : "=r"(__rv) : "I"(CSR_PICMR1), "rK"(setmask));
	return __rv;
}

static void pic_enable_irq_line(uint64_t line, int enabled);
static void pic_enable_irq_line(uint64_t line, int enabled) {

    //SET_CSR(mstatus, 0x00000008);

    if (enabled) {
        csr_set_picmr0((uint32_t) line);
        csr_set_picmr1((uint32_t) (line >> 32));
    } else {
        csr_set_picmr0((uint32_t) line);
        csr_set_picmr1((uint32_t) (line >> 32));
    }

    //return (((uint64_t) csr_read_picmr1() << 32) | (uint64_t) csr_read_picmr0()) & line;
}

void pic_enable_irq(unsigned int);
void pic_enable_irq(unsigned int irq) {

    pic_enable_irq_line((uint64_t) 1 << irq, 1);
}

static int beyond_ba51_final_init(bool cold_boot)
{

    // Enable external interrupts.

    pic_enable_irq(CROSSCON_SOC_PG_IRQ);

    //csr_set(CSR_MIDELEG, CSR_MIDELEG_F_MEID); // Delegate machine external interrupts to supervisor.
    csr_set(CSR_MIE, CSR_MIE_F_MEIE); // Enable machine external interrupt.
    //csr_set(CSR_MSTATUS, CSR_MSTATUS_F_SIE); // Enable global supervisor exceptions.
    csr_set(CSR_MSTATUS, CSR_MSTATUS_F_MIE); // Enable global machine exceptions.
   
    return 0;
}

/*
 * Initialize the platform console.
 */
static int beyond_ba51_console_init(void)
{
    return uart8250_init(UART_0_BASE_ADR, CPU_CLK, 9600, 0, 1, 0);
}

/*
 * Initialize the platform interrupt controller for current HART.
 */
static int beyond_ba51_irqchip_init(bool cold_boot)
{
    ////u32 hartid = current_hartid();
    //int ret;

    ///* Example if the generic APLIC driver is used */
    //if (cold_boot) {
    //    //ret = plic_cold_irqchip_init(&plic);
    //    ret = aplic_cold_irqchip_init(&aplic);
    //    if (ret)
    //        return ret;
    //}

    //return plic_warm_irqchip_init(&plic, 2 * hartid, 2 * hartid + 1);
    return 0;
}

/*
 * Initialize IPI for current HART.
 */
static int beyond_ba51_ipi_init(bool cold_boot)
{
    int ret;

    /* Example if the generic ACLINT driver is used */
    if (cold_boot) {
        ret = aclint_mswi_cold_init(&mswi);
        if (ret)
            return ret;
    }

    return aclint_mswi_warm_init();
}

/*
 * Initialize platform timer for current HART.
 */
static int beyond_ba51_timer_init(bool cold_boot)
{
    int ret;

    /* Example if the generic ACLINT driver is used */
    if (cold_boot) {
        ret = aclint_mtimer_cold_init(&mtimer, NULL);
        if (ret)
            return ret;
    }

    return aclint_mtimer_warm_init();
}

/*
 * Platform descriptor.
 */
const struct sbi_platform_operations beyond_ba51_ops = {
    .early_init         = beyond_ba51_early_init,
    .final_init         = beyond_ba51_final_init,
    .console_init       = beyond_ba51_console_init,
    .irqchip_init       = beyond_ba51_irqchip_init,
    .ipi_init           = beyond_ba51_ipi_init,
    .timer_init         = beyond_ba51_timer_init
};

#define HART_STACK_SIZE 0x1000
#define HEAP_SIZE(__num_hart) (0x4000 + 0x400 * (__num_hart))

const struct sbi_platform platform = {
    .opensbi_version    = OPENSBI_VERSION,
    .platform_version   = SBI_PLATFORM_VERSION(0x0, 0x00),
    .name               = "Beyond BA51",
    .features           = SBI_PLATFORM_DEFAULT_FEATURES,
    .hart_count         = BEYOND_BA51_HART_COUNT,
    .hart_stack_size    = HART_STACK_SIZE,
    .heap_size          = HEAP_SIZE(BEYOND_BA51_HART_COUNT),
    .platform_ops_addr  = (unsigned long)&beyond_ba51_ops
};
