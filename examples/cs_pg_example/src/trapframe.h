/*
 * Copyright (c) 2015-2024 Beyond Semiconductor
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

/*
 * This header defines layout of trap stack frame.
 * It is used by "traputil" to save/restore context.
 * It can be included by user code to access to saved frame.
 *
 * Registers are stored at sp+TFO_REGISTER_NAME address.
 * This module also provides EXCEPTION_FRAME_SIZE, which defines
 * the size of trap frame.
 */

#ifndef TRAPFRAME_H_
#define TRAPFRAME_H_

/*-----------------------------------------------------------*/

/**
 * Determine number of GPRS we need to save/restore in trap handler(s)
 * (note: we don't save x0 (zero) and x2 (sp))
 */
#ifndef __riscv_32e
	// RV32I
	#define NUM_GPRS 32
	#define NUM_STORED_GPRS 30
#else
	// RV32E
	#define NUM_GPRS 16
	#define NUM_STORED_GPRS 14
#endif

/**
 * Total storage required by all the registers we save in generic
 * exception handler.
 */
#if defined(__riscv_flen) && (__riscv_flen > 0)
	// FPU ABI
	#define TRAP_STACK_REGSPACE (NUM_STORED_GPRS*(__riscv_xlen/8) + 32*(__riscv_flen/8))
#else
	// NO FPU
	#define TRAP_STACK_REGSPACE (NUM_STORED_GPRS*(__riscv_xlen/8))
#endif


/**
 * Total size of exception frame includes space for all registers stored.
 * We also make sure stack remains 16-byte aligned as defined by ABI.
 */
#define TRAP_FRAME_SIZE ( (TRAP_STACK_REGSPACE + 0xf) & ~0xf )

/**
 * Note: this does not define locations for any CSR registers, as
 * may be required when using nested traps or FPU.
 * Those may be saved in handlers, though.
 */

/*-----------------------------------------------------------*/

// sp based offset of first GPR register in trap frame
// registers are aligned so ra and fp are at -4 and -8 offsets
// in frame.
#define TFO_GPR_FIRST (TRAP_FRAME_SIZE - NUM_STORED_GPRS*(__riscv_xlen/8))

/**
 * Exception Frame (SP) relative offsets for registers stored
 * within exception handlers.
 */

#if defined(__riscv_flen) && (__riscv_flen > 0)
	// sp offset of first FP register in exception frame
	#define TFO_FP_FIRST (TFO_GPR_FIRST - 32*(__riscv_flen/8))

	#define TFO_F0  (TFO_FP_FIRST + (0 * __riscv_flen/8))
	#define TFO_F1  (TFO_FP_FIRST + (1 * __riscv_flen/8))
	#define TFO_F2  (TFO_FP_FIRST + (2 * __riscv_flen/8))
	#define TFO_F3  (TFO_FP_FIRST + (3 * __riscv_flen/8))
	#define TFO_F4  (TFO_FP_FIRST + (4 * __riscv_flen/8))
	#define TFO_F5  (TFO_FP_FIRST + (5 * __riscv_flen/8))
	#define TFO_F6  (TFO_FP_FIRST + (6 * __riscv_flen/8))
	#define TFO_F7  (TFO_FP_FIRST + (7 * __riscv_flen/8))
	#define TFO_F8  (TFO_FP_FIRST + (8 * __riscv_flen/8))
	#define TFO_F9  (TFO_FP_FIRST + (9 * __riscv_flen/8))
	#define TFO_F10 (TFO_FP_FIRST + (10 * __riscv_flen/8))
	#define TFO_F11 (TFO_FP_FIRST + (11 * __riscv_flen/8))
	#define TFO_F12 (TFO_FP_FIRST + (12 * __riscv_flen/8))
	#define TFO_F13 (TFO_FP_FIRST + (13 * __riscv_flen/8))
	#define TFO_F14 (TFO_FP_FIRST + (14 * __riscv_flen/8))
	#define TFO_F15 (TFO_FP_FIRST + (15 * __riscv_flen/8))
	#define TFO_F16 (TFO_FP_FIRST + (16 * __riscv_flen/8))
	#define TFO_F17 (TFO_FP_FIRST + (17 * __riscv_flen/8))
	#define TFO_F18 (TFO_FP_FIRST + (18 * __riscv_flen/8))
	#define TFO_F19 (TFO_FP_FIRST + (19 * __riscv_flen/8))
	#define TFO_F20 (TFO_FP_FIRST + (20 * __riscv_flen/8))
	#define TFO_F21 (TFO_FP_FIRST + (21 * __riscv_flen/8))
	#define TFO_F22 (TFO_FP_FIRST + (22 * __riscv_flen/8))
	#define TFO_F23 (TFO_FP_FIRST + (23 * __riscv_flen/8))
	#define TFO_F24 (TFO_FP_FIRST + (24 * __riscv_flen/8))
	#define TFO_F25 (TFO_FP_FIRST + (25 * __riscv_flen/8))
	#define TFO_F26 (TFO_FP_FIRST + (26 * __riscv_flen/8))
	#define TFO_F27 (TFO_FP_FIRST + (27 * __riscv_flen/8))
	#define TFO_F28 (TFO_FP_FIRST + (28 * __riscv_flen/8))
	#define TFO_F29 (TFO_FP_FIRST + (29 * __riscv_flen/8))
	#define TFO_F30 (TFO_FP_FIRST + (30 * __riscv_flen/8))
	#define TFO_F31 (TFO_FP_FIRST + (31 * __riscv_flen/8))

	#define TFO_FP_LAST TFO_F31
	#define TFO_FP_NEXT (TFO_FP_LAST + __riscv_flen/8)

#endif

/* (__riscv_32e is defined only when chosen architecture is RV32E) */
#ifndef __riscv_32e
	// RV32I
	#define TFO_X3  (TFO_GPR_FIRST+(0 * __riscv_xlen/8))
	#define TFO_X4  (TFO_GPR_FIRST+(1 * __riscv_xlen/8))
	#define TFO_X5  (TFO_GPR_FIRST+(2 * __riscv_xlen/8))
	#define TFO_X6  (TFO_GPR_FIRST+(3 * __riscv_xlen/8))
	#define TFO_X7  (TFO_GPR_FIRST+(4 * __riscv_xlen/8))
	#define TFO_X9  (TFO_GPR_FIRST+(5 * __riscv_xlen/8))
	#define TFO_X10 (TFO_GPR_FIRST+(6 * __riscv_xlen/8))
	#define TFO_X11 (TFO_GPR_FIRST+(7 * __riscv_xlen/8))
	#define TFO_X12 (TFO_GPR_FIRST+(8 * __riscv_xlen/8))
	#define TFO_X13 (TFO_GPR_FIRST+(9 * __riscv_xlen/8))
	#define TFO_X14 (TFO_GPR_FIRST+(10 * __riscv_xlen/8))
	#define TFO_X15 (TFO_GPR_FIRST+(11 * __riscv_xlen/8))
	#define TFO_X16 (TFO_GPR_FIRST+(12 * __riscv_xlen/8))
	#define TFO_X17 (TFO_GPR_FIRST+(13 * __riscv_xlen/8))
	#define TFO_X18 (TFO_GPR_FIRST+(14 * __riscv_xlen/8))
	#define TFO_X19 (TFO_GPR_FIRST+(15 * __riscv_xlen/8))
	#define TFO_X20 (TFO_GPR_FIRST+(16 * __riscv_xlen/8))
	#define TFO_X21 (TFO_GPR_FIRST+(17 * __riscv_xlen/8))
	#define TFO_X22 (TFO_GPR_FIRST+(18 * __riscv_xlen/8))
	#define TFO_X23 (TFO_GPR_FIRST+(19 * __riscv_xlen/8))
	#define TFO_X24 (TFO_GPR_FIRST+(20 * __riscv_xlen/8))
	#define TFO_X25 (TFO_GPR_FIRST+(21 * __riscv_xlen/8))
	#define TFO_X26 (TFO_GPR_FIRST+(22 * __riscv_xlen/8))
	#define TFO_X27 (TFO_GPR_FIRST+(23 * __riscv_xlen/8))
	#define TFO_X28 (TFO_GPR_FIRST+(24 * __riscv_xlen/8))
	#define TFO_X29 (TFO_GPR_FIRST+(25 * __riscv_xlen/8))
	#define TFO_X30 (TFO_GPR_FIRST+(26 * __riscv_xlen/8))
	#define TFO_X31 (TFO_GPR_FIRST+(27 * __riscv_xlen/8))
	#define TFO_X1  (TFO_GPR_FIRST+(28 * __riscv_xlen/8))
	#define TFO_X8  (TFO_GPR_FIRST+(29 * __riscv_xlen/8))

#else
	// RV32E
	#define TFO_X3  (TFO_GPR_FIRST+(0 * __riscv_xlen/8))
	#define TFO_X4  (TFO_GPR_FIRST+(1 * __riscv_xlen/8))
	#define TFO_X5  (TFO_GPR_FIRST+(2 * __riscv_xlen/8))
	#define TFO_X6  (TFO_GPR_FIRST+(3 * __riscv_xlen/8))
	#define TFO_X7  (TFO_GPR_FIRST+(4 * __riscv_xlen/8))
	#define TFO_X9  (TFO_GPR_FIRST+(5 * __riscv_xlen/8))
	#define TFO_X10 (TFO_GPR_FIRST+(6 * __riscv_xlen/8))
	#define TFO_X11 (TFO_GPR_FIRST+(7 * __riscv_xlen/8))
	#define TFO_X12 (TFO_GPR_FIRST+(8 * __riscv_xlen/8))
	#define TFO_X13 (TFO_GPR_FIRST+(9 * __riscv_xlen/8))
	#define TFO_X14 (TFO_GPR_FIRST+(10 * __riscv_xlen/8))
	#define TFO_X15 (TFO_GPR_FIRST+(11 * __riscv_xlen/8))
	#define TFO_X1  (TFO_GPR_FIRST+(12 * __riscv_xlen/8))
	#define TFO_X8  (TFO_GPR_FIRST+(13 * __riscv_xlen/8))

#endif

#define TFO_GPR_LAST TFO_X8
#define TFO_GPR_NEXT (TFO_GPR_LAST + __riscv_xlen/8)

#define TFO_NEXT TFO_GPR_NEXT

#endif /* TRAPFRAME_H_ */
