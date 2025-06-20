/**
 * Assembly level entry code: first thing to run in bare metal setup
 *  after power-on.
 *
 * Copyright (c) 2014-2024 Beyond Semiconductor.
 *
 * This code is derived from freedom-metal entry code.
 * Copyright 2018 SiFive, Inc
 * SPDX-License-Identifier: Apache-2.0
 *
 * This code executes before _start, which is (usually) contained inside the
 * C library, but for this sample, which is designed to be usable without
 * stdlib it can be found within start.c.
 * In embedded systems we want to ensure that _enter, which contains the first
 * code to be executed, can be loaded at a specific address.  To enable this
 * feature we provide the '.text.bm.init.enter' section, which is
 * defined to have the first address being where execution should start.
 */

#include "csr_defs.h"
#include "traputil.h"

.section .text.bm.init.enter
.global _enter
_enter:
	.cfi_startproc
	.cfi_undefined ra

/* ---------------------------------------------------------------------------
 * The absolute first thing that must happen is configuring the global
 * pointer register, which must be done with relaxation disabled because
 * otherwise it's not valid to obtain the address of any symbol without
 * GP configured. The C environment might go ahead and do this again, but
 * that's safe as it's a fixed register.
 */
	.option push
	.option norelax
	la gp, __global_pointer$
	.option pop

/* ---------------------------------------------------------------------------
 * Set up a simple trap vector to catch anything that goes wrong early in
 * the boot process.
 */
	la t0, __early_trap_vector
	csrw mtvec, t0

/* ---------------------------------------------------------------------------
 * Bare-metal environment is expected to define its own stack pointer.
 * We also align the stack pointer here because the only RISC-V ABI that's
 * currently defined, mandates 16-byte stack alignment.
 */
	la sp, _sp
	andi sp, sp, -16
/* Increment by hartid number of stack sizes
   ( this code required only when running on multiple harts ) */
	csrr a0, mhartid
	la t0, __stack_size
	andi t0, t0, -16
	li t1, 1
	beqz a0, 2f
1:	add sp, sp, t0
	sub a0, a0, t1
	bnez a0, 1b
2:
	addi sp, sp, -16
	sw x0,12(sp)
	sw x0,8(sp)
	addi fp, sp, 16

/* ---------------------------------------------------------------------------
 * Scrub memory that is selected for scrubbing (stack, ECC data, etc.)
 */
	jal __initial_scrub

/* ---------------------------------------------------------------------------
 * Boot hart zeros bss region and copies data from source to destination.
 */
	csrr t0, mhartid
	la t1, __bm_boot_hart
	bne t0, t1, 1f

	/* zero bss */
	la a0, bm_segment_bss_target_start
	la t0, bm_segment_bss_target_end
	sub a1,t0,a0
	call bm_memzero

	/* copy data */
	la a0, bm_segment_data_target_start
	la a1, bm_segment_data_source_start
	la a2, bm_segment_data_target_end
	sub a2, a2, a0
	call bm_memcopy
1:

/* ---------------------------------------------------------------------------
 * Now that C library Set up trap vector thar calls full C trap handler.
 */
	la t0, __trap_vector
	csrw mtvec, t0

/* ---------------------------------------------------------------------------
 * Then call _start which calls init array(s) and finally executes main.
 */
	csrr a0, mhartid
	call _start

/* ---------------------------------------------------------------------------
 * Start is not supposed to return in bare metal... but if it did due to some
 * error, loop here.
 */
_alldone:
	wfi
	j _alldone

	.cfi_endproc

/* --------------------------------------------------------------------------- */
/* Trap handling helpers */
/* --------------------------------------------------------------------------- */

/*
 * Early trap vector can not call C functions. We set something up so we end
 * up here if exception happens before everything is set up.
 */
.section .text.bm.init.trapvec
.global __early_trap_vector
.align 2
__early_trap_vector:
	.cfi_startproc
	j __early_trap_vector
	.cfi_endproc

/*
 * This is assembly part of generic trap vector.
 * This __trap_vector is present here to allow proper alignment of exception handler
 * which can not be accomplished in C when using -Os size optimization. This will just
 * jump to C __trap_handler.
 */
.global __trap_vector
.align 2
__trap_vector:
	.cfi_startproc

	// save full register set
	SAVE_CONTEXT

	// syscall is processed differently, so check trap cause
	csrr s1, mcause
	addi t0,zero,CSR_MCAUSE_F_CAUSE_E_ECM
	bne s1,t0,1f

	// is a syscall
	jal ra,__syscall_handler
	sw x10,TFO_X10(sp)         // update return value (x10==a0) stored on stack, so it is returned to ecaller
	j 2f                       // now go to regular trap exit code

	// not a syscall
1:	jal ra,__trap_handler

	// restore full register set and return from trap
2:	RESTORE_CONTEXT
	mret

	.cfi_endproc

/* --------------------------------------------------------------------------- */
/* memory copy and zero helpers */
/* --------------------------------------------------------------------------- */

/* Keep it in bm.init section with _enter */
.section .text.bm.init.scrub

/* ---------------------------------------------------------------------------
 * Function to zero-scrub specified memory
 * a0 : start address for zero-scrub
 * a1 : memory region size in bytes
 * (function modifies a0 and a1)
 */
.global bm_memzero
.type bm_memzero, @function
bm_memzero:
	add t0, a0, a1 // t0: first (lowest) address not to be zeroed
	bge a0, t0, 2f // check if already done
1:	sb zero, 0(a0) // clear byte
	addi a0, a0, 1
	blt a0,t0,1b   // loop
2:	ret

/* ---------------------------------------------------------------------------
 * Function to copy memory
 * a0 : start of destination region
 * a1 : start of source region
 * a2 : memory region size in bytes
 * (function modifies a0 and a1)
 */
.global bm_memcopy
.type bm_memcopy, @function
bm_memcopy:
	add t1, a1, a2 // t0: first (lowest) address not to be copied
	bge a1, t1, 2f // check if already done
1:	lb t0, 0(a1)
	sb t0, 0(a0) // clear byte
	addi a0, a0, 1
	addi a1, a1, 1
	blt a1, t1, 1b // loop
2:	ret

/* ---------------------------------------------------------------------------
 * Initialize memories to zero
 * This must be called before anything is stored on stack
 * This cleanup functions are also helpful for easier debug.
 */
.weak __bm_memory_scrub_bit
.weak __initial_scrub
.type __initial_scrub, @function
__initial_scrub:
	mv s0, ra // save return address

	la t0, __bm_memory_scrub_bit
	beqz t0, skip_scrub

	/* Zero out per hart stack */
	mv a0, sp
	la a1, __stack_size
	jal bm_memzero

	la t0, __bm_boot_hart
	csrr a5, mhartid
	bne a5, t0, skip_scrub // only boot_hart scrubs data segment

	/* Zero out data segment */
	la a0, bm_segment_data_target_start
	la a1, bm_segment_data_target_end
	sub a1,a1,a0
	jal bm_memzero

skip_scrub:
	mv ra, s0 // restore original return address
	ret
