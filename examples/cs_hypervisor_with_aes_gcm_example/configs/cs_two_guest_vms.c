#include <config.h>

#include <arch/crosscon_soc.h>

VM_IMAGE(baremetal_image, "../baremetal-guest/build/crosscon_soc/baremetal.bin")
VM_IMAGE(baremetal2_image, "../baremetal-guest2/build/crosscon_soc/baremetal.bin")

struct vm_config vm1 = {

    .image = VM_IMAGE_BUILTIN(baremetal_image, 0x60000),

    .entry = 0x60000,

    .platform = {

        .cpu_num = 1,

        .region_num = 1,
        .regions = (struct vm_mem_region[]) {
            {
                .base = 0x60000,
                .size = 0x0ffff,
            },
        },

        .dev_num = 2,
        .devs = (struct vm_dev_region[]) {
            {
                // UART
                .pa = 0x10700000,
                .va = 0x10700000,
                .size = 0xfffff,
                .interrupt_num = 0,
            },
            {
                // AES-GCM
                .pa = AES_MM_CFG_BASE_ADR,
                .va = AES_MM_CFG_BASE_ADR,
                .size = 0xfffff,
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

    .image = VM_IMAGE_BUILTIN(baremetal2_image, 0x70000),

    .entry = 0x70000,

    .platform = {

        .cpu_num = 1,

        .region_num = 1,
        .regions = (struct vm_mem_region[]) {
            {
                .base = 0x70000,
                .size = 0x0ffff,
            },
        },

        .dev_num = 2,
        .devs = (struct vm_dev_region[]) {
            {
                // UART
                .pa = 0x10700000,
                .va = 0x10700000,
                .size = 0xfffff,
                .interrupt_num = 0,
            },
            {
                // AES-GCM
                .pa = AES_MM_CFG_BASE_ADR,
                .va = AES_MM_CFG_BASE_ADR,
                .size = 0xfffff,
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
