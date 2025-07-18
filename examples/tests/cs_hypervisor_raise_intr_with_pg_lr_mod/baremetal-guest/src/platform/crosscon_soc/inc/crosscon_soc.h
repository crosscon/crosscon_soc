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

#ifndef __CROSSCON_SOC_H__
#define __CROSSCON_SOC_H__

#include <stdint.h>
#include <stdbool.h>

/// BA51's DID register
#define PG_ADD_SIG_DRV_ADR 0x23100000

// QMEM's PG registers base address
#define QMEM_PG_CSR_ADR 0x23200000

//
// Restricted address space mode configuration registers
//

// Number of available address ranges. Needs to be adjusted to the actual
// number of ranges supported by a specific instance of PG.
#define PG_RAS_NUM_OF_RANGES 8
// The address of the first range address register
#define PG_RAS_ADDR_FIRST_REG_ADDR 0x10
// The address of the first range access permission registers
#define PG_RAS_ACC_PRM_FIRST_REG_ADDR (PG_RAS_ADDR_FIRST_REG_ADDR + PG_RAS_NUM_OF_RANGES + 1)
                                                                                
// The range address permission field indices
// Read permission index
#define PG_RAS_ACC_PRM_REG_R_BIT 0
// Write permission index
#define PG_RAS_ACC_PRM_REG_W_BIT 1
// Start and end of the DID field
#define PG_RAS_ACC_PRM_REG_DID_SIZE 29
#define PG_RAS_ACC_PRM_REG_DID_LOW 2
#define PG_RAS_ACC_PRM_REG_DID_HIGH (PG_RAS_ACC_PRM_REG_DID_LOW + PG_RAS_ACC_PRM_REG_DID_SIZE)
 // Range active index - HIGH when the range has a valid address and permissions.
#define PG_RAS_ACC_PRM_REG_A_BIT 31

//
// AES-GCM accelerator registers
//

// AES-GCM base address
#define AES_MM_CFG_BASE_ADR 0x24000000

// State register
#define AES_GCM_STATE_REG 0
// Encryption / decryption registers
#define AES_GCM_ENCRYPT_REG 1
// Key length register
#define AES_GCM_KEYL_REG 2
// Key register
#define AES_GCM_KEY_REG 3
// Initialization vector register
#define AES_GCM_IV_REG 11
// Address length
#define AES_GCM_A_LEN_REG 14
// Data length
#define AES_GCM_D_LEN_REG 15
// Address where the input data is located
#define AES_GCM_IN_D_ADDR_REG 16
// Address where the output data is located
#define AES_GCM_OUT_D_ADDR_REG 17

// State register fields
// Needs to be set to HIGH when the master has provided the initialization parameters.
#define AES_GCM_STATE_INIT_FLAG 0
// HIGH when input data is ready. Can only be written to.
#define AES_GCM_STATE_IN_D_RDY_FLAG 1
// HIGH when output data is ready. Can only be read.
#define AES_GCM_STATE_OUT_D_RDY_FLAG 2
// HIGH when tag is ready.
#define AES_GCM_STATE_TAG_RDY_FLAG 3

// Set address range entry of PG in restricted address space mode.
void set_pg_rspace_entry(
    uint32_t* pg_csrs_base,
    uint8_t entry,
    uint8_t did,
    uint32_t from_addr,
    uint32_t to_addr,
    bool allow_read,
    bool allow_write);

// Clear address range entry of PG in restricted address space mode.
void clear_pg_rspace_entry(uint32_t* pg_csrs_base, uint8_t entry);

#endif /* __CROSSCON_SOC_H__ */
