#include <config.h>

VM_IMAGE(baremetal_image, "../bao-baremetal-guest/build/crosscon_soc/baremetal.bin");
VM_IMAGE(baremetal2_image, "../bao-baremetal-guest2/build/crosscon_soc/baremetal.bin");

struct config config = {

    .vmlist_size = 2,
    .vmlist = {
        {
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

                .dev_num = 1,
                .devs = (struct vm_dev_region[]) {
                    {
                        // UART
                        .pa = 0x10700000,
                        .va = 0x10700000,
                        .size = 0xfffff,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) { 11 },  // TODO: Check if this is the right interrupt.
                    },
                },

                .arch = {
                    .irqc.plic = {
                        .base =0xc000000,
                    }
                }
            }
        },
        {
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

                .dev_num = 1,
                .devs = (struct vm_dev_region[]) {
                    {
			// UART
                        .pa = 0x10700000,
                        .va = 0x10700000,
                        .size = 0xfffff,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) { 10 },  // TODO: Check if this is the right interrupt.
                    },
                },

                .arch = {
                    .irqc.plic = {
                        .base =0xc000000,
                    }
                }
            }
        }
    }
};
