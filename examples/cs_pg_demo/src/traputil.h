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

/**
 *  Trap handler helper macros.
 *
 *    SAVE_CONTEXT
 *      -saves current CPU context to stack
 *    RESTORE_CONTEXT
 *      -restores CPU context from stack
 *
 *  These macros can only be used from assembly.
 *
 */

#ifndef _RV_EXCUTIL_H_
#define _RV_EXCUTIL_H_

#include "trapframe.h"
#include "csr_defs.h"

/*-----------------------------------------------------------*/

/* Basic building blocks for context save & restore are defined
 * below */

#if defined(__riscv_flen) && (__riscv_flen == 32)
	#define FS fsw
	#define FL flw
#elif defined(__riscv_flen) && (__riscv_flen == 64)
	#define FS fsd
	#define FL fld
#elif defined(__riscv_flen) && (__riscv_flen > 0)
	#error unsupported float width
#endif

/* This macro defines first block used in context save
 * (16 reg. version)*/
#define CTX_SAVE_REGS_1TO15                                     \
        sw x1,TFO_X1(sp);                                       \
        sw x3,TFO_X3(sp);                                       \
        sw x4,TFO_X4(sp);                                       \
        sw x5,TFO_X5(sp);                                       \
        sw x6,TFO_X6(sp);                                       \
        sw x7,TFO_X7(sp);                                       \
        sw x9,TFO_X9(sp);                                       \
        sw x10,TFO_X10(sp);                                     \
        sw x11,TFO_X11(sp);                                     \
        sw x12,TFO_X12(sp);                                     \
        sw x13,TFO_X13(sp);                                     \
        sw x14,TFO_X14(sp);                                     \
        sw x15,TFO_X15(sp);                                     \
        sw x8,TFO_X8(sp);

/* This macro defines first block used in context save
 * (32 reg. version) */
#define CTX_SAVE_REGS_1TO31                                     \
        sw x1,TFO_X1(sp);                                       \
        sw x3,TFO_X3(sp);                                       \
        sw x4,TFO_X4(sp);                                       \
        sw x5,TFO_X5(sp);                                       \
        sw x6,TFO_X6(sp);                                       \
        sw x7,TFO_X7(sp);                                       \
        sw x9,TFO_X9(sp);                                       \
        sw x10,TFO_X10(sp);                                     \
        sw x11,TFO_X11(sp);                                     \
        sw x12,TFO_X12(sp);                                     \
        sw x13,TFO_X13(sp);                                     \
        sw x14,TFO_X14(sp);                                     \
        sw x15,TFO_X15(sp);                                     \
        sw x16,TFO_X16(sp);                                     \
        sw x17,TFO_X17(sp);                                     \
        sw x18,TFO_X18(sp);                                     \
        sw x19,TFO_X19(sp);                                     \
        sw x20,TFO_X20(sp);                                     \
        sw x21,TFO_X21(sp);                                     \
        sw x22,TFO_X22(sp);                                     \
        sw x23,TFO_X23(sp);                                     \
        sw x24,TFO_X24(sp);                                     \
        sw x25,TFO_X25(sp);                                     \
        sw x26,TFO_X26(sp);                                     \
        sw x27,TFO_X27(sp);                                     \
        sw x28,TFO_X28(sp);                                     \
        sw x29,TFO_X29(sp);                                     \
        sw x30,TFO_X30(sp);                                     \
        sw x31,TFO_X31(sp);                                     \
        sw x8,TFO_X8(sp);

#define CTX_SAVE_FP_REGS                                        \
        FS f0,TFO_F0(sp);                                       \
        FS f1,TFO_F1(sp);                                       \
        FS f2,TFO_F2(sp);                                       \
        FS f3,TFO_F3(sp);                                       \
        FS f4,TFO_F4(sp);                                       \
        FS f5,TFO_F5(sp);                                       \
        FS f6,TFO_F6(sp);                                       \
        FS f7,TFO_F7(sp);                                       \
        FS f8,TFO_F8(sp);                                       \
        FS f9,TFO_F9(sp);                                       \
        FS f10,TFO_F10(sp);                                     \
        FS f11,TFO_F11(sp);                                     \
        FS f12,TFO_F12(sp);                                     \
        FS f13,TFO_F13(sp);                                     \
        FS f14,TFO_F14(sp);                                     \
        FS f15,TFO_F15(sp);                                     \
        FS f16,TFO_F16(sp);                                     \
        FS f17,TFO_F17(sp);                                     \
        FS f18,TFO_F18(sp);                                     \
        FS f19,TFO_F19(sp);                                     \
        FS f20,TFO_F20(sp);                                     \
        FS f21,TFO_F21(sp);                                     \
        FS f22,TFO_F22(sp);                                     \
        FS f23,TFO_F23(sp);                                     \
        FS f24,TFO_F24(sp);                                     \
        FS f25,TFO_F25(sp);                                     \
        FS f26,TFO_F26(sp);                                     \
        FS f27,TFO_F27(sp);                                     \
        FS f28,TFO_F28(sp);                                     \
        FS f29,TFO_F29(sp);                                     \
        FS f30,TFO_F30(sp);                                     \
        FS f31,TFO_F31(sp);

/* Restores 16 GPRS. You can not change GPRs after this block. */
/* Note: we restore sp (aka x2) last */
#define CTX_RESTORE_REGS_1TO15                                  \
        lw x1,TFO_X1(sp);                                       \
        lw x3,TFO_X3(sp);                                       \
        lw x4,TFO_X4(sp);                                       \
        lw x5,TFO_X5(sp);                                       \
        lw x6,TFO_X6(sp);                                       \
        lw x7,TFO_X7(sp);                                       \
        lw x8,TFO_X8(sp);                                       \
        lw x9,TFO_X9(sp);                                       \
        lw x10,TFO_X10(sp);                                     \
        lw x11,TFO_X11(sp);                                     \
        lw x12,TFO_X12(sp);                                     \
        lw x13,TFO_X13(sp);                                     \
        lw x14,TFO_X14(sp);                                     \
        lw x15,TFO_X15(sp);                                     \
        lw x8,TFO_X8(sp);

/* Restores 32 GPRS. You can not change GPRs after this block. */
#define CTX_RESTORE_REGS_1TO31                                  \
        lw x1,TFO_X1(sp);                                       \
        lw x3,TFO_X3(sp);                                       \
        lw x4,TFO_X4(sp);                                       \
        lw x5,TFO_X5(sp);                                       \
        lw x6,TFO_X6(sp);                                       \
        lw x7,TFO_X7(sp);                                       \
        lw x9,TFO_X9(sp);                                       \
        lw x10,TFO_X10(sp);                                     \
        lw x11,TFO_X11(sp);                                     \
        lw x12,TFO_X12(sp);                                     \
        lw x13,TFO_X13(sp);                                     \
        lw x14,TFO_X14(sp);                                     \
        lw x15,TFO_X15(sp);                                     \
        lw x16,TFO_X16(sp);                                     \
        lw x17,TFO_X17(sp);                                     \
        lw x18,TFO_X18(sp);                                     \
        lw x19,TFO_X19(sp);                                     \
        lw x20,TFO_X20(sp);                                     \
        lw x21,TFO_X21(sp);                                     \
        lw x22,TFO_X22(sp);                                     \
        lw x23,TFO_X23(sp);                                     \
        lw x24,TFO_X24(sp);                                     \
        lw x25,TFO_X25(sp);                                     \
        lw x26,TFO_X26(sp);                                     \
        lw x27,TFO_X27(sp);                                     \
        lw x28,TFO_X28(sp);                                     \
        lw x29,TFO_X29(sp);                                     \
        lw x30,TFO_X30(sp);                                     \
        lw x31,TFO_X31(sp);                                     \
        lw x8,TFO_X8(sp);

#define CTX_RESTORE_FP_REGS                                        \
        FL f0,TFO_F0(sp);                                       \
        FL f1,TFO_F1(sp);                                       \
        FL f2,TFO_F2(sp);                                       \
        FL f3,TFO_F3(sp);                                       \
        FL f4,TFO_F4(sp);                                       \
        FL f5,TFO_F5(sp);                                       \
        FL f6,TFO_F6(sp);                                       \
        FL f7,TFO_F7(sp);                                       \
        FL f8,TFO_F8(sp);                                       \
        FL f9,TFO_F9(sp);                                       \
        FL f10,TFO_F10(sp);                                     \
        FL f11,TFO_F11(sp);                                     \
        FL f12,TFO_F12(sp);                                     \
        FL f13,TFO_F13(sp);                                     \
        FL f14,TFO_F14(sp);                                     \
        FL f15,TFO_F15(sp);                                     \
        FL f16,TFO_F16(sp);                                     \
        FL f17,TFO_F17(sp);                                     \
        FL f18,TFO_F18(sp);                                     \
        FL f19,TFO_F19(sp);                                     \
        FL f20,TFO_F20(sp);                                     \
        FL f21,TFO_F21(sp);                                     \
        FL f22,TFO_F22(sp);                                     \
        FL f23,TFO_F23(sp);                                     \
        FL f24,TFO_F24(sp);                                     \
        FL f25,TFO_F25(sp);                                     \
        FL f26,TFO_F26(sp);                                     \
        FL f27,TFO_F27(sp);                                     \
        FL f28,TFO_F28(sp);                                     \
        FL f29,TFO_F29(sp);                                     \
        FL f30,TFO_F30(sp);                                     \
        FL f31,TFO_F31(sp);

/*-----------------------------------------------------------*/

/* RAW context save & restore macros.
 * There are four different versions:
 *   -32 GPRS + FPU
 *   -32 GPRS
 *   -16 GPRS + FPU
 *   -16 GPRS
 */

/* Compiler defines __riscv_32e if rv32e arch was selected when
 * compiling code. */
#ifndef __riscv_32e
	/* riscv_32i version */

	#if defined(__riscv_flen) && (__riscv_flen > 0)
		/* version for builds that use FPU */

		/* This macro saves CPU context when entering trap
		 * handler. */
		#define SAVE_CONTEXT                        \
		            addi sp,sp,-TRAP_FRAME_SIZE; \
		            CTX_SAVE_REGS_1TO31; \
		            addi fp,sp,TRAP_FRAME_SIZE; \
		            CTX_SAVE_FP_REGS;

		/* This macro restores CPU context when returning from exception
		 * handler. It restores state saved by SAVE_CONTEXT macro. */
		#define RESTORE_CONTEXT \
		            CTX_RESTORE_FP_REGS \
		            CTX_RESTORE_REGS_1TO31 \
		            addi sp,sp,TRAP_FRAME_SIZE;

	#else
		/* version for build that does not use FPU */

		#define SAVE_CONTEXT                          \
		            addi sp,sp,-TRAP_FRAME_SIZE; \
		            CTX_SAVE_REGS_1TO31; \
		            addi fp,sp,TRAP_FRAME_SIZE;

		#define RESTORE_CONTEXT                       \
		            CTX_RESTORE_REGS_1TO31            \
		            addi sp,sp,TRAP_FRAME_SIZE;

	#endif /* fpu */

#else /* __riscv_32e version */

	/* These are versions of SAVE/RESTORE macro for 16 register
	   CPU version. They skip registers x16-x31. */

	#if defined(__riscv_flen) && (__riscv_flen > 0)
		/* version for builds that use FPU */

		/* This macro saves CPU context when entering trap
		 * handler. */
		#define SAVE_CONTEXT                        \
		            addi sp,sp,-TRAP_FRAME_SIZE; \
		            CTX_SAVE_REGS_1TO15 \
		            addi fp,sp,TRAP_FRAME_SIZE; \
		            CTX_SAVE_FP_REGS

		/* This macro restores CPU context when returning from exception
		 * handler. It restores state saved by SAVE_CONTEXT macro. */
		#define RESTORE_CONTEXT \
		            CTX_RESTORE_FP_REGS \
		            CTX_RESTORE_REGS_1TO15 \
		            addi sp,sp,TRAP_FRAME_SIZE;

	#else
		/* version for build that does not use FPU */

		#define SAVE_CONTEXT                          \
					addi sp,sp,-TRAP_FRAME_SIZE; \
					CTX_SAVE_REGS_1TO15; \
		            addi fp,sp,TRAP_FRAME_SIZE;

		#define RESTORE_CONTEXT                       \
					CTX_RESTORE_REGS_1TO15            \
					addi sp,sp,TRAP_FRAME_SIZE;

	#endif /* fpu */

#endif /* rv32i/rv32e */

#endif /* _RV_EXCUTIL_H_ */
