#include <config.h>

#include <crosscon_soc.h>

VM_IMAGE(baremetal_image, "../baremetal-guest/build/crosscon_soc/baremetal.bin")
VM_IMAGE(baremetal2_image, "../baremetal-guest2/build/crosscon_soc/baremetal.bin")

struct vm_config vm1 = {

    .image = VM_IMAGE_BUILTIN(baremetal_image, 0x68000),

    .entry = 0x68000,

    .platform = {

        .cpu_num = 1,

        .region_num = 1,
        .regions = (struct vm_mem_region[]) {
            {
                .base = 0x68000,
                .size = 0x0c000,
            },
        },

        .dev_num = 4,
        .devs = (struct vm_dev_region[]) {
            {
                // UART
                .pa = UART_0_BASE_ADR,
                .va = UART_0_BASE_ADR,
                .size = 0xfffff,
                .interrupt_num = 0,
            },
            {
                // AES-GCM
                .pa = AES_GCM_CFG_BASE_ADR,
                .va = AES_GCM_CFG_BASE_ADR,
                .size = 0xfffff,
                .interrupt_num = 0,
            },
            {
                // SRAM
                .pa = SRAM_BASE_ADR,
                .va = SRAM_BASE_ADR,
                .size = 0xffffff,
                .interrupt_num = 0,
            },
            {
                // SRAM's PG lock-release mechanism
                .pa = SRAM_PG_LR_BASE_ADR,
                .va = SRAM_PG_LR_BASE_ADR,
                .size = 0xffffff,
                .interrupt_num = 0,
            }
        },

        .arch = {
            .irqc.plic = {
                .base = 0xc000000,
            }
        }
    }
};

struct vm_config vm2 = {

    .image = VM_IMAGE_BUILTIN(baremetal2_image, 0x74000),

    .entry = 0x74000,

    .platform = {

        .cpu_num = 1,

        .region_num = 1,
        .regions = (struct vm_mem_region[]) {
            {
                .base = 0x74000,
                .size = 0x0c000,
            },
        },

        .dev_num = 4,
        .devs = (struct vm_dev_region[]) {
            {
                // UART
                .pa = UART_1_BASE_ADR,
                .va = UART_1_BASE_ADR,
                .size = 0xfffff,
                .interrupt_num = 0,
            },
            {
                // AES-GCM
                .pa = AES_GCM_CFG_BASE_ADR,
                .va = AES_GCM_CFG_BASE_ADR,
                .size = 0xfffff,
                .interrupt_num = 0,
            },
            {
                // SRAM
                .pa = SRAM_BASE_ADR,
                .va = SRAM_BASE_ADR,
                .size = 0xffffff,
                .interrupt_num = 0,
            },
            {
                // SRAM's PG lock-release mechanism
                .pa = SRAM_PG_LR_BASE_ADR,
                .va = SRAM_PG_LR_BASE_ADR,
                .size = 0xffffff,
                .interrupt_num = 0,
            }
        },
        .arch = {
            .irqc.plic = {
                .base = 0xc000000,
            }
        }
    }
};

struct config config = {

    .vmlist_size = 2,
    .vmlist = (struct vm_config*[]) {
       &vm1,
       &vm2
    }
};
