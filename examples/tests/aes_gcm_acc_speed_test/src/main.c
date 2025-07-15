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

static inline uint32_t get_cycle_cnt() {
    uint32_t x;
    asm volatile ("csrr %0, mcycle" : "=r"(x));
    return x;
}

void aes_gcm_cipher(
    // Input parameters
    bool encrypt, // True for encryption; false for decryption.
    uint8_t keyl, // Key size: 0x2 for 256-bit key, 0x00 for 128-bit key
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

    aes_mm_status_reg[AES_GCM_KEYL_REG] = (uint32_t) keyl;

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
            asm volatile ("nop");
        }

    }

    //
    // Pass data blocks.
    //

    uint32_t nc_start = get_cycle_cnt();
    
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

        memcpy((void*) (data_out + j), (void*) data_out_block_buf, csize);
    }

    uint32_t nc_diff = get_cycle_cnt() - nc_start;
    printf("# of cycles to process data = %lu\n", nc_diff);
    uint32_t n_of_d_blocks = (d_len + 16 - 1) / 16;
    printf("# of processed blocks = %ld\n", n_of_d_blocks);
    const uint32_t CPU_FREQUENCY = 25000000; // Hz
    const uint32_t n_cycles_per_block = (uint32_t) (nc_diff / n_of_d_blocks);
    printf("# of cycles per block = %lu\n", n_cycles_per_block);
    uint32_t proc_speed = (uint32_t)((CPU_FREQUENCY / n_cycles_per_block) * 128);
    printf("encryption / decryption speed = %lu Kbps\n", proc_speed / 1024);

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
    char* ds1_data_in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus scelerisque pulvinar consectetur. Morbi ullamcorper at lectus sit amet ullamcorper. Curabitur ac feugiat orci, id convallis orci. Morbi diam nisl, malesuada ut libero rhoncus, fringilla varius metus. Ut malesuada, neque id maximus pellentesque, nisl mi vestibulum tellus, et suscipit velit ligula ac nunc. Vestibulum accumsan quam tortor, ac pretium ipsum pellentesque ac. Maecenas vel urna eu urna auctor imperdiet eu ac metus. Duis sagittis, lectus lacinia malesuada dictum, augue eros semper sapien, nec consequat ligula justo in mauris. Sed porttitor convallis lacus, id aliquet neque imperdiet id. Quisque ac bibendum neque. Aenean sodales fermentum felis hendrerit congue. Nullam et felis arcu. Nam ac nisl sagittis, blandit justo et, suscipit ex. Nullam commodo elementum sapien, quis convallis nulla tincidunt in. Cras iaculis sem eget tincidunt posuere. Maecenas ultrices, arcu ac ultrices scelerisque, elit neque facilisis urna, et efficitur nisl purus eget tellus. Vivamus condimentum dolor augue, aliquam scelerisque lacus porta non. Proin velit sem, porta et sodales sit amet, tincidunt ac augue. Nulla egestas nibh vitae nisl rhoncus pharetra. In luctus quam vitae sapien volutpat, at egestas erat maximus. Cras interdum id nisl quis molestie. Ut suscipit tellus vel risus eleifend rhoncus. Sed condimentum mattis urna, vel condimentum augue sodales ac. Proin bibendum felis ut felis luctus, sed pretium mauris interdum. In hac habitasse platea dictumst. Nulla ac nulla consectetur, fermentum erat at, gravida odio. Suspendisse tincidunt ultrices elit sit amet vehicula. Interdum et malesuada fames ac ante ipsum primis in faucibus. Pellentesque sagittis, augue a rutrum venenatis, quam orci rhoncus turpis, euismod rutrum justo turpis eu arcu. Phasellus malesuada varius cursus. Donec vel lectus id dolor pharetra mollis. Aliquam sit amet orci hendrerit, sodales turpis sit amet, sodales arcu. Ut faucibus massa ac dictum porta. Fusce ut odio sagittis, faucibus ante sed, lobortis nunc. Proin commodo, magna vitae lacinia ultricies, justo ipsum cursus odio, vel condimentum massa ex non erat. Vivamus consequat dui ligula, non maximus lectus consectetur pellentesque. Suspendisse a nisi mollis, consectetur mi eu, efficitur magna. Nam auctor non nibh at lobortis. Praesent rutrum pulvinar porta. Nulla imperdiet nibh ac risus mattis imperdiet. Cras sed tristique lectus. Vestibulum sodales nulla lorem. Cras non tincidunt nisl. Duis eget vehicula nunc, in lobortis felis. Cras dolor leo, ornare aliquet sollicitudin sed, dictum quis quam. Nulla ante velit, volutpat vel nisl sed, molestie facilisis sem. Praesent consectetur urna porttitor nunc lacinia, et malesuada erat ornare. Mauris mattis, turpis non tristique finibus, urna orci laoreet quam, et sodales felis magna eget nulla. Maecenas suscipit velit ut erat volutpat euismod. Aliquam eu nunc nec quam tincidunt tristique.";

    uint32_t ds1_data_len = strlen(ds1_data_in);
    printf("data_len = %lu\n", ds1_data_len);

    uint8_t ds1_data_out[ds1_data_len];
    uint8_t ds1_tag[16];

    printf("Encrypting with 128-bit key ...\n");

    aes_gcm_cipher(
        // Input parameter
        true,
        0x0, // 128-bit key
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

    //Printf("\n");
    //Printf("Decrypting with 128-bit key ...\n");

    //Aes_gcm_cipher(
    //    // Input parameter
    //    false,
    //    0x0, // 128-bit key
    //    ds1_key,
    //    ds1_iv,
    //    ds1_ad_len,
    //    (uint8_t *) ds1_ad_data,
    //    ds1_data_len,
    //    ds1_data_out,
    //    // Output parameters
    //    ds1_data_out_dec,
    //    ds1_tag_dec);

    //Printf("decrypted msg = %s\n", ds1_data_out_dec);

    //If (memcmp(ds1_tag, ds1_tag_dec, 16) != 0) {
    //    printf("Error: Tags do not match.\n");
    //    return 0;
    //}

    printf("Encrypting with 256-bit key ...\n");

    aes_gcm_cipher(
        // Input parameter
        true,
        0x2, // 256-bit key
        ds1_key,
        ds1_iv,
        ds1_ad_len,
        (uint8_t *) ds1_ad_data,
        ds1_data_len,
        (uint8_t *) ds1_data_in,
        // Output parameters
        ds1_data_out,
        ds1_tag);

    memset(ds1_data_out_dec, 0, ds1_data_len + 1);

    printf("\n");
    printf("Decrypting with 256-bit key ...\n");

    aes_gcm_cipher(
        // Input parameter
        false,
        0x2, // 256-bit key
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
