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

//
// Synchronization utilities
//

#define SHARED_MEMORY 0x7ff00

typedef struct {
    spinlock_t lock;
    uint8_t next_step_flag;
} NextStepSyncStruct;

volatile NextStepSyncStruct* ns = (NextStepSyncStruct*) SHARED_MEMORY;

void ns_wait_1() {
    
    uint8_t cns = 0;

    while (cns == 0) {

        spin_lock(&(ns->lock));

        cns = ns->next_step_flag;

        spin_unlock(&(ns->lock));

    }

}

void ns_clear() {

    spin_lock(&(ns->lock));

    ns->next_step_flag = 0;

    spin_unlock(&(ns->lock));

}

void ns_wait_1_and_clear() {
 
    while (1) {

        spin_lock(&(ns->lock));

        if (ns->next_step_flag == 1) {
            ns->next_step_flag = 0;
            
            spin_unlock(&(ns->lock));
            break;
        }

        spin_unlock(&(ns->lock));

    }

}

// Reads a line from UART until new line character is encounter or max_len
// characters were read.
int read_line(uint8_t* buffer, size_t max_len) {

    int i = 0;

    while (i < max_len) {

        char ch = uart_getchar();

        printf("%c", ch);
        fflush(stdout);

        if (((int) ch) == 13) {

            ch = uart_getchar();

            if (((int) ch) == 10) {
                printf("\n");
                break;
            }

            continue;
        }

        buffer[i] = (uint8_t) ch;

        i++;
    }

    return i;
}

//
// AES-GCM utilities
//

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

    // Wait for VM0 to allow next step.
    ns_wait_1_and_clear();

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

    printf("\n");
    printf("[guest 1] Done passing initial parameters.\n");

    // Wait for VM0 to allow next step.
    printf("\n");
    ns_wait_1_and_clear();

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

    printf("\n");
    printf("[guest 1] Done passing additional data.\n");
    printf("\n");

    //
    // Pass data blocks.
    //
    
    for (int j = 0; j < d_len;  j += 16) {

        // Wait for VM0 to allow next step.
        ns_wait_1_and_clear();

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

        printf("\n");
        printf("[guest 1] block_out[%d] (hex) = 0x", j / 16); 
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

    printf("\n");

    ns_wait_1_and_clear();

    printf("\n");
    printf("[guest 1] tag (hex) = 0x"); 
    for (int i = 0; i < 16; i++) {
        printf("%02x", ((uint8_t*) data_out_block_buf + 16)[i]);
    }
    printf("\n");

    memcpy(tag, ((uint8_t*) data_out_block_buf + 16), 16);
}


#define KEY_MAX_SIZE 32 // Bytes
#define IV_MAX_SIZE 12 // Bytes
#define ADATA_MAX_SIZE 256 // Bytes
#define DATA_MAX_SIZE 256 // Bytes

void main(void){

    // The VM is configured to use UART at address 0x11000000.

    printf("\n");
    printf("\n");
    printf("----------------------------------------------\n");
    printf("---       Cross Hardware-Software Demo     ---\n");
    printf("----------------------------------------------\n");
    printf("\n");

    printf("[guest 1] Bare-metal test guest\n");
    printf("\n");

    uint8_t buf_key[KEY_MAX_SIZE + 1];
    uint8_t buf_iv[IV_MAX_SIZE + 1];
    uint8_t buf_adata[ADATA_MAX_SIZE + 1];
    uint8_t buf_data[DATA_MAX_SIZE + 1];

    memset(buf_key, 0, sizeof buf_key);
    memset(buf_iv, 0, sizeof buf_iv);
    memset(buf_adata, 0, sizeof buf_adata);
    memset(buf_data, 0, sizeof buf_data);

    printf("[guest 1] Enter key: ");
    fflush(stdout);

    read_line(buf_key, KEY_MAX_SIZE);

    printf("[guest 1] Enter IV: ");
    fflush(stdout);

    read_line(buf_iv, IV_MAX_SIZE);

    printf("[guest 1] Enter additional data: ");
    fflush(stdout);
    uint32_t ds1_ad_len = read_line(buf_adata, ADATA_MAX_SIZE);

    printf("[guest 1] Enter data: ");
    fflush(stdout);
    uint32_t ds1_data_len = read_line(buf_data, DATA_MAX_SIZE);

    printf("\n");
    printf("[guest 1] Encrypting with key '%s' and IV '%s'.\n", buf_key, buf_iv);
    printf("[guest 1] additional data (length %dB): %s\n", ds1_ad_len, buf_adata);
    printf("[guest 1] data (length %dB): %s\n", ds1_data_len, buf_data);
    printf("\n");

    printf("\n");

    ns_clear();

    uint8_t ds1_data_out[ds1_data_len];
    uint8_t ds1_tag[16];

    printf("\n");
    printf("[guest 1] Encrypting ...\n");
    printf("\n");

    aes_gcm_cipher(
        // Input parameter
        true,
        buf_key,
        buf_iv,
        ds1_ad_len,
        buf_adata,
        ds1_data_len,
        buf_data,
        // Output parameters
        ds1_data_out,
        ds1_tag);

    uint8_t ds1_data_out_dec[ds1_data_len + 1];
    memset(ds1_data_out_dec, 0, ds1_data_len + 1);
    uint8_t ds1_tag_dec[16];

    printf("\n");
    printf("[guest 1] Decrypting ...\n");
    printf("\n");

    aes_gcm_cipher(
        // Input parameter
        false,
        buf_key,
        buf_iv,
        ds1_ad_len,
        buf_adata,
        ds1_data_len,
        ds1_data_out,
        // Output parameters
        ds1_data_out_dec,
        ds1_tag_dec);

    printf("\n");

    printf("[guest 1] decrypted msg = '%s'\n", ds1_data_out_dec);

    if (memcmp(ds1_tag, ds1_tag_dec, 16) != 0) {
        printf("[guest 1] Error: Tags do not match.\n");
    } else {
        printf("[guest 1] Tags match.\n");
    }

    printf("\n");

    printf("[guest 1] Done.\n");

    while(1) {
        asm volatile ("nop");
    }
    
}
