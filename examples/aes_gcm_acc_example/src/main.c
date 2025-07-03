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
 * AES-GCM example: An example of how to use AES-GCM accelerator.
 */

#include "sys.h"
#include "csr_defs.h"
#include "uart.h"
#include "crosscon_soc.h"

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void handle_external_interrupt() { 

    printf("Handling external interrupt.");

}

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

    set_pg_rspace_entry(
        (unsigned int *) QMEM_PG_CSR_ADR, 0, 0,
        (unsigned int) data_in_block_buf, (unsigned int) (data_in_block_buf + 16 + 1),
        true, true);
    set_pg_rspace_entry(
        (unsigned int *) QMEM_PG_CSR_ADR, 2, 0,
        (unsigned int) data_out_block_buf, (unsigned int) (data_out_block_buf + 16 + 16 + 1 + 1),
        true, true);

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

    printf("Done passing initial parameters.\n");

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
            printf("Waiting for additional data to be processed ...\n");
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
            printf("Waiting for output data ...\n");
        }

        printf("data_out[%d] (hex) = 0x", j); 
        for (int i = 0; i < 16; i++) {
            printf("%02x", ((uint8_t*) data_out_block_buf)[i]);
        }
        printf("\n");

        memcpy((void*) (data_out + j), (void*) data_out_block_buf, csize);

        //printf("data_out[%d] (str) = %s\n", j, (char *) data_out);

    }

    // Wait for tag.
    
    while (!(aes_mm_status_reg[AES_GCM_STATE_REG] & (0x1 << AES_GCM_STATE_TAG_RDY_FLAG))) {
        printf("Waiting for tag ...\n");
    }

    printf("tag (hex) = 0x"); 
    for (int i = 0; i < 16; i++) {
        printf("%02x", ((uint8_t*) data_out_block_buf + 16)[i]);
    }
    printf("\n");

    memcpy(tag, ((uint8_t*) data_out_block_buf + 16), 16);

    clear_pg_rspace_entry((unsigned int *) QMEM_PG_CSR_ADR, 0);
    clear_pg_rspace_entry((unsigned int *) QMEM_PG_CSR_ADR, 2);
}

int main(void) {

    // Set domain to 0.
    uint32_t *pg_add_sig_drv = (uint32_t*) PG_ADD_SIG_DRV_ADR;
    pg_add_sig_drv[0] = 0;

    // Configure APB subsystem's PG to allow access to UART to domain 0.
    set_pg_rspace_entry(
        (unsigned int *) APB_SUB_PG_CSR_ADR, 0, 0,
        UART_RBR, UART_RBR + 0xfffff, true, true);

    uint8_t ds1_key[] = {0xda, 0xaa, 0xd6, 0xe5, 0x60, 0x4e, 0x8e, 0x17, 0xbd, 0x9f, 0x10, 0x8d, 0x91, 0xe2, 0x6a, 0xfe, 0x62, 0x81, 0xda, 0xc8, 0xfd, 0xa0, 0x9, 0x10, 0x40, 0xa7, 0xa6, 0xd7, 0xbd, 0x9b, 0x43, 0xb5};
    uint8_t ds1_iv[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

    char* ds1_ad_data = "Testing ... Testing ... Testing ... Testing ... Testing ... Testing ... Testing ...";
    uint32_t ds1_ad_len = strlen(ds1_ad_data);
    char* ds1_data_in = "This are not the droids you are looking for!";
    uint32_t ds1_data_len = strlen(ds1_data_in);

    uint8_t ds1_data_out[ds1_data_len];
    uint8_t ds1_tag[16];

    printf("Encrypting ...\n");

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
    printf("Decrypting ...\n");

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

    printf("decrypted msg = %s\n", ds1_data_out_dec);

    if (memcmp(ds1_tag, ds1_tag_dec, 16) != 0) {
        printf("Error: Tags do not match.\n");
        return -1;
    }

    printf("Done.\n");
    
    return 0;
}
