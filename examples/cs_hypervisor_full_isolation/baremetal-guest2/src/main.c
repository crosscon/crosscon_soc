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

#include <beyond_uart.h>
#include <crosscon_soc.h>

void aes_gcm_cipher(
    // Input parameters
    bool encrypt, // True for encryption; false for decryption.
    uint8_t key[32],
    uint8_t iv[12],
    uint32_t ad_len,
    uint8_t *ad_data,
    uint32_t d_len,
    uint8_t *data_in,
    // Output parameters
    uint8_t *data_out,
    uint8_t *tag)
{

    uint8_t data_in_block_buf[16];
    uint8_t data_out_block_buf[16 + 16 + 1]; // Space for output block and tag.

    uint32_t *aes_mm_status_reg = (uint32_t*) AES_GCM_CFG_BASE_ADR;

    //
    // Pass initial parameters.
    //

    aes_mm_status_reg[AES_GCM_ENCRYPT_REG] = (uint32_t) encrypt;

    aes_mm_status_reg[AES_GCM_KEYL_REG] = 0x2;

    for (int i = 0; i < 8; i++) {
        aes_mm_status_reg[AES_GCM_KEY_REG + i] = *((uint32_t *) (key + (4*i)));
    }

    for (int i = 0; i < 3; i++) {
        aes_mm_status_reg[AES_GCM_IV_REG + i] = *((uint32_t *) (iv + (4*i)));
    }
 
    aes_mm_status_reg[AES_GCM_A_LEN_REG] = ad_len;

    aes_mm_status_reg[AES_GCM_D_LEN_REG] = d_len;

    aes_mm_status_reg[AES_GCM_IN_D_ADDR_REG] = (uint32_t) data_in_block_buf;

    aes_mm_status_reg[AES_GCM_OUT_D_ADDR_REG] = (uint32_t) data_out_block_buf;

    aes_mm_status_reg[AES_GCM_STATE_REG] = (uint32_t) (0x1) << AES_GCM_STATE_INIT_FLAG;

    printf("[guest 1] Done passing initial parameters.\n");

    //
    // Pass additional data blocks.
    //
    
    for (int j = 0; j < ad_len; j += 16) {

        size_t csize = 16;

        if (j + 16 > ad_len) {

            memset(data_in_block_buf, 0, 16);

            csize = ad_len - j;

        }
        
        memcpy((void*) data_in_block_buf, (void*) (ad_data + j), csize);

        aes_mm_status_reg[AES_GCM_STATE_REG] = (uint32_t) (0x1) << AES_GCM_STATE_IN_D_RDY_FLAG;

        while ((aes_mm_status_reg[AES_GCM_STATE_REG] & (0x1 << AES_GCM_STATE_IN_D_RDY_FLAG))) {
            asm volatile ("nop");
        }

    }

    //
    // Pass data blocks.
    //
    
    for (int j = 0; j < d_len;  j += 16) {

        size_t csize = 16;

        if (j + 16 > d_len) {

            memset(data_in_block_buf, 0, 16);

            csize = d_len - j;

        }
        
        memcpy((void*) data_in_block_buf, (void*) (data_in + j), csize);
        
        aes_mm_status_reg[AES_GCM_STATE_REG] = (uint32_t) (0x1) << AES_GCM_STATE_IN_D_RDY_FLAG;

        while (!(aes_mm_status_reg[AES_GCM_STATE_REG] & (0x1 << AES_GCM_STATE_OUT_D_RDY_FLAG))) {
            asm volatile ("nop");
        }

        printf("[guest 1] data_out[%d] (hex) = 0x", j / 16); 
        for (int i = 0; i < 16; i++) {
            printf("%02x", ((uint8_t*) data_out_block_buf)[i]);
        }
        printf("\n");

        memcpy((void*) (data_out + j), (void*) data_out_block_buf, csize);
    }

    // Wait for tag.
    
    while (!(aes_mm_status_reg[AES_GCM_STATE_REG] & (0x1 << AES_GCM_STATE_TAG_RDY_FLAG))) {
        asm volatile ("nop");
    }

    printf("[guest 1] tag (hex) = 0x"); 
    for (int i = 0; i < 16; i++) {
        printf("%02x", ((uint8_t*) data_out_block_buf + 16)[i]);
    }
    printf("\n");

    memcpy(tag, ((uint8_t*) data_out_block_buf + 16), 16);
}

void main(void){

    // The VM is configured to use UART at address 0x11000000.
    printf("[guest 1] Bare-metal test guest\n");

    //while(1) {
    //    printf("Just waiting ...\n");
    //}
    
    uint8_t ds1_key[] = {0x38, 0xc5, 0xae, 0x2b, 0xcd, 0x1f, 0x12, 0xaa, 0x26, 0x9e, 0x45, 0xae, 0x8c, 0x87, 0x62, 0xf0, 0x30, 0x63, 0xa, 0x51, 0x37, 0xdd, 0x6d, 0x1c, 0x79, 0x9c, 0x1, 0x96, 0x26, 0xf3, 0x30, 0x96};
    uint8_t ds1_iv[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

    char* ds1_ad_data = "Additional data of the guest vm 1";
    uint32_t ds1_ad_len = strlen(ds1_ad_data);
    char* ds1_data_in = "Test message of the guest vm 1. Test message of the guest vm 1. Test message of the guest vm 1";
    uint32_t ds1_data_len = strlen(ds1_data_in);

    uint8_t ds1_data_out[ds1_data_len];
    uint8_t ds1_tag[16];

    printf("additional data = '%s'\n", ds1_ad_data);
    printf("msg = '%s'\n", ds1_data_in);

    printf("[guest 1] Encrypting ...\n");

    aes_gcm_cipher(
        // Input parameter
        true,
        ds1_key,
        ds1_iv,
        ds1_ad_len,
        (uint8_t *) ds1_ad_data,
        ds1_data_len,
        (uint8_t *) ds1_data_in,
        // Output parameters
        ds1_data_out,
        ds1_tag);

    uint8_t ds1_data_out_dec[ds1_data_len + 1];
    memset(ds1_data_out_dec, 0, ds1_data_len + 1);
    uint8_t ds1_tag_dec[16];

    printf("\n");
    printf("[guest 1] Decrypting ...\n");

    aes_gcm_cipher(
        // Input parameter
        false,
        ds1_key,
        ds1_iv,
        ds1_ad_len,
        (uint8_t *) ds1_ad_data,
        ds1_data_len,
        ds1_data_out,
        // Output parameters
        ds1_data_out_dec,
        ds1_tag_dec);

    printf("[guest 1] decrypted msg = '%s'\n", ds1_data_out_dec);

    if (memcmp(ds1_tag, ds1_tag_dec, 16) != 0) {
        printf("[guest 1] Error: Tags do not match.\n");
    }

    printf("[guest 1] Done.\n");

    while(1) {
        asm volatile ("nop");
    }
    
    //int cnt = 0;
    //while(1) {
    //    printf("[guest 0] cnt = %d\n", cnt);
    //    cnt += 1;
    //}

    //while(1) wfi();
}
